#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "double_array_private.h"
#include "int.h"

double * double_array_file_scan_steady_state_primal_weak_raw(FILE * in, int n)
{
  double * a;

  int_file_scan(in);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan number_of_cells_1\n", stderr);
    return NULL;
  }

  int_file_scan(in);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan number_of_cells_d\n", stderr);
    return NULL;
  }

  a = double_array_file_scan_raw(in, n);
  if (a == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan array of length %s%d%s\n",
      color_variable, n, color_none);
    return NULL;
  }

  return a;
}
