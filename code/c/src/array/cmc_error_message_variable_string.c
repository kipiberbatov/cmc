#include <stdio.h>

#include "cmc_error_message.h"

void cmc_error_message_variable_string(const char  *s)
{
  fprintf(stderr, "%s%s%s", color_yellow, s, color_none);
}
