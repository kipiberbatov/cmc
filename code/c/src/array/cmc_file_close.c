#include "cmc_file_close.h"
#include "cmc_error_message.h"

void cmc_file_close(FILE * out, int * status)
{
  *status = fclose(out);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_string("cannot close file\n");
  }
}
