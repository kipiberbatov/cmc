#include <stdio.h>

#include "cmc_error_message.h"

void cmc_error_message_cannot_calculate(const char * name)
{
  fprintf(stderr,
    "cannot calculate variable %s%s%s\n",
    color_variable, name, color_none);
}
