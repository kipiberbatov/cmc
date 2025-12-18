#include <stdlib.h>

#include "cmc_error_message.h"
#include "int.h"
#include "mesh_brick_private.h"

static void mesh_brick_boundary_p(int * m_bd_p, int d, const int * n, int p)
{
  int bin_d_p, ind, sign_p, sign_v, u, v, y_ind, y_size;
  int a[MAX_DIM], n_bar_p[MAX_DIM];

  bin_d_p = int_binomial(d, p);
  sign_p = (p % 2 == 1) ? 1 : -1;
  ind = 0;
  int_array_assign_identity(a, p);
  for (u = 0; u < bin_d_p; ++u)
  {
    mesh_brick_assign_n_bar(n_bar_p, d, n, p, a);
    y_size = int_array_total_product(d, n_bar_p);
    for (y_ind = 0; y_ind < y_size; ++y_ind)
    {
      sign_v = 1;
      for (v = 0; v < p; ++v)
      {
        m_bd_p[ind] = -sign_p * sign_v;
        m_bd_p[ind + 1] = sign_p * sign_v;
        ind += 2;
        sign_v *= -1;
      }
    }
    if (u < bin_d_p - 1)
      int_array_combination_next(a, d, p);
  }
}

int ** mesh_brick_boundary(int d, const int * n, const int * m_bd_sizes)
{
  int p;
  int ** m_bd;

  m_bd = (int **) malloc(sizeof(int *) * d);
  if (m_bd == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(int *) * d, "m->bd");
    return NULL;
  }

  for (p = 1; p <= d; ++p)
  {
    m_bd[p - 1] = (int *) malloc(sizeof(int) * m_bd_sizes[p - 1]);
    if (m_bd[p - 1] == NULL)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr,
        "cannot allocate %s%zu%s bytes of memory for m->bd[%s%d%s]\n",
        color_variable, sizeof(int) * m_bd_sizes[p - 1], color_none,
        color_variable, p - 1, color_none);
      int_array2_free(m_bd, p - 1);
      return NULL;
    }

    mesh_brick_boundary_p(m_bd[p - 1], d, n, p);
  }
  return m_bd;
}
