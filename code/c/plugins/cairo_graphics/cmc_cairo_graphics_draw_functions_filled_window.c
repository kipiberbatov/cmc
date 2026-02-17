#include <stdlib.h>

#include "cmc_cairo_graphics.h"
#include "cmc_rgb.h"
#include "cmc_graphics_filled_window_draw_functions.h"

const struct cmc_graphics_filled_window_draw_functions
cmc_cairo_graphics_draw_functions_filled_window =
{
  (void (*)(void **, int *)) cmc_rgb_allocate_color,
  free,
  (void (*)(void *, int *, int, int)) cmc_rgb_set_from_scheme_rainbow,
  (void (*)(void *, int *, const void *)) cmc_cairo_graphics_paint_rgb
};
