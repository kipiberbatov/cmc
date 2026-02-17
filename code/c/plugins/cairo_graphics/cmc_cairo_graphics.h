#ifndef _cmc_cairo_h
#define _cmc_cairo_h

#include <cairo.h>

struct arc_2d;
struct cmc_graphics_mesh_2d_edge;
struct cmc_graphics_mesh_2d_node;
struct cmc_graphics_rectangle;
struct cmc_rgb;
struct line_2d;

void cmc_cairo_graphics_paint_white(cairo_t * cr, int * status);

void
cmc_cairo_graphics_paint_rgb(cairo_t * cr, int * status, const struct cmc_rgb * color);

void cmc_cairo_graphics_2d_line_draw(
  cairo_t * cr, int * status, const struct line_2d * line);

void cmc_cairo_graphics_2d_arc_draw(
  cairo_t * cr, int * status, const struct arc_2d * arc);

void cmc_cairo_graphics_rectangle_draw(
  cairo_t * cr, int * status, const struct cmc_graphics_rectangle * rectangle,
  void (*get_color)(struct cmc_rgb *, const void *));

void cmc_cairo_graphics_mesh_2d_node_draw(
  cairo_t * cr, int * status, const struct cmc_graphics_mesh_2d_node * node,
  void (*get_color)(struct cmc_rgb *, const void *));

void cmc_cairo_graphics_mesh_2d_edge_black_draw(
  cairo_t * cr, int * status, const struct cmc_graphics_mesh_2d_edge * edge,
  void (*draw_curve)(cairo_t *, int *, const void *));

void cmc_cairo_graphics_mesh_2d_edge_oriented_draw(
  cairo_t * cr, int * status, const struct cmc_graphics_mesh_2d_edge * edge,
  void (*get_color)(struct cmc_rgb *, const void *));

#endif /* _cmc_cairo_h */
