#include <stdio.h>

#include <cairo-pdf.h>

#include "cmc_error_message.h"
#include "cmc_cairo_animation_draw_to_file.h"

static void set_version(cairo_surface_t * surface)
{
  cairo_pdf_surface_restrict_to_version(surface, CAIRO_PDF_VERSION_1_5);
}

void cmc_cairo_animation_pdf(
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
    animation, status, filename, cairo_pdf_surface_create, set_version);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot draw animation to PDF file %s%s%s\n",
      color_variable, filename, color_none);
    return;
  }
}
