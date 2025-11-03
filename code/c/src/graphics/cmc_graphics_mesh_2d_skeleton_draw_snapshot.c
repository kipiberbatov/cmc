#include <stdio.h>

#include "cmc_error_message.h"
#include "cmc_animation.h"
#include "cmc_graphics_mesh_2d_skeleton.h"
#include "cmc_graphics_mesh_2d_skeleton_draw_functions.h"

void cmc_graphics_mesh_2d_skeleton_draw_snapshot(
  void * canvas,
  int * status,
  const struct cmc_animation * animation)
{
  struct cmc_graphics_mesh_2d_skeleton * skeleton;
  const struct cmc_graphics_mesh_2d_skeleton_draw_functions * functions;

  *(void **) (&skeleton) = animation->data;
  *(const void **) (&functions) = animation->draw_functions;

  functions->draw_skeleton(
    canvas,
    status,
    skeleton,
    functions->draw_curves,
    functions->draw_black_edge);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot draw skeleton %d\n", stderr);
    return;
  }
}
