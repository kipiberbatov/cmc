#include "cmc_error_message.h"
#include "cmc_animation.h"
#include "cmc_animation_generic_data.h"
#include "cmc_command_line.h"
#include "cmc_graphics_filled_window.h"

static void update_index(int * i){++*i;}

int main(int argc, char ** argv)
{
  char * animation_backend, * animation_library, * canvas_backend,
       * canvas_library, * output_name = NULL;
  int size, status;
  const int close_automatically_default = 0, timelapse_default = 100,
            total_colors_default = 100;
  const double height_default = 500,  width_default = 500;
  struct cmc_animation_generic_data generic_data;
  struct cmc_animation animation;
  struct cmc_graphics_filled_window filled_window;

  cmc_command_line option_animation_backend, option_animation_library,
                    option_canvas_backend, option_canvas_library,
                    option_close_automatically, option_height, option_output,
                    option_timelapse, option_title, option_total_colors,
                    option_width, no_positional_arguments;

  cmc_command_line *(options[]) =
  {
    &option_animation_library,
    &option_animation_backend,
    &option_canvas_library,
    &option_canvas_backend,
    &option_total_colors,
    &option_width,
    &option_height,
    &option_output,
    &option_title,
    &option_timelapse,
    &option_close_automatically,
    &no_positional_arguments
  };

  cmc_command_line_set_option_string(
    &option_animation_backend, &animation_backend, "--animation-backend", NULL);

  cmc_command_line_set_option_string(
    &option_animation_library, &animation_library, "--animation-library", NULL);

  cmc_command_line_set_option_string(
    &option_canvas_backend, &canvas_backend, "--canvas-backend", NULL);

  cmc_command_line_set_option_string(
    &option_canvas_library, &canvas_library, "--canvas-library", NULL);

  cmc_command_line_set_option_string(
    &option_output, &output_name, "--output", NULL);
  option_output.minimal_number_of_arguments = 0;

  cmc_command_line_set_option_string(
    &option_title, &(animation.title), "--title", "Changing colors");

  cmc_command_line_set_option_int(
    &option_total_colors, &(generic_data.total_steps), "--total-colors",
    &total_colors_default);

  cmc_command_line_set_option_int(
    &option_timelapse, &(animation.timelapse),
    "--timelapse", &timelapse_default);

  cmc_command_line_set_option_double(
    &option_width, &(generic_data.width), "--width", &width_default);

  cmc_command_line_set_option_double(
    &option_height, &(generic_data.height), "--height", &height_default);

  cmc_command_line_set_option_int(
    &option_close_automatically, &(animation.close_automatically),
    "--close-automatically", &close_automatically_default);

  cmc_command_line_set_option_no_arguments(
    &no_positional_arguments, NULL, NULL, NULL);

  size = (int) (sizeof(options) / sizeof(*options));
  status = 0;
  cmc_command_line_parse(options, &status, size, argc, argv);
  if (status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot parse command line options\n", stderr);
    goto end;
  }

  generic_data.new_index = 0;
  animation.data = (void *) &filled_window;
  animation.generic_data = (void *) &generic_data;
  animation.total_colors = generic_data.total_steps;
  animation.update_new_index = update_index;
  animation.draw_snapshot = cmc_graphics_filled_window_draw_snapshot;

  cmc_animation_check_input(&status, &animation);
  if (status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("bad input\n", stderr);
    goto end;
  }

  cmc_animation_read_and_apply_backends(
    &animation, &status,
    argc, argv, output_name,
    canvas_library, canvas_backend, animation_library, animation_backend);
  if (status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot read and apply backends\n", stderr);
    goto end;
  }

end:
  return status;
}
