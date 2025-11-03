#include <stdio.h>

#include <cairo-svg.h>

#include "cmc_error_message.h"
#include "cmc_cairo_animation_draw_to_file.h"

void cmc_cairo_svg_animation(
  struct cmc_animation * animation,
  int * status,
  int argc,
  char ** argv,
  const char * filename)
{
  if (filename == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("empty filenames are not allowed\n", stderr);
    *status = 1;
    return;
  }

  cmc_cairo_animation_draw_to_file(
    animation, status, filename, cairo_svg_surface_create, NULL);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot draw animation to SVG file %s%s%s\n",
      color_variable, filename, color_none);
    return;
  }
}
