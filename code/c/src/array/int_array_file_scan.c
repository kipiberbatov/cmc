#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "int_private.h"

int * int_array_file_scan(FILE * in, int n, const char * format)
{
  int * a;

  if (n == 0)
    return (int *) malloc(sizeof(int));

  if (!strcmp(format, "--raw"))
    a = int_array_file_scan_raw(in, n);
  else
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "format %s is not supported\n", format);
    errno = EINVAL;
    return NULL;
  }

  if (a == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan input in format %s\n", format);
  }
  return a;
}
