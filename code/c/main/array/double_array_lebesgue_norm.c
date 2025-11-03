#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "cmc_command_line.h"

int main(int argc, char ** argv)
{
  char * a_format, * a_name, * output_name;
  int n, size, status;
  double p, result;
  const double p_default = 2.;
  double * a;
  FILE * output;

  cmc_command_line
    option_a_format, option_a_name, option_n, option_no_positional_arguments,
    option_output_name, option_p;

  cmc_command_line *(options[]) =
  {
    &option_a_format,
    &option_a_name,
    &option_n,
    &option_p,
    &option_output_name,
    &option_no_positional_arguments
  };

  cmc_command_line_set_option_int(&option_n, &n, "--size", NULL);

  cmc_command_line_set_option_double(
    &option_p, &p, "--norm-order", &p_default);

  cmc_command_line_set_option_string(
    &option_a_format, &a_format, "--vector-format", "--raw");

  cmc_command_line_set_option_string(
    &option_a_name, &a_name, "--vector", NULL);

  cmc_command_line_set_option_string(
    &option_output_name, &output_name, "--output", NULL);

  /* there are no positional arguments */
  cmc_command_line_set_option_no_arguments(
    &option_no_positional_arguments, NULL, NULL, NULL);

  size = (int) (sizeof(options) / sizeof(*options));
  status = 0;
  cmc_command_line_parse(options, &status, size, argc, argv);
  if (status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot parse command line options\n", stderr);
    return status;
  }

  if (n < 0)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "the vector length is %s%d%s but it must be at least 0\n",
      color_variable, n, color_none);
    status = 1;
    goto end;
  }

  if (p < 0)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "the order of the l^p norm is %s%d%s but it must be at least 0\n",
      color_variable, n, color_none);
    status = 1;
    goto end;
  }

  a = double_array_file_scan_by_name(a_name, n, a_format);
  if (a == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan array of size %s%d%s from file %s%s%s in format %s%s%s\n",
      color_variable, n, color_none,
      color_variable, a_name, color_none,
      color_variable, a_format, color_none);
    status = errno;
    goto end;
  }

  result = double_array_lebesgue_norm(p, n, a);
  free(a);

  output = fopen(output_name, "w");
  if (output == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open file %s%s%s for writing\n",
      color_variable, output_name, color_none);
    status = errno;
    goto end;
  }

  fprintf(output, "%g\n", result);

  fclose(output);
end:
  return status;
}
