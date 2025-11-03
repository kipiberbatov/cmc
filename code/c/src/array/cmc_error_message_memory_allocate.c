#include <stdio.h>

#include "cmc_error_message.h"

void cmc_error_message_memory_allocate(const char * name)
{
  fprintf(stderr,
    "cannot allocate memory for variable %s%s%s\n",
    color_variable, name, color_none);
}
