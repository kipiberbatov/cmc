#include "cmc_cairo_graphics.h"
#include "cmc_graphics_mesh_2d_skeleton.h"
#include "cmc_graphics_mesh_2d_skeleton_draw_functions.h"

static void (*draw_curves[2])(void *, int *, const void *) =
{
  (void (*)(void *, int *, const void *)) cmc_cairo_graphics_2d_line_draw,
  (void (*)(void *, int *, const void *)) cmc_cairo_graphics_2d_arc_draw
};

const struct cmc_graphics_mesh_2d_skeleton_draw_functions
cmc_cairo_graphics_draw_functions_mesh_2d_skeleton_polar =
{
  cmc_graphics_mesh_2d_skeleton_draw_polar,
  draw_curves,
  (void (*)(void *, int *, const struct cmc_graphics_mesh_2d_edge *,
    void (*)(void *, int *, const void *)))
    cmc_cairo_graphics_mesh_2d_edge_black_draw
};
