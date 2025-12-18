#include <stdlib.h>

#include "cmc_error_message.h"
#include "matrix_sparse.h"

static void jagged1_intersection_indices(
  int * res, const jagged1 * arr1, const jagged1 * arr2)
{
  int i, ind, j;

  ind = 0;
  for (i = 0; i < arr1->a0; ++i)
  {
    j = jagged1_position(arr2, arr1->a1[i]);
    if (j != -1)
    {
      res[ind] = j;
      ++ind;
    }
  }
}

static void matrix_sparse_remove_cols_total(
  int * b_cols_total, const matrix_sparse * a, const jagged1 * rows_complement,
  const jagged1 * cols_complement)
{
  int j, j_loc, col_nonzero;
  jagged1 col;

  b_cols_total[0] = 0;
  for (j_loc = 0; j_loc < cols_complement->a0; ++j_loc)
  {
    j = cols_complement->a1[j_loc];
    col.a0 = a->cols_total[j + 1] - a->cols_total[j];
    col.a1 = a->row_indices + a->cols_total[j];
    col_nonzero = jagged1_intersection_count(&col, rows_complement);
    b_cols_total[j_loc + 1] = b_cols_total[j_loc] + col_nonzero;
  }
}

static void matrix_sparse_remove_row_indices(
  int * b_row_indices, const matrix_sparse * a, const jagged1 * rows_complement,
  const jagged1 * cols_complement, const int * b_cols_total)
{
  int j, j_loc;
  jagged1 col;

  for (j_loc = 0; j_loc < cols_complement->a0; ++j_loc)
  {
    j = cols_complement->a1[j_loc];
    col.a0 = a->cols_total[j + 1] - a->cols_total[j];
    col.a1 = a->row_indices + a->cols_total[j];
    jagged1_intersection_indices(
      b_row_indices + b_cols_total[j_loc], &col, rows_complement);
  }
}

static void matrix_sparse_remove_values(
  double * b_values, const matrix_sparse * a, const jagged1 * rows_complement,
  const jagged1 * cols_complement, const int * b_cols_total,
  const int * b_row_indices)
{
  int i, i_loc, j, j_loc;
  double * a_values_j;
  jagged1 col;

  for (j_loc = 0; j_loc < cols_complement->a0; ++j_loc)
  {
    j = cols_complement->a1[j_loc];
    col.a0 = a->cols_total[j + 1] - a->cols_total[j];
    col.a1 = a->row_indices + a->cols_total[j];
    a_values_j = a->values + a->cols_total[j];
    for (i_loc = b_cols_total[j_loc]; i_loc < b_cols_total[j_loc + 1]; ++i_loc)
    {
      i = jagged1_position(&col, rows_complement->a1[b_row_indices[i_loc]]);
      b_values[i_loc] = a_values_j[i];
    }
  }
}

matrix_sparse * matrix_sparse_restrict(
  const matrix_sparse * a, const jagged1 * rows_complement,
  const jagged1 * cols_complement)
{
  int b_nonzero_max;
  matrix_sparse * b;

  b = (matrix_sparse *) malloc(sizeof(matrix_sparse));
  if (b == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for b\n",
      sizeof(matrix_sparse));
    goto end;
  }

  b->rows = rows_complement->a0;
  b->cols = cols_complement->a0;

  b->cols_total = (int *) malloc(sizeof(int) * (b->cols + 1));
  if (b->cols_total == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for b->cols_total\n",
      sizeof(int) * (b->cols + 1));
    goto b_free;
  }
  matrix_sparse_remove_cols_total(
    b->cols_total, a, rows_complement, cols_complement);

  b_nonzero_max = b->cols_total[b->cols];

  b->row_indices = (int *) malloc(sizeof(int) * b_nonzero_max);
  if (b->row_indices == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for b->row_indices\n",
      sizeof(int) * b_nonzero_max);
    goto b_cols_total_free;
  }
  matrix_sparse_remove_row_indices(
    b->row_indices, a, rows_complement, cols_complement, b->cols_total);

  b->values = (double *) malloc(sizeof(double) * b_nonzero_max);
  if (b->values == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for b->values\n",
      sizeof(double) * b_nonzero_max);
    goto b_row_indices_free;
  }
  matrix_sparse_remove_values(b->values, a, rows_complement, cols_complement,
                              b->cols_total, b->row_indices);

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

matrix_sparse * matrix_sparse_restrict_symmetric(
  const matrix_sparse * a, const jagged1 * rows_complement)
{
  return matrix_sparse_restrict(a, rows_complement, rows_complement);
}

matrix_sparse * matrix_sparse_remove(
  const matrix_sparse * a, const jagged1 * rows, const jagged1 * cols)
{
  matrix_sparse * b = NULL;
  jagged1 * rows_complement, * cols_complement;

  rows_complement = jagged1_complement(a->rows, rows);
  if (rows_complement == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate rows_complement\n", stderr);
    goto end;
  }

  cols_complement = jagged1_complement(a->cols, cols);
  if (cols_complement == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate cols_complement\n", stderr);
    goto rows_complement_free;
  }

  b = matrix_sparse_restrict(a, rows_complement, cols_complement);
  if (b == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate b\n", stderr);
    goto cols_complement_free;
  }

cols_complement_free:
  jagged1_free(cols_complement);
rows_complement_free:
  jagged1_free(rows_complement);
end:
  return b;
}

matrix_sparse * matrix_sparse_remove_symmetric(
  const matrix_sparse * a, const jagged1 * rows)
{
  matrix_sparse * b = NULL;
  jagged1 * rows_complement;

  rows_complement = jagged1_complement(a->rows, rows);
  if (rows_complement == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate rows_complement\n", stderr);
    goto end;
  }
  b = matrix_sparse_restrict_symmetric(a, rows_complement);
  if (b == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate b\n", stderr);
    goto rows_complement_free;
  }

rows_complement_free:
  jagged1_free(rows_complement);
end:
  return b;
}
