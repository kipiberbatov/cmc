#include <stdio.h>

#include "cmc_error_message.h"
#include "cmc_animation.h"
#include "cmc_animation_generic_data.h"
#include "cmc_cairo_animation_draw_to_file.h"

static void cmc_cairo_animation_draw_page_to_cairo_context(
  cairo_t * cr, int * status, const struct cmc_animation * animation)
{
  animation->draw_snapshot((void *) cr, status, animation);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot draw to Cairo context\n", stderr);
    return;
  }
  cairo_show_page(cr);
  *status = cairo_status(cr);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot render with Cairo: %s\n",
      cairo_status_to_string(*status));
    return;
  }
}

static void cmc_cairo_animation_draw_to_cairo_surface(
  cairo_surface_t * surface, struct cmc_animation * animation, int * status)
{
  int i, n;
  struct cmc_animation_generic_data * generic_data;
  cairo_t * cr;

  generic_data = animation->generic_data;
  n = generic_data->total_steps;
  i = generic_data->new_index;
  while (i < n)
  {
    cr = cairo_create(surface);
    *status = cairo_status(cr);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr,
        "cannot create Cairo context from Cairo surface: %s\n",
        cairo_status_to_string(*status));
      return;
    }

    cmc_cairo_animation_draw_page_to_cairo_context(cr, status, animation);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr,
        "cannot render snapshot %s%d%s to Cairo context\n",
        color_variable, i, color_none);
      return;
    }

    generic_data->old_index = i;
    animation->update_new_index(&(generic_data->new_index));
    i = generic_data->new_index;
    cairo_destroy(cr);
  }
}

void cmc_cairo_animation_draw_to_file(
  struct cmc_animation * animation,
  int * status,
  const char * filename,
  cairo_surface_t * (*_surface_create)(const char *, double, double),
  void (*_set_version)(cairo_surface_t * surface))
{
  double height, width;
  cairo_surface_t * surface;

  width = animation->generic_data->width;
  height = animation->generic_data->height;

  surface = _surface_create(filename, width, height);
  *status = cairo_surface_status(surface);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot create Cairo PDF surface from filename %s%s%s: %s\n",
      color_variable, filename, color_none,
      cairo_status_to_string(*status));
    return;
  }

  if(_set_version != NULL)
    _set_version(surface);

  cmc_cairo_animation_draw_to_cairo_surface(surface, animation, status);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot draw animation to PDF Cairo surface\n", stderr);
    return;
  }
  cairo_surface_destroy(surface);
}
