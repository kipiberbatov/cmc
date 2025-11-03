#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "matrix_sparse.h"

int main(int argc, char ** argv)
{
  char * a_format, * a_name, * out_format;
  matrix_sparse * a, * b;

#define ARGC 4
  if (argc != ARGC)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_number_of_command_line_arguments_mismatch(ARGC, argc);
    return EINVAL;
  }

  a_format = argv[1];
  a_name = argv[2];
  out_format = argv[3];

  a = matrix_sparse_file_scan_by_name(a_name, a_format);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan input matrix from file %s in format %s\n",
      a_name, a_format);
    goto end;
  }

  b = matrix_sparse_copy(a);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot copy input matrix\n", stderr);
    goto a_free;
  }

  matrix_sparse_file_print(stdout, b, out_format);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot print matrix copy in format %s\n", out_format);
    goto b_free;
  }

b_free:
  matrix_sparse_free(b);
a_free:
  matrix_sparse_free(a);
end:
  return errno;
}
