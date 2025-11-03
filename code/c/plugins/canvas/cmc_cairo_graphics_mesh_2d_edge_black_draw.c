#include <stdio.h>

#include "cmc_error_message.h"
#include "cmc_cairo.h"
#include "cmc_graphics_mesh_2d_edge.h"

void cmc_cairo_graphics_mesh_2d_edge_black_draw(
  cairo_t * cr, int * status, const struct cmc_graphics_mesh_2d_edge * edge,
  void (*draw_curve)(cairo_t *, int *, const void *))
{
  cairo_save(cr);
  cairo_set_source_rgb(cr, 0, 0, 0);
  cairo_set_line_width(cr, edge->width);
  draw_curve(cr, status, edge->data);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot draw curve to Cairo context: %s\n",
      cairo_status_to_string(*status));
    return;
  }
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
