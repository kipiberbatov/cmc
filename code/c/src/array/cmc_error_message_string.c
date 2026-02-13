#include <stdio.h>

#include "cmc_error_message.h"

void cmc_error_message_string(const char * s)
{
  fputs(s, stderr);
}
