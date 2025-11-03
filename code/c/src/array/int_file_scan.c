#include <errno.h>

#include "cmc_error_message.h"
#include "int.h"

int int_file_scan(FILE * in)
{
  int a, correct;

  correct = fscanf(in, "%d", &a);
  if (correct <= 0)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    if (correct == 0)
      fputs("input is not a valid integer\n", stderr);
    else
      fputs("there is no number to scan\n", stderr);
    errno = EINVAL;
    return -1;
  }
  return a;
}
