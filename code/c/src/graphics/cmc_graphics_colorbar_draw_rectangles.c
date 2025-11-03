#include <stdio.h>

#include "cmc_error_message.h"
#include "cmc_graphics_rectangle.h"
#include "cmc_graphics_colorbar_direction.h"
#include "cmc_graphics_colorbar_draw_functions.h"
#include "cmc_rgb.h"

static void cmc_graphics_colorbar_draw_rectangles_horizontal(
  struct cmc_graphics_rectangle * rectangle,
  void * canvas,
  int * status,
  double width,
  double height,
  int total_colors,
  const struct cmc_graphics_colorbar_draw_functions * functions)
{
  int j;
  double step_x;
  void (*set_color)(void *, int, int) = functions->set_color;
  void (*get_color)(void *, const void *) = functions->get_color;
  void (*draw_rectangle)(void *, int *, const struct cmc_graphics_rectangle *,
    void (*)(void *, const void *)) = functions->draw_rectangle;

  step_x = width / (double) total_colors;
  rectangle->x = 0;
  rectangle->y = 0;
  rectangle->width = step_x;
  rectangle->height = height;
  for (j = 0; j < total_colors; ++j)
  {
    set_color(rectangle->color, j, total_colors);
    draw_rectangle(canvas, status, rectangle, get_color);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fputs("cannot draw rectangle\n", stderr);
      return;
    }
    rectangle->x += step_x;
  }
}

static void cmc_graphics_colorbar_draw_rectangles_vertical(
  struct cmc_graphics_rectangle * rectangle,
  void * canvas,
  int * status,
  double width,
  double height,
  int total_colors,
  const struct cmc_graphics_colorbar_draw_functions * functions)
{
  int j;
  double step_y;
  void (*set_color)(void *, int, int) = functions->set_color;
  void (*get_color)(void *, const void *) = functions->get_color;
  void (*draw_rectangle)(void *, int *, const struct cmc_graphics_rectangle *,
    void (*)(void *, const void *)) = functions->draw_rectangle;

  step_y = height / (double) total_colors;
  rectangle->x = 0;
  rectangle->y = height - step_y;
  rectangle->width = width;
  rectangle->height = step_y;
  for (j = 0; j < total_colors; ++j)
  {
    set_color(rectangle->color, j, total_colors);
    draw_rectangle(canvas, status, rectangle, get_color);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fputs("cannot draw rectangle\n", stderr);
      return;
    }
    rectangle->y -= step_y;
  }
}

void cmc_graphics_colorbar_draw_rectangles(
  struct cmc_graphics_rectangle * rectangle,
  void * canvas,
  int * status,
  double width,
  double height,
  enum cmc_graphics_colorbar_direction direction,
  int total_colors,
  const struct cmc_graphics_colorbar_draw_functions * functions)
{
  void (*drawer)(
    struct cmc_graphics_rectangle * rectangle,
    void * canvas,
    int * status,
    double width,
    double height,
    int total_colors,
    const struct cmc_graphics_colorbar_draw_functions * functions);

  if (direction == cmc_graphics_colorbar_direction_horizontal)
    drawer = cmc_graphics_colorbar_draw_rectangles_horizontal;
  else if (direction == cmc_graphics_colorbar_direction_vertical)
    drawer = cmc_graphics_colorbar_draw_rectangles_vertical;
  else
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("direction is neither horizontal, nor vertical\n", stderr);
    *status = 1;
    return;
  }

  drawer(rectangle, canvas, status, width, height, total_colors, functions);
  if(*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot draw rectangles\n", stderr);
    return;
  }
}
