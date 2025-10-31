#include <stdlib.h>

#include "cmc_error_message.h"
#include "color.h"
#include "double_array.h"
#include "int.h"
#include "matrix_sparse.h"

matrix_sparse * matrix_sparse_identity(int n)
{
  matrix_sparse * a;

  a = (matrix_sparse *) malloc(sizeof(matrix_sparse));
  if (a == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(matrix_sparse), "a");
    goto end;
  }

  a->rows = n;
  a->cols = n;

  a->cols_total = (int *) malloc(sizeof(int) * (n + 1));
  if (a->cols_total == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(int) * (n + 1), "a->cols_total");
    goto a_free;
  }
  int_array_assign_identity(a->cols_total, n + 1);

  a->row_indices = (int *) malloc(sizeof(int) * n);
  if (a->row_indices == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(int) * n, "a->row_indices");
    goto a_cols_total_free;
  }
  int_array_assign_identity(a->row_indices, n);

  a->values = (double *) malloc(sizeof(double) * n);
  if (a->values == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * n, "a->values");
    goto a_row_indices_free;
  }
  double_array_assign_constant(a->values, n, 1.);

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
