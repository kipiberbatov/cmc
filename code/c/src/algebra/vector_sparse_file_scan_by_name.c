#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "vector_sparse.h"

vector_sparse * vector_sparse_file_scan_by_name(
  const char * name, const char * format)
{
  FILE * in;
  vector_sparse * a = NULL;

  in = fopen(name, "r");
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot open file %s%s%s: %s\n",
      color_variable, name, color_none, strerror(errno));
    goto end;
  }

  a = vector_sparse_file_scan(in, format);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan a in format %s%s%s: %s\n",
      color_variable, format, color_none, strerror(errno));
    goto in_close;
  }

in_close:
  fclose(in);
end:
  return a;
}
