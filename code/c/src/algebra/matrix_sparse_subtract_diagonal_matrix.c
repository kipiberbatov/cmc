#include "matrix_sparse.h"

void matrix_sparse_subtract_diagonal_matrix(
  matrix_sparse * a,
  const double * d)
{
  int i_loc, j, n;
  int * a_cols_total, * a_row_indices;
  double * a_values;

  n = a->cols;
  a_cols_total = a->cols_total;
  a_row_indices = a->row_indices;
  a_values = a->values;
  for (j = 0; j < n; ++j)
  {
    for (i_loc = a_cols_total[j]; i_loc < a_cols_total[j + 1]; ++i_loc)
    {
      if (a_row_indices[i_loc] == j)
      {
        a_values[i_loc] -= d[j];
        break;
      }
    }
  }
}
