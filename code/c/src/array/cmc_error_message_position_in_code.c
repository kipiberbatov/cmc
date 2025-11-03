#include <stdio.h>

#include "cmc_error_message.h"

void cmc_error_message_position_in_code(const char * file, int line)
{
  fprintf(stderr, "%s%s%s:%s%d%s: %s%s%s: ",
    color_bright_cyan, file, color_none,
    color_yellow, line, color_none,
    color_red, "error", color_none);
}
