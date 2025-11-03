#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "matrix_sparse.h"


static void matrix_sparse_constrained_solve_cholesky_file_print(
  FILE * out, const matrix_sparse * a, const double * b, const jagged1 * rows)
{
  double * x;

  x = matrix_sparse_constrained_solve_cholesky(a, b, rows);
  if (x == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot find x\n", stderr);
    return;
  }
  fprintf(out, "%d\n", a->rows);
  double_array_file_print(out, a->rows, x, "--raw");
  free(x);
}

int main(void)
{
  int b_m, status;
  double * b;
  jagged1 * rows;
  matrix_sparse * a;
  FILE * in, * out;

  out = stdout;
  in = stdin;
  status = fscanf(in, "%d", &b_m);
  if (status != 1)
    return EINVAL;

  b = double_array_file_scan(in, b_m, "--raw");
  if (b == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan right-hand side b\n", stderr);
    goto end;
  }

  rows = jagged1_file_scan(in, "--raw");
  if (rows == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan rows for deletion in format --raw\n", stderr);
    goto b_free;
  }

  a = matrix_sparse_file_scan(in, "--raw");
  if (a == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan left-hand side a in format --raw\n", stderr);
    goto rows_free;
  }

  matrix_sparse_constrained_solve_cholesky_file_print(out, a, b, rows);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot restrict, solve and print\n", stderr);
    goto a_free;
  }

a_free:
  matrix_sparse_free(a);
rows_free:
  jagged1_free(rows);
b_free:
  free(b);
end:
  return errno;
}
