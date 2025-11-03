#include <stdio.h>

#include "cmc_error_message.h"
#include "cmc_rgb.h"

void cmc_rgb_set_from_scheme_rainbow_no_checks(
  struct cmc_rgb * color, int i, int n)
{
  int k_n, k_i, k;
  
  k_n = n / cmc_rgb_color_scheme_rainbow_regions_size;
  k_i = i % k_n;
  k = i / k_n;
  cmc_rgb_color_scheme_rainbow_regions[k](color, k_i, k_n);
}

void cmc_rgb_set_from_scheme_rainbow(
  struct cmc_rgb * color, int * status, int i, int n)
{
  if (n % cmc_rgb_color_scheme_rainbow_regions_size != 0)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "the number of total colors (%s%d%s) "
      "is not divisible by the number of color regions (%s%d%s)\n",
      color_variable, n, color_none,
      color_variable, cmc_rgb_color_scheme_rainbow_regions_size, color_none);
    *status = 1;
    return;
  }
  if (i < 0 || i >= n)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "the color index i = %s%d%s "
      "is not in the interval [0, total_colors - 1] = [0, %s%d%s]\n",
      color_variable, i, color_none,
      color_variable, n - 1, color_none);
    *status = 1;
    return;
  }
  cmc_rgb_set_from_scheme_rainbow_no_checks(color, i, n);
}
