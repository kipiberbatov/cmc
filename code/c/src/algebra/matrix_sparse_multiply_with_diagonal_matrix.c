#include "matrix_sparse.h"

/* Find the a . diagonal(d[0], ..., d[a->cols - 1]) */
void matrix_sparse_multiply_with_diagonal_matrix(
  matrix_sparse * a,
  const double * d)
{
  int i_global, j, n;
  int * a_cols_total;
  double d_j;
  double * a_values;

  n = a->cols;
  a_cols_total = a->cols_total;
  a_values = a->values;

  for (j = 0; j < n; ++j)
  {
    d_j = d[j];
    for (i_global = a_cols_total[j]; i_global < a_cols_total[j + 1]; ++i_global)
      a_values[i_global] *= d_j;
  }
}
