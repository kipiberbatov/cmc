#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "double.h"
#include "cmc_command_line.h"

static void
double_file_scan_by_name(double * a, int * status, const char * name)
{
  FILE * in;

  in = fopen(name, "r");
  if (in == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open file %s%s%s for reading\n",
      color_variable, name, color_none);
    *status = errno;
    return;
  }

  *a = double_file_scan(in);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot read a 64-bit float from file %s%s%s\n",
      color_variable, name, color_none);
    *status = errno;
  }
  fclose(in);
}

int main(int argc, char ** argv)
{
  char * a_name, * b_name, * output_name;
  int size, status;
  double a, b = 0.;
  FILE * output;

  cmc_command_line
    option_a_name, option_b_name, option_no_positional_arguments,
    option_output_name;

  cmc_command_line *(options[]) =
  {
    &option_a_name,
    &option_b_name,
    &option_output_name,
    &option_no_positional_arguments
  };

  cmc_command_line_set_option_string(
    &option_a_name, &a_name, "--numerator", NULL);

  cmc_command_line_set_option_string(
    &option_b_name, &b_name, "--denominator", NULL);

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

  double_file_scan_by_name(&a, &status, a_name);
  if (status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot read numerator\n", stderr);
    return status;
  }

  double_file_scan_by_name(&b, &status, b_name);
  if (status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot read denominator\n", stderr);
    return status;
  }

  if (b == 0)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("the denominator cannot be 0\n", stderr);
    status = 1;
    return status;
  }

  output = fopen(output_name, "w");
  if (output == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open file %s%s%s for writing\n",
      color_variable, output_name, color_none);
    status = errno;
    return status;
  }
  fprintf(output, "%g\n", a / b);
  fclose(output);

  return status;
}
