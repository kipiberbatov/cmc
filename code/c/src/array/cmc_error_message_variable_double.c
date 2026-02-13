#include <stdio.h>

#include "cmc_error_message.h"

void cmc_error_message_variable_double(double x)
{
  fprintf(stderr, "%s%f%s", color_yellow, x, color_none);
}
