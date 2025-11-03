#include <stdio.h>

#include "cmc_error_message.h"
#include "cmc_rgb.h"

void cmc_rgb_check_color_scheme_rainbow(int * status, int n)
{
  if (n % cmc_rgb_color_scheme_rainbow_regions_size)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "the number of total colors (%s%d%s) "
      "is not divisible by the number of color regions (%s%d%s)\n",
      color_variable, n, color_none,
      color_variable, cmc_rgb_color_scheme_rainbow_regions_size, color_none);
    *status = 1;
  }
}
