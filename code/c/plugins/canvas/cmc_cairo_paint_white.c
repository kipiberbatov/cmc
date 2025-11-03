#include <stdio.h>

#include "cmc_error_message.h"
#include "cmc_cairo.h"

void cmc_cairo_paint_white(cairo_t * cr, int * status)
{
  cairo_save(cr);
  cairo_set_source_rgb(cr, 1, 1, 1);
  cairo_paint(cr);
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
