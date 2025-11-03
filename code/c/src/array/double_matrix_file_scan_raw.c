#include <stdlib.h>

#include "cmc_error_message.h"
#include "double_array_private.h"
#include "double_matrix_private.h"

double * double_matrix_file_scan_raw(FILE * in, int m, int n)
{
  double * a;

  a = double_array_file_scan_raw(in, m * n);
  if (a == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan matrix as an array of length %d\n", m * n);
    return NULL;
  }
  return a;
}
