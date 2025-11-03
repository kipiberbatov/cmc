#include <stdio.h>

#include "cmc_error_message.h"

void cmc_error_message_number_of_command_line_arguments_mismatch(
  int ARGC, int argc)
{
  fprintf(stderr,
    "the number of command-line arguments must be %s%d%s; "
    "instead it is %s%d%s\n",
    color_variable, ARGC, color_none,
    color_variable, argc, color_none);
}
