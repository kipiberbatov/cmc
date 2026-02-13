#include <errno.h>
#include <string.h>

#include "cmc_file_open.h"
#include "cmc_error_message.h"

void
cmc_file_open(FILE ** out, int * status, const char * name, const char * mode)
{
  *out = fopen(name, mode);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_string("cannot open file ");
    cmc_error_message_variable_string(name);
    cmc_error_message_string(" in mode ");
    cmc_error_message_variable_string(mode);
    cmc_error_message_string(": ");
    cmc_error_message_variable_string(strerror(errno));
    cmc_error_message_string("\n");
    *status = errno;
  }
}
