#include <errno.h>
#include <string.h>

#include "cmc_error_message.h"
#include "jagged_private.h"

jagged4 * jagged4_file_scan(FILE * in, const char * format)
{
  jagged4 * arr;

  if (!strcmp(format, "--raw"))
    arr = jagged4_file_scan_raw(in);
  else
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    errno = EINVAL;
    fprintf(stderr, "format %s%s%s is not supported\n",
      color_variable, format, color_none);
    return NULL;
  }

  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan arr in format %s%s%s: %s\n",
      color_variable, format, color_none, strerror(errno));
  }
  return arr;
}
