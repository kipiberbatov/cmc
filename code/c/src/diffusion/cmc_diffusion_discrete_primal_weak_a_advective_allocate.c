#include "cmc_diffusion_discrete_primal_weak_a_advective_private.h"
#include "cmc_error_message.h"
#include "cmc_memory.h"
#include "int.h"
#include "mesh.h"

void cmc_diffusion_discrete_primal_weak_a_advective_allocate(
  struct matrix_sparse ** a_advective_pointer,
  int * status,
  const struct mesh * K)
{
  int d = K->dim;
  int power_2_d = (1 << d);
  int cn_0 = K->cn[0];

  int max;
  struct jagged2 fc_0_d;
  struct matrix_sparse * a_advective;

  cmc_memory_allocate(
    (void **) a_advective_pointer, status, sizeof(a_advective));
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("a_advective");
    goto end;
  }

  a_advective = *a_advective_pointer;
  a_advective->cols = cn_0;
  a_advective->rows = cn_0;

  cmc_memory_allocate(
    (void **) &(a_advective->cols_total), status, sizeof(int) * (cn_0 + 1));
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("a_advective_cols");
    goto a_advective_free;
  }

  mesh_fc_part2(&fc_0_d, K, 0, d);
  max = int_array_total_sum(cn_0, fc_0_d.a2) * power_2_d;

  cmc_memory_allocate(
    (void **) &(a_advective->row_indices), status, sizeof(int) * max);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("a_advective_row_indices");
    goto a_advective_cols_total_free;
  }

  cmc_memory_allocate(
    (void **) &(a_advective->values), status, sizeof(double) * max);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("a_advective_row_indices");
    goto a_advective_row_indices_free;
  }

  goto end;

  /* cleaning if an error occurs */
a_advective_row_indices_free:
  cmc_memory_free(a_advective->row_indices);
a_advective_cols_total_free:
  cmc_memory_free(a_advective->cols_total);
a_advective_free:
  cmc_memory_free(a_advective);
end:
  return;
}
