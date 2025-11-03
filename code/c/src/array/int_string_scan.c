#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "int.h"

int int_string_scan(const char * s)
{
  int a;
  char * ptr;

  a = (int) strtol(s, &ptr, 10);
  if (strlen(ptr))
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "%s is not a valid integer\n", s);
    errno = EINVAL;
  }
  return a;
}
