#include <stdlib.h>

#include "cmc_error_message.h"
#include "color.h"
#include "matrix_sparse.h"

static void matrix_sparse_columns_restrict_set_cols_total(
  int * b_cols_total,
  const matrix_sparse * a,
  const jagged1 * columns)
{
  int b_cols, j, j_local, rows_j;
  int * a_cols_total, * columns_a1;

  b_cols = columns->a0;
  columns_a1 = columns->a1;
  a_cols_total = a->cols_total;

  b_cols_total[0] = 0;
  for (j_local = 0; j_local < b_cols; ++j_local)
  {
    j = columns_a1[j_local];
    rows_j = a_cols_total[j + 1] - a_cols_total[j];
    b_cols_total[j_local + 1] = b_cols_total[j_local] + rows_j;
  }
}

static void matrix_sparse_columns_restrict_set_row_indices(
  int * b_row_indices,
  const matrix_sparse * a,
  const jagged1 * columns,
  const int * b_cols_total)
{
  int b_cols, i_local, j, j_local, rows_j;
  int * a_cols_total, * a_row_indices, * a_row_indices_j,
      * b_row_indices_j_local, * columns_a1;

  b_cols = columns->a0;
  columns_a1 = columns->a1;
  a_cols_total = a->cols_total;
  a_row_indices = a->row_indices;

  for (j_local = 0; j_local < b_cols; ++j_local)
  {
    j = columns_a1[j_local];
    rows_j = a_cols_total[j + 1] - a_cols_total[j];
    a_row_indices_j = a_row_indices + a_cols_total[j];
    b_row_indices_j_local = b_row_indices + b_cols_total[j_local];
    for (i_local = 0; i_local < rows_j; ++i_local)
      b_row_indices_j_local[i_local] = a_row_indices_j[i_local];
  }
}

static void matrix_sparse_columns_restrict_set_values(
  double * b_values,
  const matrix_sparse * a,
  const jagged1 * columns,
  const int * b_cols_total)
{
  int b_cols, i_local, j, j_local, rows_j;
  int * a_cols_total, * columns_a1;
  double * a_values, * a_values_j, * b_values_j_local;

  b_cols = columns->a0;
  columns_a1 = columns->a1;
  a_cols_total = a->cols_total;
  a_values = a->values;

  for (j_local = 0; j_local < b_cols; ++j_local)
  {
    j = columns_a1[j_local];
    rows_j = a_cols_total[j + 1] - a_cols_total[j];
    a_values_j = a_values + a_cols_total[j];
    b_values_j_local = b_values + b_cols_total[j_local];
    for (i_local = 0; i_local < rows_j; ++i_local)
      b_values_j_local[i_local] = a_values_j[i_local];
  }
}

matrix_sparse * matrix_sparse_columns_restrict(
  const matrix_sparse * a,
  const jagged1 * columns)
{
  int b_nonzero_max;
  matrix_sparse * b;

  b = (matrix_sparse *) malloc(sizeof(matrix_sparse));
  if (b == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(matrix_sparse), "b");
    goto end;
  }

  b->rows = a->rows;
  b->cols = columns->a0;

  b->cols_total = (int *) malloc(sizeof(int) * (b->cols + 1));
  if (b->cols_total == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(int) * (b->cols + 1), "b->cols_total");
    goto b_free;
  }
  matrix_sparse_columns_restrict_set_cols_total(b->cols_total, a, columns);

  b_nonzero_max = b->cols_total[b->cols];

  b->row_indices = (int *) malloc(sizeof(int) * b_nonzero_max);
  if (b->row_indices == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(int) * b_nonzero_max, "b->row_indices");
    goto b_cols_total_free;
  }
  matrix_sparse_columns_restrict_set_row_indices(
    b->row_indices, a, columns, b->cols_total);

  b->values = (double *) malloc(sizeof(double) * b_nonzero_max);
  if (b->values == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * b_nonzero_max, "b->values");
    goto b_row_indices_free;
  }
  matrix_sparse_columns_restrict_set_values(
    b->values, a, columns, b->cols_total);

  return b;

  /* cleaning if an error occurs */
b_row_indices_free:
  free(b->row_indices);
b_cols_total_free:
  free(b->cols_total);
b_free:
  free(b);
end:
  return NULL;
}
