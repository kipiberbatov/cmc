#include <math.h>
#include <stdio.h>

#include "cmc_error_message.h"
#include "cmc_cairo.h"
#include "cmc_graphics_mesh_2d_node.h"
#include "cmc_rgb.h"

/* must use get_color along with cmc_rgb */
void cmc_cairo_graphics_mesh_2d_node_draw(
  cairo_t * cr, int * status, const struct cmc_graphics_mesh_2d_node * node,
  void (*get_color)(struct cmc_rgb *, const void *))
{
  double r;
  double * x;
  struct cmc_rgb color;

  r = node->size;
  x = node->coordinates;
  get_color(&color, node->color);

  cairo_save(cr);
  cairo_set_source_rgb(cr, color.red, color.green, color.blue);
  cairo_arc(cr, x[0], x[1], r, 0, 2 * M_PI);
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
