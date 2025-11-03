#include <stdio.h>

#include "cmc_error_message.h"
#include "cmc_animation.h"
#include "cmc_animation_generic_data.h"
#include "cmc_graphics_mesh_2d_1_cochain_sequence.h"
#include "cmc_graphics_mesh_2d_1_cochain_sequence_draw_functions.h"
#include "cmc_graphics_mesh_2d_skeleton.h"

void cmc_graphics_mesh_2d_1_cochain_sequence_draw_snapshot(
  void * canvas,
  int * status,
  const struct cmc_animation * animation)
{
  struct cmc_graphics_mesh_2d_1_cochain_sequence * cochain_sequence;
  struct cmc_graphics_mesh_2d_skeleton skeleton;
  const struct cmc_graphics_mesh_2d_1_cochain_sequence_draw_functions *
    functions;

  *(void **) (&cochain_sequence) = animation->data;
  *(const void **) (&functions) = animation->draw_functions;

  skeleton.line_width = cochain_sequence->line_width;
  skeleton.coordinates = cochain_sequence->coordinates;
  skeleton.m = cochain_sequence->m;

  functions->set_background_color(canvas, status);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot set set background color %d\n", stderr);
    return;
  }

  functions->draw_skeleton(
    canvas,
    status,
    &skeleton,
    functions->draw_curves,
    functions->draw_black_edge);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot draw skeleton %d\n", stderr);
    return;
  }

  functions->draw_values(
    canvas, status, cochain_sequence, functions,
    animation->generic_data->new_index, animation->total_colors);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot draw values %d\n", stderr);
    return;
  }
}
