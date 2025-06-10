#include <math.h>
#include <stdio.h>
#include <string.h>

#include "arc_2d.h"
#include "color.h"
#include "cmc_graphics_mesh_2d_1_cochain_sequence.h"
#include "cmc_graphics_mesh_2d_1_cochain_sequence_draw_functions.h"
#include "cmc_graphics_mesh_2d_edge.h"
#include "line_2d.h"
#include "mesh.h"

void cmc_graphics_mesh_2d_1_cochain_sequence_draw_values_disk_polar_forman(
  void * canvas,
  int * status,
  const struct cmc_graphics_mesh_2d_1_cochain_sequence * cochain_sequence,
  const struct cmc_graphics_mesh_2d_1_cochain_sequence_draw_functions *
    functions,
  int i,
  int total_colors)
{
  int color_index, end_index, j, index, na, nd;
  int * cf_1_0_index, * m_cn;
  double cx, cy, r, r0, rx, ry, theta;
  double color_coefficient, denominator, min, max, sign, size;
  double * boundary_1, * coordinates, * values_i;
  struct jagged2 cf_1_0;
  struct mesh * m;
  struct cmc_graphics_mesh_2d_edge edge;
  struct line_2d flow_rate_direction, line;
  struct arc_2d arc;
  void (*set_color)(void *, int, int) = functions->set_color;
  void (*get_color)(void *, const void *) = functions->get_color;
  void (*draw_oriented_edge)(void *, int *,
    const struct cmc_graphics_mesh_2d_edge *,
    void (*)(void *, const void *)) = functions->draw_oriented_edge;

  min = cochain_sequence->min_value;
  max = cochain_sequence->max_value;
  denominator = max - min;
  if (denominator == 0.)
    return;
  color_coefficient = (double) (total_colors - 1) / denominator;

  boundary_1 = cochain_sequence->boundary_1;
  coordinates = cochain_sequence->coordinates;

  edge.width = cochain_sequence->line_width;
  if (edge.width < 2.5)
    edge.width = 2.5;

  m = cochain_sequence->m;
  m_cn = m->cn;
  mesh_cf_part2(&cf_1_0, m, 1, 0);
  cf_1_0_index = cf_1_0.a2;

  functions->check_color_scheme(status, total_colors);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot create color scheme with %d colors\n",
      total_colors);
    return;
  }

  functions->allocate_color(&(edge.color), status);
  if (*status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot allocate color\n", stderr);
    return;
  }

  na = 2 * (2 * m_cn[0] - m_cn[1] - 2);
  nd = (m_cn[0] - 1) / na;
  end_index = na * nd / 4;
  cx = coordinates[0];
  cy = coordinates[1];
  rx = coordinates[2 * end_index] - cx;
  ry = coordinates[2 * end_index + 1] - cy;
  r = sqrt(rx * rx + ry * ry);
  r0 = r / nd;
  theta = M_PI * 2 / na;
  arc.x0 = cx;
  arc.y0 = cy;

  size = edge.width * 48. / sqrt((double) m_cn[0]);
  edge.width = size / 6.;
  edge.data = (void *) &flow_rate_direction;
  values_i = cochain_sequence->values + cf_1_0.a0 * i;
  index = 0;

  /* edges to nodes */
  for (i = 1; i <= nd / 2; ++i)
  {
    /* rays */
    for (j = 0; j < na; ++j)
    {
      color_index = (int) ((fabs(values_i[index]) - min) * color_coefficient);
      if (color_index)
      {
        set_color(edge.color, color_index, total_colors);
        sign = boundary_1[2 * index + 1] * values_i[index] > 0. ? -1. : 1.;
        memcpy(line.x0, coordinates + 2 * cf_1_0_index[0], sizeof(double) * 2);
        memcpy(line.x1, coordinates + 2 * cf_1_0_index[1], sizeof(double) * 2);
        line_2d_set_flow_rate_direction(&flow_rate_direction, &line, sign,size);
        draw_oriented_edge(canvas, status, &edge, get_color);
        if (*status)
        {
          color_error_position(__FILE__, __LINE__);
          fputs("cannot paint an edge\n", stderr);
          goto color_free;
        }
      }
      ++index;
      cf_1_0_index += 2;
    }

    /* arcs */
    arc.r = r0 * 2 * i;
    for (j = 0; j < na; ++j)
    {
      color_index = (int) ((fabs(values_i[index]) - min) * color_coefficient);
      if (color_index)
      {
        set_color(edge.color, color_index, total_colors);
        sign = boundary_1[2 * index + 1] * values_i[index] > 0. ? -1. : 1.;
        if (j % 2 == 0)
          sign = -sign;
        arc.alpha = j * theta;
        arc.beta = (j + 1) * theta;
        arc_2d_set_flow_rate_direction(&flow_rate_direction, &arc, sign, size);
        draw_oriented_edge(canvas, status, &edge, get_color);
        if (*status)
        {
          color_error_position(__FILE__, __LINE__);
          fputs("cannot paint an edge\n", stderr);
          goto color_free;
        }
      }
      ++index;
      cf_1_0_index += 2;
    }
  }

  /* faces to edges */

  /* inner circle: arc-ray-arc */
  arc.r = r0;
  for (j = 0; j < na / 2; ++j)
  {
    color_index = (int) ((fabs(values_i[index]) - min) * color_coefficient);
    if (color_index)
    {
      set_color(edge.color, color_index, total_colors);
      sign = boundary_1[2 * index + 1] * values_i[index] < 0. ? -1. : 1.;
      arc.alpha = 2 * j * theta;
      arc.beta = (2 * j + 1) * theta;
      arc_2d_set_flow_rate_direction(&flow_rate_direction, &arc, sign, size);
      draw_oriented_edge(canvas, status, &edge, get_color);
      if (*status)
      {
        color_error_position(__FILE__, __LINE__);
        fputs("cannot paint an edge\n", stderr);
        goto color_free;
      }
    }
    ++index;
    cf_1_0_index += 2;

    color_index = (int) ((fabs(values_i[index]) - min) * color_coefficient);
    if (color_index)
    {
      set_color(edge.color, color_index, total_colors);
      sign = boundary_1[2 * index + 1] * values_i[index] > 0. ? -1. : 1.;
      memcpy(line.x0, coordinates + 2 * cf_1_0_index[0], sizeof(double) * 2);
      memcpy(line.x1, coordinates + 2 * cf_1_0_index[1], sizeof(double) * 2);
      line_2d_set_flow_rate_direction(&flow_rate_direction, &line, sign, size);
      draw_oriented_edge(canvas, status, &edge, get_color);
      if (*status)
      {
        color_error_position(__FILE__, __LINE__);
        fputs("cannot paint an edge\n", stderr);
        goto color_free;
      }
    }
    ++index;
    cf_1_0_index += 2;

    color_index = (int) ((fabs(values_i[index]) - min) * color_coefficient);
    if (color_index)
    {
      set_color(edge.color, color_index, total_colors);
      sign = boundary_1[2 * index + 1] * values_i[index] > 0. ? -1. : 1.;
      arc.alpha = (2 * j + 1) * theta;
      arc.beta = (2 * j + 2) * theta;
      arc_2d_set_flow_rate_direction(&flow_rate_direction, &arc, sign, size);
      draw_oriented_edge(canvas, status, &edge, get_color);
      if (*status)
      {
        color_error_position(__FILE__, __LINE__);
        fputs("cannot paint an edge\n", stderr);
        goto color_free;
      }
    }
    ++index;
    cf_1_0_index += 2;
  }

  /* outer circles: ray-arc-ray-arc */
  for (i = 1; i < nd / 2; ++i)
  {
    arc.r = r0 * (2 * i + 1);
    for (j = 0; j < na / 2; ++j)
    {
      color_index = (int) ((fabs(values_i[index]) - min) * color_coefficient);
      if (color_index)
      {
        set_color(edge.color, color_index, total_colors);
        sign = boundary_1[2 * index + 1] * values_i[index] > 0. ? -1. : 1.;
        memcpy(line.x0, coordinates + 2 * cf_1_0_index[0], sizeof(double) * 2);
        memcpy(line.x1, coordinates + 2 * cf_1_0_index[1], sizeof(double) * 2);
        line_2d_set_flow_rate_direction(&flow_rate_direction, &line, sign,size);
        draw_oriented_edge(canvas, status, &edge, get_color);
        if (*status)
        {
          color_error_position(__FILE__, __LINE__);
          fputs("cannot paint an edge\n", stderr);
          goto color_free;
        }
      }
      ++index;
      cf_1_0_index += 2;

      color_index = (int) ((fabs(values_i[index]) - min) * color_coefficient);
      if (color_index)
      {
        set_color(edge.color, color_index, total_colors);
        sign = boundary_1[2 * index + 1] * values_i[index] < 0. ? -1. : 1.;
        arc.alpha = 2 * j * theta;
        arc.beta = (2 * j + 1) * theta;
        arc_2d_set_flow_rate_direction(&flow_rate_direction, &arc, sign, size);
        draw_oriented_edge(canvas, status, &edge, get_color);
        if (*status)
        {
          color_error_position(__FILE__, __LINE__);
          fputs("cannot paint an edge\n", stderr);
          goto color_free;
        }
      }
      ++index;
      cf_1_0_index += 2;

      color_index = (int) ((fabs(values_i[index]) - min) * color_coefficient);
      if (color_index)
      {
        set_color(edge.color, color_index, total_colors);
        sign = boundary_1[2 * index + 1] * values_i[index] < 0. ? -1. : 1.;
        memcpy(line.x0, coordinates + 2 * cf_1_0_index[0], sizeof(double) * 2);
        memcpy(line.x1, coordinates + 2 * cf_1_0_index[1], sizeof(double) * 2);
        line_2d_set_flow_rate_direction(&flow_rate_direction, &line, sign,size);
        draw_oriented_edge(canvas, status, &edge, get_color);
        if (*status)
        {
          color_error_position(__FILE__, __LINE__);
          fputs("cannot paint an edge\n", stderr);
          goto color_free;
        }
      }
      ++index;
      cf_1_0_index += 2;

      color_index = (int) ((fabs(values_i[index]) - min) * color_coefficient);
      if (color_index)
      {
        set_color(edge.color, color_index, total_colors);
        sign = boundary_1[2 * index + 1] * values_i[index] > 0. ? -1. : 1.;
        arc.alpha = (2 * j + 1) * theta;
        arc.beta = (2 * j + 2) * theta;
        arc_2d_set_flow_rate_direction(&flow_rate_direction, &arc, sign, size);
        draw_oriented_edge(canvas, status, &edge, get_color);
        if (*status)
        {
          color_error_position(__FILE__, __LINE__);
          fputs("cannot paint an edge\n", stderr);
          goto color_free;
        }
      }
      ++index;
      cf_1_0_index += 2;
    }
  }
color_free:
  functions->deallocate_color(edge.color);
}
