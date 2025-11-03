#include <math.h>
#include <stdio.h>

#include "cmc_error_message.h"
#include "cmc_cairo.h"
#include "cmc_graphics_rectangle.h"
#include "cmc_rgb.h"

/* must use get_color along with cmc_rgb */
void cmc_cairo_graphics_rectangle_draw(
  cairo_t * cr, int * status, const struct cmc_graphics_rectangle * rectangle,
  void (*get_color)(struct cmc_rgb *, const void *))
{
  double height, width, x, y;
  struct cmc_rgb color;

  x = rectangle->x;
  y = rectangle->y;
  width = rectangle->width;
  height = rectangle->height;
  get_color(&color, rectangle->color);

  cairo_save(cr);
  cairo_set_source_rgb(cr, color.red, color.green, color.blue);
  cairo_rectangle(cr, x, y, width, height);
  cairo_fill(cr);
  cairo_stroke(cr);
  cairo_restore(cr);
  *status = cairo_status(cr);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot render with Cairo: %s\n",
      cairo_status_to_string(*status));
    return;
  }
}
