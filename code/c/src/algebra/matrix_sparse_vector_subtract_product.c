#include "matrix_sparse.h"

/* q -= b . u */
void matrix_sparse_vector_subtract_product(
  double * q,
  const matrix_sparse * b,
  const double * u)
{
  int b_cols, b_rows_j, i, i_local, j;
  int * b_cols_total, * b_row_indices, * b_row_indices_j;
  double b_i_j, u_j;
  double * b_values, * b_values_j;

  b_cols = b->cols;
  b_cols_total = b->cols_total;
  b_row_indices = b->row_indices;
  b_values = b->values;
  for (j = 0; j < b_cols; ++j)
  {
    b_rows_j = b_cols_total[j + 1] - b_cols_total[j];
    b_row_indices_j = b_row_indices + b_cols_total[j];
    b_values_j = b_values + b_cols_total[j];
    u_j = u[j];
    for (i_local = 0; i_local < b_rows_j; ++i_local)
    {
      i = b_row_indices_j[i_local];
      b_i_j = b_values_j[i_local];
      q[i] -= b_i_j * u_j;
    }
  }
}
