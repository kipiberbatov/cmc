#include <stdlib.h>

#include "cmc_error_message.h"
#include "matrix_sparse.h"

matrix_sparse ** matrix_sparse_array_file_scan(
  FILE * in, int n, const char * format)
{
  int i;
  matrix_sparse ** a;

  a = (matrix_sparse **) malloc(sizeof(matrix_sparse *) * n);
  if (a == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(matrix_sparse *) * n, "a");
    return NULL;
  }

  for (i = 0; i < n; ++i)
  {
    a[i] = matrix_sparse_file_scan(in, format);
    if (a[i] == NULL)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot scan a[%d] in format %s\n", i, format);
      matrix_sparse_array_free(a, i);
      return NULL;
    }
  }

  return a;
}
