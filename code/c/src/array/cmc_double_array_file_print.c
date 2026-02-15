#include <errno.h>

#include "cmc_double_array__struct.h"
#include "cmc_double_array_file_print.h"
#include "cmc_error_message.h"
#include "double_array.h"

void cmc_double_array_file_print(
  FILE * out,
  int * status,
  const struct cmc_double_array * data,
  const char * format)
{
  double_array_file_print(
    out, data->size, data->values, format);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_string("cannot print data\n");
    *status = errno;
  }
}
