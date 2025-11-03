#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "double.h"

double double_string_scan(const char * s)
{
  double a;
  char * ptr;

  a = strtod(s, &ptr);
  if (strlen(ptr))
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "%s is not a valid 64-bit float\n", s);
    errno = EINVAL;
  }
  return a;
}
