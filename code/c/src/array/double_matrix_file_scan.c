#include <errno.h>
#include <string.h>

#include "cmc_error_message.h"
#include "double_array_private.h"
#include "double_matrix.h"
#include "double_matrix_private.h"

double * double_matrix_file_scan(FILE * in, int m, int n, const char * format)
{
  double * a;

  if (!strcmp(format, "--raw"))
    a = double_matrix_file_scan_raw(in, m, n);
  else if (!strcmp(format, "--steady-state-mixed-weak-solution-flow-rate-raw"))
    a = double_array_file_scan_steady_state_primal_weak_raw(in, m * n);
  else
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "format %s is not supported\n", format);
    errno = EINVAL;
    return NULL;
  }

  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan input matrix\n", stderr);
  }
  return a;
}
