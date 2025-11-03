#include <errno.h>
#include <string.h>

#include "cmc_error_message.h"
#include "double.h"

double double_file_scan(FILE * in)
{
  int correct;
  double a;

  correct = fscanf(in, "%lf", &a);
  if (correct <= 0)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    if (correct == 0)
      fputs("input is not a valid 64-bit floating point number: %s\n", stderr);
    else
      fputs("there is no number to scan\n", stderr);
    errno = EINVAL;
    return -1;
  }
  return a;
}
