#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "double_matrix.h"

double * double_matrix_file_scan_by_name(
  const char * name, int m, int n, const char * format)
{
  FILE * in;
  double * a = NULL;

  in = fopen(name, "r");
  if (in == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot open file %s: %s\n", name, strerror(errno));
    goto end;
  }

  a = double_matrix_file_scan(in, m, n, format);
  if (a == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan matrix a from file %s in format %s\n",
      name, format);
    goto in_close;
  }

in_close:
  fclose(in);
end:
  return a;
}
