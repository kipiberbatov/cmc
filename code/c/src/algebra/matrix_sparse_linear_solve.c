#include <errno.h>
#include <string.h>

#include "cmc_error_message.h"
#include "matrix_sparse_private.h"

void matrix_sparse_linear_solve(
  const matrix_sparse * a, double * b, const char * method)
{
  if (!strcmp(method, "--cholesky"))
    matrix_sparse_linear_solve_cholesky(a, b);
  else if (!strcmp(method, "--lu"))
    matrix_sparse_linear_solve_lu(a, b);
  else
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "method %s is not supported\n", method);
    errno = EINVAL;
    return;
  }

  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot solve linear system using method %s\n", method);
  }
}
