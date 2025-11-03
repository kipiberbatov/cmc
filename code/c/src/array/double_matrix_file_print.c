#include <errno.h>
#include <string.h>

#include "cmc_error_message.h"
#include "double_matrix.h"
#include "double_matrix_private.h"

void double_matrix_file_print(
  FILE * out, int m, int n, const double * a, const char * format)
{
  if (!strcmp(format, "--raw"))
    double_matrix_file_print_raw(out, m, n, a);
  else if (!strcmp(format, "--curly"))
    double_matrix_file_print_curly(out, m, n, a);
  else
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "format %s is not supported\n", format);
    errno = EINVAL;
  }
}
