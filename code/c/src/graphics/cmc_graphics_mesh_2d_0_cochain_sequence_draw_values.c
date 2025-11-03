#include <stdio.h>

#include "cmc_error_message.h"
#include "cmc_graphics_mesh_2d_0_cochain_sequence.h"
#include "cmc_graphics_mesh_2d_0_cochain_sequence_draw_functions.h"
#include "cmc_graphics_mesh_2d_node.h"
#include "cmc_rgb.h"

void cmc_graphics_mesh_2d_0_cochain_sequence_draw_values(
  void * canvas,
  int * status,
  const struct cmc_graphics_mesh_2d_0_cochain_sequence * cochain_sequence,
  int i,
  int total_colors,
  const struct cmc_graphics_mesh_2d_0_cochain_sequence_draw_functions *
    functions)
{
  int color_index, j, number_of_nodes;
  double color_coefficient, max, min, denominator;
  double * coordinates, * point_sizes, * values_i;
  struct cmc_graphics_mesh_2d_node node;
  void (*set_color)(void *, int, int) = functions->set_color;
  void (*get_color)(void *, const void *) = functions->get_color;
  void (*draw_node)(void *, int *, const struct cmc_graphics_mesh_2d_node *,
    void (*)(void *, const void *)) = functions->draw_node;

  min = cochain_sequence->min_value;
  max = cochain_sequence->max_value;
  number_of_nodes = cochain_sequence->m->cn[0];
  denominator = max - min;
  point_sizes = cochain_sequence->point_sizes;
  coordinates = cochain_sequence->coordinates;

  functions->check_color_scheme(status, total_colors);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot create color scheme with %d colors\n",
      total_colors);
    return;
  }

  functions->allocate_color(&(node.color), status);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot allocate color\n", stderr);
    return;
  }

  values_i = cochain_sequence->values + number_of_nodes * i;
  if (denominator == 0.)
  {
    set_color(node.color, 0, total_colors);
    for (j = 0; j < number_of_nodes; ++j)
    {
      node.size = point_sizes[j];
      node.coordinates = coordinates + 2 * j;
      draw_node(canvas, status, &node, get_color);
      if (*status)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fputs("cannot draw node\n", stderr);
        goto color_free;
      }
    }
  }
  else
  {
    color_coefficient = (double) (total_colors - 1) / denominator;
    for (j = 0; j < number_of_nodes; ++j)
    {
      color_index = (int) ((values_i[j] - min) * color_coefficient);
      node.size = point_sizes[j];
      node.coordinates = coordinates + 2 * j;
      set_color(node.color, color_index, total_colors);
      draw_node(canvas, status, &node, get_color);
      if (*status)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fputs("cannot draw node\n", stderr);
        goto color_free;
      }
    }
  }
color_free:
  functions->deallocate_color(node.color);
}
