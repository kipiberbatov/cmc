#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "int.h"

void int_string_scan_void(void * result, int * status, const char * s)
{
  char * ptr;

  if (*s == 0)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("empty string is not a valid integer\n", stderr);
    *status = 1;
  }

  *((int *) result) = (int) strtol(s, &ptr, 10);
  if (strlen(ptr))
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "%s%s%s is not a valid integer\n",
      color_variable, s, color_none);
    *status = 1;
  }
}
