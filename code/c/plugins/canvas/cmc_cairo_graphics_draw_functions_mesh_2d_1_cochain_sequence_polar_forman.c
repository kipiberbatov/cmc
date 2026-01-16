#include <stdlib.h>

#include "cmc_cairo.h"
#include "cmc_graphics_mesh_2d_skeleton.h"
#include "cmc_graphics_mesh_2d_1_cochain_sequence.h"
#include "cmc_graphics_mesh_2d_1_cochain_sequence_draw_functions.h"
#include "cmc_rgb.h"

static void (*draw_curves[2])(void *, int *, const void *) =
{
  (void (*)(void *, int *, const void *)) cmc_cairo_graphics_2d_line_draw,
  (void (*)(void *, int *, const void *)) cmc_cairo_graphics_2d_arc_draw,
};

const struct cmc_graphics_mesh_2d_1_cochain_sequence_draw_functions
cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence_polar_forman =
{
  (void (*)(void **, int *)) cmc_rgb_allocate_color,
  free,
  (void (*)(void *, int *)) cmc_cairo_paint_white,
  cmc_graphics_mesh_2d_1_cochain_sequence_draw_values_polar_forman,
  cmc_rgb_check_color_scheme_rainbow,
  (void (*)(void *, int , int)) cmc_rgb_set_from_scheme_rainbow_no_checks,
  (void (*)(void *, int *, const struct cmc_graphics_mesh_2d_edge *,
    void (*)(void *, const void *)))
    cmc_cairo_graphics_mesh_2d_edge_oriented_draw,
  (void (*)(void *, const void *)) cmc_rgb_get_color_rgb,
  cmc_graphics_mesh_2d_skeleton_draw_polar_forman,
  draw_curves,
  (void (*)(void *, int *, const struct cmc_graphics_mesh_2d_edge *,
    void (*)(void *, int *, const void *)))
    cmc_cairo_graphics_mesh_2d_edge_black_draw
};
