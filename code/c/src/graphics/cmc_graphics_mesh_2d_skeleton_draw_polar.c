#include <math.h>
#include <stdio.h>

#include "arc_2d.h"
#include "cmc_error_message.h"
#include "cmc_graphics_mesh_2d_edge.h"
#include "cmc_graphics_mesh_2d_skeleton.h"
#include "line_2d.h"
#include "mesh.h"
#include "vector_2d.h"

void cmc_graphics_mesh_2d_skeleton_draw_polar(
  void * canvas,
  int * status,
  const struct cmc_graphics_mesh_2d_skeleton * skeleton,
  void (**draw_curves)(void *, int *, const void *),
  void (*draw_black_edge)(
    void *, int *, const struct cmc_graphics_mesh_2d_edge *,
    void (*)(void *, int *, const void *)))
{
  int i, j, index, na, nd, product;
  int * cf_1_0_index, * m_cf_a3_2_0, * m_cn;
  double cx, cy, rx, ry, theta;
  double * coordinates, * x0, * x1;
  jagged2 cf_1_0;
  mesh * m;
  struct cmc_graphics_mesh_2d_edge edge;
  struct line_2d line;
  struct arc_2d arc;

  void (*draw_line)(void *, int *, const void *) = draw_curves[0];
  void (*draw_arc)(void *, int *, const void *) = draw_curves[1];

  coordinates = skeleton->coordinates;
  edge.width = skeleton->line_width;
  m = skeleton->m;
  m_cn = m->cn;
  m_cf_a3_2_0 = m->cf->a3 + m_cn[1];
  mesh_cf_part2(&cf_1_0, m, 1, 0);
  cf_1_0_index = cf_1_0.a2;

  product = m_cn[2];
  na = 0;
  i = 0;
  while (m_cf_a3_2_0[i] == 3)
  {
    ++na;
    ++i;
  }
  nd = product / na;
  cx = coordinates[0];
  cy = coordinates[1];
  theta = M_PI * 2 / na;
  arc.x0 = cx;
  arc.y0 = cy;

  index = 0;
  for (i = 0; i < nd; ++i)
  {
    /* rays */
    edge.data = (void *) &line;
    for (j = 0; j < na; ++j)
    {
      x0 = coordinates + 2 * cf_1_0_index[0];
      x1 = coordinates + 2 * cf_1_0_index[1];
      line.x0[0] = x0[0];
      line.x0[1] = x0[1];
      line.x1[0] = x1[0];
      line.x1[1] = x1[1];
      draw_black_edge(canvas, status, &edge, draw_line);
      if (*status)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fprintf(stderr, "cannot draw edge as a line for index %d\n", index);
        return;
      }
      ++index;
      cf_1_0_index += 2;
    }

    /* arcs */
    edge.data = (void *) &arc;
    x0 = coordinates + 2 * cf_1_0_index[0];
    rx = x0[0] - cx;
    ry = x0[1] - cy;
    arc.r = sqrt(rx * rx + ry * ry);
    for (j = 0; j < na; ++j)
    {
      arc.alpha = j * theta;
      arc.beta = (j + 1) * theta;
      draw_black_edge(canvas, status, &edge, draw_arc);
      if (*status)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fprintf(stderr, "cannot draw edge as an arc for index %d\n", index);
        return;
      }
      ++index;
      cf_1_0_index += 2;
    }
  }
}
