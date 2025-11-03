#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "matrix_sparse.h"

matrix_sparse * matrix_sparse_file_scan_by_name(
  const char * name, const char * format)
{
  FILE * in;
  matrix_sparse * a = NULL;

  in = fopen(name, "r");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open file %s%s%s: %s%s%s\n",
      color_variable, name, color_none,
      color_stdlib, strerror(errno), color_none);
    goto end;
  }

  a = matrix_sparse_file_scan(in, format);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan sparse matrix in format %s%s%s\n",
      color_variable, name, color_none);
    goto in_close;
  }

in_close:
  fclose(in);
end:
  return a;
}
