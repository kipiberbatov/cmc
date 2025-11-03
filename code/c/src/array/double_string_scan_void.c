#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "double.h"

void double_string_scan_void(void * result, int * status, const char * s)
{
  char * ptr;

  *((double *) result) = (double) strtod(s, &ptr);
  if (strlen(ptr))
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "%s%s%s is not a valid floating point number\n",
      color_variable, s, color_none);
    *status = 1;
  }
}
