#include <stdlib.h>

#include "cmc_cairo_graphics.h"
#include "cmc_graphics_colorbar.h"
#include "cmc_graphics_colorbar_draw_functions.h"
#include "cmc_rgb.h"

struct cmc_graphics_rectangle;

const struct cmc_graphics_colorbar_draw_functions
cmc_cairo_graphics_draw_functions_colorbar =
{
  (void (*)(void **, int *)) cmc_rgb_allocate_color,
  free,
  cmc_graphics_colorbar_draw_rectangles,
  cmc_rgb_check_color_scheme_rainbow,
  (void (*)(void *, int , int)) cmc_rgb_set_from_scheme_rainbow_no_checks,
  (void (*)(void *, int *, const struct cmc_graphics_rectangle *,
    void (*)(void *, const void *))) cmc_cairo_graphics_rectangle_draw,
  (void (*)(void *, const void *)) cmc_rgb_get_color_rgb
};
