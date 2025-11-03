#include <stdio.h>

#include "cmc_error_message.h"
#include "cmc_animation.h"
#include "cmc_animation_generic_data.h"
#include "cmc_graphics_filled_window.h"
#include "cmc_graphics_filled_window_draw_functions.h"

void cmc_graphics_filled_window_draw_snapshot(
  void * canvas,
  int * status,
  const struct cmc_animation * animation)
{
  int color_index, total_colors;
  struct cmc_graphics_filled_window filled_window;
  const struct cmc_graphics_filled_window_draw_functions * functions;

  *(void **) (&filled_window) = animation->data;

  color_index = animation->generic_data->new_index;
  total_colors = animation->total_colors;
  *(const void **) (&functions) = animation->draw_functions;

  functions->allocate_color(&(filled_window.color), status);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot allocate color\n", stderr);
    return;
  }

  functions->set_color(filled_window.color, status, color_index, total_colors);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot set color %d\n", color_index);
    goto color_free;
  }

  functions->paint(canvas, status, filled_window.color);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot set color %d\n", color_index);
    goto color_free;
  }

color_free:
  functions->deallocate_color(filled_window.color);
}
