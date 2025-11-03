#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "double.h"
#include "matrix_sparse.h"

int main(int argc, char ** argv)
{
  char * a_format, * a_name, * alpha_name, * b_format, * b_name, * beta_name,
       * out_format;
  double alpha, beta;
  matrix_sparse * a, * b, * c;

#define ARGC 8
  if (argc != ARGC)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_number_of_command_line_arguments_mismatch(ARGC, argc);
    return EINVAL;
  }

  a_name = argv[1];
  a_format = argv[2];
  b_name = argv[3];
  b_format = argv[4];
  alpha_name = argv[5];
  beta_name = argv[6];
  out_format = argv[7];

  alpha = double_string_scan(alpha_name);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan alpha from string %s\n", alpha_name);
    goto end;
  }

  beta = double_string_scan(beta_name);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan beta from string %s\n", beta_name);
    goto end;
  }

  a = matrix_sparse_file_scan_by_name(a_name, a_format);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan matrix a from file %s in format %s\n",
      a_name, a_format);
    goto end;
  }

  b = matrix_sparse_file_scan_by_name(b_name, b_format);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan matrix b from file %s in format %s\n",
      b_name, b_format);
    goto a_free;
  }

  c = matrix_sparse_linear_combination(a, b, alpha, beta);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot calculate c = %g a + %g b\n", alpha, beta);
    goto b_free;
  }

  matrix_sparse_file_print(stdout, c, out_format);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot print c in format %s\n", out_format);
    goto c_free;
  }

c_free:
  matrix_sparse_free(c);
b_free:
  matrix_sparse_free(b);
a_free:
  matrix_sparse_free(a);
end:
  return errno;
}
