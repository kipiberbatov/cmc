#include "matrix_sparse.h"

/* Find the diagonal(d[0], ..., d[a->cols - 1]) . a */
void matrix_sparse_multiply_with_diagonal_matrix_on_the_left(
  matrix_sparse * a,
  const double * d)
{
  int i, i_global, j, n;
  int * a_cols_total, * a_row_indices;
  double * a_values;

  n = a->cols;
  a_cols_total = a->cols_total;
  a_row_indices = a->row_indices;
  a_values = a->values;

  for (j = 0; j < n; ++j)
  {
    for (i_global = a_cols_total[j]; i_global < a_cols_total[j + 1]; ++i_global)
    {
      i = a_row_indices[i_global];
      a_values[i_global] *= d[i];
    }
  }
}
