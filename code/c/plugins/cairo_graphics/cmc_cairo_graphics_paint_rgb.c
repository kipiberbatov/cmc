#include <stdio.h>

#include "cmc_error_message.h"
#include "cmc_cairo_graphics.h"
#include "cmc_rgb.h"

void
cmc_cairo_graphics_paint_rgb(cairo_t * cr, int * status, const struct cmc_rgb * color)
{
  cairo_save(cr);
  cairo_set_source_rgb(cr, color->red, color->green, color->blue);
  cairo_paint(cr);
  cairo_restore(cr);
  *status = cairo_status(cr);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot draw with Cairo: %s\n",
      cairo_status_to_string(*status));
    return;
  }
}
