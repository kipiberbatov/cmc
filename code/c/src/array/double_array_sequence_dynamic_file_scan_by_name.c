#include <errno.h>
#include <string.h>

#include "cmc_error_message.h"
#include "double_array_sequence_dynamic.h"

double_array_sequence_dynamic *
double_array_sequence_dynamic_file_scan_by_name(const char * name)
{
  FILE * in;
  double_array_sequence_dynamic * a;

  in = fopen(name, "r");
  if (in == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open file %s%s%s: %s\n",
      color_variable, name, color_none, strerror(errno));
    return NULL;
  }

  a = double_array_sequence_dynamic_file_scan(in);
  if (a == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan file %s%s%s\n",
      color_variable, name, color_none);
    goto in_close;
  }

in_close:
  fclose(in);
  return a;
}
