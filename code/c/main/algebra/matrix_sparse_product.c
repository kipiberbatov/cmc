#include <errno.h>

#include "cmc_error_message.h"
#include "matrix_sparse.h"

int main(int argc, char ** argv)
{
  char * a_format, * a_name, * b_format, * b_name, * out_format;
  matrix_sparse * a, * b, * c;

#define ARGC 6
  if (argc != ARGC)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_number_of_command_line_arguments_mismatch(ARGC, argc);
    errno = EIO;
    goto end;
  }

  a_name = argv[1];
  a_format = argv[2];
  a = matrix_sparse_file_scan_by_name(a_name, a_format);
  if (a == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan the first matrix a from file %s in format %s\n",
      a_name, a_format);
    goto end;
  }

  b_name = argv[3];
  b_format = argv[4];
  b = matrix_sparse_file_scan_by_name(b_name, b_format);
  if (b == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan the second matrix b from file %s in format %s\n",
      b_name, b_format);
    goto a_free;
  }

  c = matrix_sparse_product(a, b);
  if (c == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate the matrix product c = a . b\n", stderr);
    goto b_free;
  }

  out_format = argv[5];
  matrix_sparse_file_print(stdout, c, out_format);

  matrix_sparse_free(c);
b_free:
  matrix_sparse_free(b);
a_free:
  matrix_sparse_free(a);
end:
  return errno;
}
