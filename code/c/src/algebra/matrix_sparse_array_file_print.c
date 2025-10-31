#include <errno.h>
#include <string.h>

#include "color.h"
#include "matrix_sparse.h"

void matrix_sparse_array_file_print(
  FILE * out, int n, matrix_sparse ** a, const char * format)
{
  int i;

  for (i = 0; i < n; ++i)
  {
    matrix_sparse_file_print(out, a[i], format);
    if (errno)
    {
      color_error_position(__FILE__, __LINE__);
      fprintf(stderr,
        "cannot print a[%s%d%s] for reading: %s\n",
        color_variable, i, color_none, strerror(errno));
      return;
    }
    if (i < n - 1)
      fputc('\n', out);
  }
}
