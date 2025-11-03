#include <errno.h>

#include "cmc_error_message.h"
#include "matrix_sparse.h"

static void matrix_sparse_part_file_print(FILE * out, const matrix_sparse * a)
{
  int i, j;
  double k;

  for (i = 0; i < a->rows; ++i)
  {
    for (j = 0; j < a->cols - 1; ++j)
    {
      k = matrix_sparse_part(a, i, j);
      fprintf(out, "%g ", k);
    }
    k = matrix_sparse_part(a, i, j);
    fprintf(out, "%g\n", k);
  }
}

int main(void)
{
  matrix_sparse * a;
  FILE * in, * out;

  out = stdout;
  in = stdin;
  a = matrix_sparse_file_scan(in, "--raw");
  if (a == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan matrix a in format --raw\n", stderr);
    return errno;
  }
  matrix_sparse_part_file_print(out, a);
  matrix_sparse_free(a);
  return errno;
}
