#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "cmc_memory.h"

void cmc_memory_reallocate(void ** new, int * status, void * old, size_t size)
{
  *new = realloc(old, size);
  if (*new == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot reallocate %s%ld%s bytes of memory\n",
      color_variable, size, color_none);
    *status = ENOMEM;
  }
}
