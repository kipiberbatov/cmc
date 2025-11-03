#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "matrix_sparse.h"

int main(int argc, char ** argv)
{
  char * a_format, * a_name, * b_name, * method;
  double * b;
  matrix_sparse * a;

#define ARGC 5
  if (argc != ARGC)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_number_of_command_line_arguments_mismatch(ARGC, argc);
    return EINVAL;
  }

  a_name = argv[1];
  a_format = argv[2];
  b_name = argv[3];
  method = argv[4];

  a = matrix_sparse_file_scan_by_name(a_name, a_format);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan matrix a from file %s in format %s\n",
      a_name, a_format);
    goto end;
  }

  b = double_array_file_scan_by_name(b_name, a->rows, "--raw");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot open file %s for reading vector b\n", b_name);
    goto a_free;
  }

  matrix_sparse_linear_solve(a, b, method);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot solve linear system a x = b using method %s\n",
      method);
    goto b_free;
  }

  double_array_file_print(stdout, a->rows, b, "--raw");

b_free:
  free(b);
a_free:
  matrix_sparse_free(a);
end:
  return errno;
}
