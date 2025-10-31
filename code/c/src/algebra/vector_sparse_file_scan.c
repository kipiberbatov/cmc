#include <errno.h>
#include <string.h>

#include "color.h"
#include "vector_sparse_private.h"

vector_sparse * vector_sparse_file_scan(FILE * in, const char * format)
{
  vector_sparse * a;

  if (!strcmp(format, "--raw"))
    a = vector_sparse_file_scan_raw(in);
  else
  {
    color_error_position(__FILE__, __LINE__);
    errno = EINVAL;
    fprintf(stderr, "format %s%s%s is not supported\n",
      color_variable, format, color_none);
    return NULL;
  }

  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot scan input\n", stderr);
  }
  return a;
}
