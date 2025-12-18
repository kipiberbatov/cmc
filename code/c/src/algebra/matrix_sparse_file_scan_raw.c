#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "int.h"
#include "matrix_sparse_private.h"

static int matrix_sparse_cols_total_possible(
  int m, int n, const int * a_cols_total)
{
  int i;

  if (a_cols_total[0] != 0)
    return 0;
  if (a_cols_total[n] > m * n)
    return 0;
  for (i = 0; i < n; ++i)
    if (a_cols_total[i + 1] < a_cols_total[i])
      return 0;
  return 1;
}

static int all_values_in_range(int length, const int * a, int begin, int end)
{
  int i;

  for (i = 0; i < length; ++i)
    if (a[i] < begin || a[i] >= end)
      return 0;
  return 1;
}

static int all_values_different(int length, const int * a)
{
  int i, j;

  for (i = 0; i < length - 1; ++i)
    for (j = i + 1; j < length; ++j)
      if (a[i] == a[j])
        return 0;
  return 1;
}

static int matrix_sparse_row_indices_possible(
  int m, int n, const int * a_cols_total, const int * a_row_indices)
{
  int i, length;
  const int * b;

  for (i = 0; i < n; ++i)
  {
    length = a_cols_total[i + 1] - a_cols_total[i];
    b = a_row_indices + a_cols_total[i];
    if (!all_values_in_range(length, b, 0, m))
      return 0;
    if (!all_values_different(length, b))
      return 0;
  }
  return 1;
}

matrix_sparse * matrix_sparse_file_scan_raw(FILE * in)
{
  matrix_sparse * a;

  a = (matrix_sparse *) malloc(sizeof(matrix_sparse));
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for a\n",
      sizeof(matrix_sparse));
    goto end;
  }

  a->rows = int_file_scan(in);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan a->rows\n", stderr);
    goto a_free;
  }
  if (a->rows <= 0)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "a->rows = %d but it must be positive\n", a->rows);
    errno = EINVAL;
    goto a_free;
  }

  a->cols = int_file_scan(in);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan a->cols\n", stderr);
    goto a_free;
  }
  if (a->cols <= 0)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "a->cols = %d but it must be positive\n", a->cols);
    errno = EINVAL;
    goto a_free;
  }

  a->cols_total = int_array_file_scan(in, a->cols + 1, "--raw");
  if (a->cols_total == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan a->cols_total in format --raw\n", stderr);
    goto a_free;
  }
  if(!matrix_sparse_cols_total_possible(a->rows, a->cols, a->cols_total))
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("the value of a->cols_total is impossible\n", stderr);
    errno = EINVAL;
    goto a_cols_total_free;
  }

  a->row_indices = int_array_file_scan(in, a->cols_total[a->cols], "--raw");
  if (a->row_indices == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan a->row_indices in format --raw\n", stderr);
    goto a_cols_total_free;
  }
  if (!matrix_sparse_row_indices_possible(
    a->rows, a->cols, a->cols_total, a->row_indices))
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("the value of a->row_indices is impossible\n", stderr);
    errno = EINVAL;
    goto a_row_indices_free;
  }

  a->values = double_array_file_scan(in, a->cols_total[a->cols], "--raw");
  if (a->values == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan a->values in format --raw\n", stderr);
    goto a_row_indices_free;
  }
  /* there are no constraints on a->values */

  return a;

  /* cleaning if an error occurs */
a_row_indices_free:
  free(a->row_indices);
a_cols_total_free:
  free(a->cols_total);
a_free:
  free(a);
end:
  return NULL;
}
