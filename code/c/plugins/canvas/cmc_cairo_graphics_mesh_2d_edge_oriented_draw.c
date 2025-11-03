#include <math.h>
#include <stdio.h>

#include "cmc_error_message.h"
#include "cmc_cairo.h"
#include "cmc_graphics_mesh_2d_edge.h"
#include "cmc_rgb.h"
#include "line_2d.h"

void cmc_cairo_graphics_mesh_2d_edge_oriented_draw(
  cairo_t * cr, int * status, const struct cmc_graphics_mesh_2d_edge * edge,
  void (*get_color)(struct cmc_rgb *, const void *))
{
  double width;
  struct line_2d * line;
  struct cmc_rgb color;

  width = edge->width;
  line = (struct line_2d *) edge->data;
  get_color(&color, edge->color);

  cairo_save(cr);
  cairo_set_source_rgb(cr, color.red, color.green, color.blue);
  cairo_set_line_width(cr, width);
  cairo_move_to(cr, line->x0[0], line->x0[1]);
  cairo_line_to(cr, line->x1[0], line->x1[1]);
  cairo_stroke(cr);
  cairo_arc(cr, line->x1[0], line->x1[1], width, 0, 2 * M_PI);
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
