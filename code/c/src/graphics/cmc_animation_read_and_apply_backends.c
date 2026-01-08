#include <stdio.h>

#include "cmc_dynamic_library.h"

#include "cmc_error_message.h"
#include "cmc_animation.h"

void cmc_animation_read_and_apply_backends(
  struct cmc_animation * animation,
  int * status,
  int argc,
  char ** argv,
  const char * output_name,
  const char * canvas_library,
  const char * canvas_backend,
  const char * animation_library,
  const char * animation_backend)
{
  void * lib_animation, * lib_canvas;
  char * error;
  void (*render)(struct cmc_animation *, int *, int, char **, const char *);

  lib_canvas = cmc_dynamic_library_open(canvas_library);
  error = cmc_dynamic_library_error();
  if (error)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "%s\n", error);
    *status = 1;
    goto end;
  }

  *(void **) (&(animation->draw_functions))
  = cmc_dynamic_library_get_symbol_address(lib_canvas, canvas_backend);
  error = cmc_dynamic_library_error();
  if (error)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "%s\n", error);
    *status = 1;
    goto lib_canvas_close;
  }

  lib_animation = cmc_dynamic_library_open(animation_library);
  error = cmc_dynamic_library_error();
  if (error)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "%s\n", error);
    *status = 1;
    goto lib_canvas_close;
  }

  *(void **) (&render)
  = cmc_dynamic_library_get_symbol_address(lib_animation, animation_backend);
  error = cmc_dynamic_library_error();
  if (error)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "%s\n", error);
    *status = 1;
    goto lib_animation_close;
  }

  render(animation, status, argc, argv, output_name);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot draw animation\n", stderr);
    goto lib_animation_close;
  }

lib_animation_close:
  cmc_dynamic_library_close(lib_animation);
lib_canvas_close:
  cmc_dynamic_library_close(lib_canvas);
end:
  return;
}
