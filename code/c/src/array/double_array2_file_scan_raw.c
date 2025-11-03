#include <stdlib.h>

#include "cmc_error_message.h"
#include "double_array_private.h"
#include "double_array2.h"
#include "double_array2_private.h"

double ** double_array2_file_scan_raw(FILE * in, int a0, const int * a1)
{
  int i;
  double ** a;

  a = (double **) malloc(sizeof(double *) * a0);
  if (a == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double *) * a0, "a");
    return NULL;
  }
  for (i = 0; i < a0; ++i)
  {
    a[i] = double_array_file_scan_raw(in, a1[i]);
    if (a[i] == NULL)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot scan a[%d] in format --raw\n", i);
      double_array2_free(a, i);
      return NULL;
    }
  }
  return a;
}
