#include "cmc_error_message.h"
#include "cmc_file_close.h"
#include "cmc_file_close_output_channel.h"

void cmc_file_close_output_channel(FILE * out, int * status)
{
  if (out != stdout)
  {
    cmc_file_close(out, status);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      cmc_error_message_string("cannot close output channel\n");
    }
  }
}
