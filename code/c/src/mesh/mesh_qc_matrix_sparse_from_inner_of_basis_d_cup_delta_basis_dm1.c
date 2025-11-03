#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "mesh_qc.h"

static void
update_values(matrix_sparse * b, const double * m_inner_d)
{
  int b_cols, i, i_local, j;
  int * b_cols_total, * b_row_indices;
  double * b_values;

  b_cols = b->cols;
  b_cols_total = b->cols_total;
  b_row_indices = b->row_indices;
  b_values = b->values;

  for (j = 0; j < b_cols; ++j)
  {
    for (i_local = b_cols_total[j]; i_local < b_cols_total[j + 1]; ++i_local)
    {
      i = b_row_indices[i_local];
      b_values[i_local] *= m_inner_d[i];
    }
  }
}

matrix_sparse *
mesh_qc_matrix_sparse_from_inner_of_basis_d_cup_delta_basis_dm1(
  const matrix_sparse * m_cbd_dm1,
  const double * m_inner_d)
{
  int nonzero_max;
  matrix_sparse * b;

  b = (matrix_sparse *) malloc(sizeof(matrix_sparse));
  if (b == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytes of memory for b\n", sizeof(matrix_sparse));
    return NULL;
  }

  matrix_sparse_copy_topology(b, m_cbd_dm1);

  nonzero_max = b->cols_total[b->cols];
  b->values = (double *) malloc(sizeof(double) * nonzero_max);
  if (b->values == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytes of memory for b->values\n",
      sizeof(double) * nonzero_max);
    free(b);
    return NULL;
  }
  memcpy(b->values, m_cbd_dm1->values, sizeof(double) * nonzero_max);
  update_values(b, m_inner_d);

  return b;
}
