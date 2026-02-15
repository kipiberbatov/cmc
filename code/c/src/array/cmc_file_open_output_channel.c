#include "cmc_error_message.h"
#include "cmc_file_open.h"
#include "cmc_file_open_output_channel.h"

void cmc_file_open_output_channel(
  FILE ** out, int * status, const char * name)
{
  if (name == NULL)
    *out = stdout;
  else
  {
    cmc_file_open(out, status, name, "w");
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      cmc_error_message_string("cannot open output file\n");
    }
  }
}
