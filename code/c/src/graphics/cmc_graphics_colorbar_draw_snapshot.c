#include <stdio.h>

#include "cmc_error_message.h"
#include "cmc_animation.h"
#include "cmc_animation_generic_data.h"
#include "cmc_graphics_colorbar_direction.h"
#include "cmc_graphics_colorbar_draw_functions.h"
#include "cmc_graphics_rectangle.h"

void cmc_graphics_colorbar_draw_snapshot(
  void * canvas,
  int * status,
  const struct cmc_animation * animation)
{
  int total_colors;
  const struct cmc_graphics_colorbar_draw_functions * functions;
  enum cmc_graphics_colorbar_direction direction;
  struct cmc_graphics_rectangle rectangle;

  total_colors = animation->total_colors;
  *(const void **) (&functions) = animation->draw_functions;
  direction = *(int *) animation->data;

  functions->check_color_scheme(status, total_colors);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot create color scheme with %s%d%s colors\n",
      color_variable, total_colors, color_none);
    return;
  }

  functions->allocate_color(&(rectangle.color), status);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot allocate color\n", stderr);
    return;
  }

  functions->draw_rectangles(
    &rectangle,
    canvas,
    status,
    animation->generic_data->width,
    animation->generic_data->height,
    direction,
    total_colors,
    functions);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot draw values %d\n", stderr);
    goto color_free;
  }

color_free:
  functions->deallocate_color(rectangle.color);
}
