#include "cmc_cairo_graphics.h"
#include "line_2d.h"

void cmc_cairo_graphics_2d_line_draw(
  cairo_t * cr, int * status, const struct line_2d * line)
{
  cairo_move_to(cr, line->x0[0], line->x0[1]);
  cairo_line_to(cr, line->x1[0], line->x1[1]);
  cairo_stroke(cr);
}
