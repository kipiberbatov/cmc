#include "cmc_command_line.h"

void cmc_command_line_bind(
  cmc_command_line ** options,
  cmc_command_line * options_list,
  int size)
{
  int i;

  for (i = 0; i < size; ++i)
    options[i] = options_list + i;
}
