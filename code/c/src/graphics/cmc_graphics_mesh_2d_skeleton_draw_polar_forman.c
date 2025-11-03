#include <math.h>
#include <stdio.h>
#include <string.h>

#include "arc_2d.h"
#include "cmc_error_message.h"
#include "cmc_graphics_mesh_2d_edge.h"
#include "cmc_graphics_mesh_2d_skeleton.h"
#include "line_2d.h"
#include "mesh.h"

void cmc_graphics_mesh_2d_skeleton_draw_polar_forman(
  void * canvas,
  int * status,
  const struct cmc_graphics_mesh_2d_skeleton * skeleton,
  void (**draw_curves)(void *, int *, const void *),
  void (*draw_black_edge)(
    void *, int *, const struct cmc_graphics_mesh_2d_edge *,
    void (*)(void *, int *, const void *)))
{
  int i, j, index, na, nd;
  int * cf_1_0_index, * m_cn;
  double cx, cy, rx, ry, theta;
  double * coordinates, * x0;
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
  mesh_cf_part2(&cf_1_0, m, 1, 0);
  cf_1_0_index = cf_1_0.a2;

  na = 2 * (2 * m_cn[0] - m_cn[1] - 2);
  nd = (m_cn[0] - 1) / na;
  cx = coordinates[0];
  cy = coordinates[1];
  theta = M_PI * 2 / na;
  arc.x0 = cx;
  arc.y0 = cy;

  index = 0;
  /* edges to nodes */
  for (i = 1; i <= nd / 2; ++i)
  {
    /* rays */
    edge.data = (void *) &line;
    for (j = 0; j < na; ++j)
    {
      memcpy(line.x0, coordinates + 2 * cf_1_0_index[0], sizeof(double) * 2);
      memcpy(line.x1, coordinates + 2 * cf_1_0_index[1], sizeof(double) * 2);
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

  /* inner circle: arc-ray-arc */
  x0 = coordinates + 2 * cf_1_0_index[0];
  rx = x0[0] - cx;
  ry = x0[1] - cy;
  arc.r = sqrt(rx * rx + ry * ry);
  for (j = 0; j < na / 2; ++j)
  {
    arc.alpha = 2 * j * theta;
    arc.beta = (2 * j + 1) * theta;
    edge.data = (void *) &arc;
    draw_black_edge(canvas, status, &edge, draw_arc);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot draw edge as an arc for index %d\n", index);
      return;
    }
    ++index;
    cf_1_0_index += 2;

    memcpy(line.x0, coordinates + 2 * cf_1_0_index[0], sizeof(double) * 2);
    memcpy(line.x1, coordinates + 2 * cf_1_0_index[1], sizeof(double) * 2);
    edge.data = (void *) &line;
    draw_black_edge(canvas, status, &edge, draw_line);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot draw edge as a line for index %d\n", index);
      return;
    }
    ++index;
    cf_1_0_index += 2;

    arc.alpha = (2 * j + 1) * theta;
    arc.beta = (2 * j + 2) * theta;
    edge.data = (void *) &arc;
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

  /* outer circles: ray-arc-ray-arc */
  for (i = 1; i < nd / 2; ++i)
  {
    x0 = coordinates + 2 * cf_1_0_index[2];
    rx = x0[0] - cx;
    ry = x0[1] - cy;
    arc.r = sqrt(rx * rx + ry * ry);
    for (j = 0; j < na / 2; ++j)
    {
      memcpy(line.x0, coordinates + 2 * cf_1_0_index[0], sizeof(double) * 2);
      memcpy(line.x1, coordinates + 2 * cf_1_0_index[1], sizeof(double) * 2);
      edge.data = (void *) &line;
      draw_black_edge(canvas, status, &edge, draw_line);
      if (*status)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fprintf(stderr, "cannot draw edge as a line for index %d\n", index);
        return;
      }
      ++index;
      cf_1_0_index += 2;

      arc.alpha = 2 * j * theta;
      arc.beta = (2 * j + 1) * theta;
      edge.data = (void *) &arc;
      draw_black_edge(canvas, status, &edge, draw_arc);
      if (*status)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fprintf(stderr, "cannot draw edge as an arc for index %d\n", index);
        return;
      }
      ++index;
      cf_1_0_index += 2;

      memcpy(line.x0, coordinates + 2 * cf_1_0_index[0], sizeof(double) * 2);
      memcpy(line.x1, coordinates + 2 * cf_1_0_index[1], sizeof(double) * 2);
      edge.data = (void *) &line;
      draw_black_edge(canvas, status, &edge, draw_line);
      if (*status)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fprintf(stderr, "cannot draw edge as a line for index %d\n", index);
        return;
      }
      ++index;
      cf_1_0_index += 2;

      arc.alpha = (2 * j + 1) * theta;
      arc.beta = (2 * j + 2) * theta;
      edge.data = (void *) &arc;
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
