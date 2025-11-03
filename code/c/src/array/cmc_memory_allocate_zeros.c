#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "cmc_memory.h"

void cmc_memory_allocate_zeros(void ** data, int * status, size_t size)
{
  *data = calloc(size, 1);
  if (*data == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %s%ld%s bytes of zeros\n",
      color_variable, size, color_none);
    *status = ENOMEM;
  }
}
