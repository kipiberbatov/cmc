#include <string.h>

#include "cmc_error_message.h"
#include "double_array2_private.h"
#include "double_array2.h"

void double_array2_file_print(FILE * out, int * status,
  int a0, const int * a1, double ** a2, const char * format)
{
  void (*printer)(FILE *, int, const int *, double **);

  if (!strcmp(format, "raw"))
    printer = double_array2_file_print_raw;
  else
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "format %s%s%s is not supported\n",
      color_variable, format, color_none);
    *status = 1;
    return;
  }

  printer(out, a0, a1, a2);
}
