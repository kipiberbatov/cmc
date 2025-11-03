#include "cmc_error_message.h"
#include "matrix_sparse.h"

matrix_sparse * matrix_sparse_add(
  const matrix_sparse * a, const matrix_sparse * b)
{
  matrix_sparse * c;

  c = matrix_sparse_linear_combination(a, b, 1., 1.);
  if (c == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot add matrices\n", stderr);
  }
  return c;
}
