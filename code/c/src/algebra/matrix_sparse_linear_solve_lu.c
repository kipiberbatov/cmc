#include <errno.h>
#include <string.h>

#include "cmc_error_message.h"
#include "matrix_sparse_private.h"

void matrix_sparse_linear_solve_lu(const matrix_sparse * a, double * b)
{
  int correct;
  cs a0;

  matrix_sparse_to_cs(&a0, a);
  correct = cs_lusol(1, &a0, b, 1.E-10);
  if (!correct)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot solve linear system\n", stderr);
    errno = EINVAL;
    return;
  }
  else
    errno = 0;
}
