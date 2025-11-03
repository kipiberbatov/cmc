#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "matrix_sparse.h"

/* read a sparse matrix and vector from a file, multiply and print them */
int main(int argc, char ** argv)
{
  char * a_name, * x_name;
  int m, n;
  double * x, * y;
  matrix_sparse * a;

#define ARGC 3
  if (argc != ARGC)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_number_of_command_line_arguments_mismatch(ARGC, argc);
    return EINVAL;
  }

  a_name = argv[1];
  x_name = argv[2];

  a = matrix_sparse_file_scan_by_name(a_name, "--raw");
  if (a == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan sparse matrix a from file %s in format --raw\n",
      a_name);
    goto end;
  }

  m = a->rows;
  n = a->cols;

  x = double_array_file_scan_by_name(x_name, n, "--raw");
  if (x == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan vector x of length %d from file %s in format --raw\n",
      n, x_name);
    goto a_free;
  }

  y = (double *) calloc(m, sizeof(double));
  if (y == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m, "y");
    goto x_free;
  }

  matrix_sparse_vector_multiply_add(y, a, x);
  double_array_file_print(stdout, m, y, "--raw");

  free(y);
x_free:
  free(x);
a_free:
  free(a);
end:
  return errno;
}
