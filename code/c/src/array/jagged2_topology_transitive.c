#include "cmc_error_message.h"
#include "cmc_memory.h"
#include "int.h"
#include "jagged.h"

static int find_total_max(const jagged2 * x_to_y, const jagged2 * y_to_z)
{
  int cumulative_index, i, j, j_local, total_i, total_max, x_to_y_a0,
      x_to_y_a1_i;
  int * x_to_y_a1, * x_to_y_a2, * x_to_y_a2_i, * y_to_z_a1;

  x_to_y_a0 = x_to_y->a0;
  x_to_y_a1 = x_to_y->a1;
  x_to_y_a2 = x_to_y->a2;
  y_to_z_a1 = y_to_z->a1;

  total_max = 0;
  cumulative_index = 0;
  for (i = 0; i < x_to_y_a0; ++i)
  {
    x_to_y_a1_i = x_to_y_a1[i];
    x_to_y_a2_i = x_to_y_a2 + cumulative_index;
    cumulative_index += x_to_y_a1_i;
    total_i = 0;
    for (j_local = 0; j_local < x_to_y_a1_i; ++j_local)
    {
      j = x_to_y_a2_i[j_local];
      total_i += y_to_z_a1[j];
    }
    if (total_max < total_i)
      total_max = total_i;
  }
  return total_max / 2;
}

static void find_union(
  jagged1 * x_to_z_i, int i, const jagged1 * x_to_y_i, const jagged2 * y_to_z)
{
  int j, j_local, k, k_local, q_r_index, value, x_to_y_i_a0, x_to_z_i_a0;
  int * x_to_y_i_a1, * x_to_z_i_a1, * y_to_z_a1, * y_to_z_a2;

  x_to_y_i_a0 = x_to_y_i->a0;
  x_to_y_i_a1 = x_to_y_i->a1;
  x_to_z_i_a1 = x_to_z_i->a1;
  y_to_z_a1 = y_to_z->a1;
  y_to_z_a2 = y_to_z->a2;

  x_to_z_i_a0 = 0;
  for (j_local = 0; j_local < x_to_y_i_a0; ++j_local)
  {
    j = x_to_y_i_a1[j_local];
    q_r_index = int_array_total_sum(j, y_to_z_a1);
    for (k_local = 0; k_local < y_to_z_a1[j]; ++k_local)
    {
      k = q_r_index + k_local;
      value = y_to_z_a2[k];
      if (!int_array_member(x_to_z_i_a0, x_to_z_i_a1, value))
      {
        x_to_z_i_a1[x_to_z_i_a0] = value;
        ++x_to_z_i_a0;
      }
    }
  }
  x_to_z_i->a0 = x_to_z_i_a0;
  x_to_z_i->a1 = x_to_z_i_a1;
}

void jagged2_topology_transitive(
  jagged2 ** x_to_z_, int * status,
  const jagged2 * x_to_y, const jagged2 * y_to_z)
{
  int x_to_z_a2_size, i, index, cumulative_index, total_max, x_to_y_a0;
  int * x_to_y_a1, * x_to_y_a2, * x_to_z_a1, * x_to_z_a2, * x_to_z_a2_i;
  jagged2 * x_to_z;
  jagged1 x_to_y_i, x_to_z_i;

  x_to_y_a0 = x_to_y->a0;
  x_to_y_a1 = x_to_y->a1;
  x_to_y_a2 = x_to_y->a2;

  cmc_memory_allocate((void **) &x_to_z, status, sizeof(jagged2));
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("x_to_z");
    goto end;
  }

  cmc_memory_allocate((void **) &x_to_z_a1, status, sizeof(int) * x_to_y_a0);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("x_to_z_a1");
    goto x_to_z_free;
  }

  total_max = find_total_max(x_to_y, y_to_z);
  cmc_memory_allocate((void **) &x_to_z_a2_i, status, sizeof(int) * total_max);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("x_to_z_a2_i");
    goto x_to_z_a1_free;
  }

  x_to_z_a2_size = 0;
  cumulative_index = 0;
  x_to_z_i.a1 = x_to_z_a2_i;
  for (i = 0; i < x_to_y_a0; ++i)
  {
    x_to_y_i.a0 = x_to_y_a1[i];
    x_to_y_i.a1 = x_to_y_a2 + cumulative_index;
    find_union(&x_to_z_i, i, &x_to_y_i, y_to_z);
    cumulative_index += x_to_y_i.a0;
    x_to_z_a2_size += x_to_z_i.a0;
    x_to_z_a1[i] = x_to_z_i.a0;
  }
  cmc_memory_free(x_to_z_a2_i);

  cmc_memory_allocate(
    (void **) &x_to_z_a2, status, sizeof(int) * x_to_z_a2_size);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("x_to_z_a2");
    goto x_to_z_a1_free;
  }

  cumulative_index = 0;
  index = 0;
  for (i = 0; i < x_to_y_a0; ++i)
  {
    x_to_z_i.a1 = x_to_z_a2 + index;
    x_to_y_i.a0 = x_to_y_a1[i];
    x_to_y_i.a1 = x_to_y_a2 + cumulative_index;
    find_union(&x_to_z_i, i, &x_to_y_i, y_to_z);
    cumulative_index += x_to_y_i.a0;
    index += x_to_z_i.a0;
  }

  x_to_z->a0 = x_to_y_a0;
  x_to_z->a1 = x_to_z_a1;
  x_to_z->a2 = x_to_z_a2;
  *x_to_z_ = x_to_z;
  return;

  /* cleaning if an error occurs */
x_to_z_a1_free:
  cmc_memory_free(x_to_z_a1);
x_to_z_free:
  cmc_memory_free(x_to_z);
end:
  return;
}
