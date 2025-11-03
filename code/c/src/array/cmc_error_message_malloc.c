#include <stdio.h>

#include "cmc_error_message.h"

void cmc_error_message_malloc(size_t size, const char * name)
{
  fprintf(stderr,
    "cannot allocate %s%ld%s bytes of memory for variable %s%s%s\n",
    color_variable, size, color_none,
    color_variable, name, color_none);
}
