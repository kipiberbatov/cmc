#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "double_array.h"

double * double_array_file_scan_by_name(
  const char * name, int n, const char * format)
{
  FILE * in;
  double * a = NULL;

  in = fopen(name, "r");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot open file %s: %s\n", name, strerror(errno));
    goto end;
  }

  a = double_array_file_scan(in, n, format);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan a in format %s\n", format);
    goto in_close;
  }

in_close:
  fclose(in);
end:
  return a;
}
