#include <stdio.h>

#include "cmc_error_message.h"

void cmc_error_message_variable_int(int n)
{
  fprintf(stderr, "%s%d%s", color_yellow, n, color_none);
}
