/* system headers */
#include <errno.h>
#include <stdlib.h>

/* internal headers */
#include "cmc_error_message.h"
#include "double_array.h"
#include "double_matrix.h"
#include "frame.h"
#include "cmc_animation.h"
#include "cmc_animation_generic_data.h"
#include "cmc_command_line.h"
#include "cmc_graphics_mesh_2d_0_cochain_sequence.h"
#include "mesh.h"

static void update_index(int * i){++*i;}

int main(int argc, char ** argv)
{
  char * animation_backend, * animation_library, * canvas_backend,
       * canvas_library, * m_format, * m_name, * output_name = NULL,
       * u_format, * u_name;
  int n, number_of_time_steps, size, status;
  const int close_automatically_default = 0, timelapse_default = 50,
            total_colors_default = 100;
  double coefficient_left, coefficient_right, coefficient_bottom,
         coefficient_top;
  const double coefficient_bottom_default = 0.1,
               coefficient_left_default = 0.1,
               coefficient_right_default = 0.1,
               coefficient_top_default = 0.1,
               height_default = 500,
               width_default = 500;
  double * new_coordinates, * u;
  mesh * m;
  struct cmc_graphics_mesh_2d_0_cochain_sequence cochain_sequence;
  struct cmc_animation animation;
  struct cmc_animation_generic_data generic_data;
  margin window_margin;
  frame_mesh_data data;

  cmc_command_line option_animation_backend, option_animation_library,
                    option_canvas_backend, option_canvas_library,
                    option_close_automatically, option_coefficient_bottom,
                    option_coefficient_left, option_coefficient_right,
                    option_coefficient_top, option_height, option_mesh,
                    option_mesh_format, option_output, option_timelapse,
                    option_title, option_total_colors, option_total_steps,
                    option_width, option_u, option_u_format,
                    no_positional_arguments;

  cmc_command_line *(options[]) =
  {
    &option_animation_library,
    &option_animation_backend,
    &option_canvas_library,
    &option_canvas_backend,
    &option_mesh,
    &option_mesh_format,
    &option_u,
    &option_u_format,
    &option_width,
    &option_height,
    &option_title,
    &option_timelapse,
    &option_close_automatically,
    &option_total_steps,
    &option_total_colors,
    &option_output,
    &option_coefficient_left,
    &option_coefficient_right,
    &option_coefficient_top,
    &option_coefficient_bottom,
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
    &option_mesh_format, &m_format, "--mesh-format", "--raw");

  cmc_command_line_set_option_string(&option_mesh, &m_name, "--mesh", NULL);

  cmc_command_line_set_option_string(
    &option_u_format, &u_format, "--cochain-sequence-format", "--raw");

  cmc_command_line_set_option_string(
    &option_u, &u_name, "--cochain-sequence", NULL);

  cmc_command_line_set_option_double(
    &option_width, &(generic_data.width), "--width", &width_default);

  cmc_command_line_set_option_double(
    &option_height, &(generic_data.height), "--height", &height_default);

  cmc_command_line_set_option_int(
    &option_total_steps, &number_of_time_steps,
    "--number-of-time-steps", NULL);

  cmc_command_line_set_option_int(
    &option_total_colors, &(animation.total_colors), "--total-colors",
    &total_colors_default);

  cmc_command_line_set_option_int(
    &option_timelapse, &(animation.timelapse),
    "--timelapse", &timelapse_default);

  cmc_command_line_set_option_string(
    &option_title, &(animation.title), "--title", "0-cochain sequence");

  cmc_command_line_set_option_int(
    &option_close_automatically, &(animation.close_automatically),
    "--close-automatically", &close_automatically_default);

  cmc_command_line_set_option_string(
    &option_output, &output_name, "--output", NULL);
  option_output.minimal_number_of_arguments = 0;

  cmc_command_line_set_option_double(
    &option_coefficient_left, &coefficient_left,
    "--margin-percentage-left",
    &coefficient_left_default);

  cmc_command_line_set_option_double(
    &option_coefficient_right, &coefficient_right,
    "--margin-percentage-right",
    &coefficient_right_default);

  cmc_command_line_set_option_double(
    &option_coefficient_top, &coefficient_top,
    "--margin-percentage-top",
    &coefficient_top_default);

  cmc_command_line_set_option_double(
    &option_coefficient_bottom, &coefficient_bottom,
    "--margin-percentage-bottom",
    &coefficient_bottom_default);

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

  generic_data.total_steps = number_of_time_steps + 1;
  generic_data.new_index = 0;
  animation.generic_data = &generic_data;
  cmc_animation_check_input(&status, &animation);
  if (status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("bad input\n", stderr);
    goto end;
  }

  errno = 0;

  m = mesh_file_scan_by_name(m_name, m_format);
  if (m == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh m from file %s in format %s\n", m_name, m_format);
    status = 1;
    goto end;
  }

  n = generic_data.total_steps;

  u = double_matrix_file_scan_by_name(u_name, n, m->cn[0], u_format);
  if (u == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan cochain sequence u from file %s in format %s\n",
      u_name, u_format);
    status = 1;
    goto m_free;
  }

  new_coordinates = (double *) malloc(sizeof(double) * 2 * m->cn[0]);
  if (new_coordinates == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * 2 * m->cn[0], "new_coordinates");
    status = 1;
    goto u_free;
  }

  window_margin.left = generic_data.width * coefficient_left;
  window_margin.right = generic_data.width * coefficient_right;
  window_margin.top = generic_data.height * coefficient_top;
  window_margin.bottom = generic_data.height * coefficient_bottom;
  data.coordinates = new_coordinates;
  if (m->dim_embedded == 3)
  {
    int i;
    double * m_coord_2d = malloc(sizeof(double) * 2 * m->cn[0]);
    if (m_coord_2d == NULL)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      cmc_error_message_malloc(sizeof(double) * 2 * m->cn[0], "m_coord_2d");
      status = 1;
      goto new_coordinates_free;
    }
    for (i = 0; i < m->cn[0]; ++i)
    {
      m_coord_2d[2 * i] = m->coord[3 * i];
      m_coord_2d[2 * i + 1] = m->coord[3 * i + 1];
    }
    frame_internal_info_for_set_of_points(
      &data,
      m->cn[0],
      m_coord_2d,
      generic_data.width,
      generic_data.height,
      &window_margin);
    free(m_coord_2d);
  }
  /* default case: 2D region in R^2 */
  else
    frame_internal_info_for_set_of_points(
      &data,
      m->cn[0],
      m->coord,
      generic_data.width,
      generic_data.height,
      &window_margin);

  if (data.point_size < 2.5)
    data.point_size = 2.5;

  cochain_sequence.values = u;
  cochain_sequence.coordinates = new_coordinates;
  cochain_sequence.point_sizes = (double *) malloc(sizeof(double) * m->cn[0]);
  if (cochain_sequence.point_sizes == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m->cn[0],
      "cochain_sequence.point_sizes");
    status = 1;
    goto new_coordinates_free;
  }
  double_array_assign_constant(
    cochain_sequence.point_sizes, m->cn[0], data.point_size);
  cochain_sequence.m = m;
  cochain_sequence.line_width = data.line_width / 4;
  cochain_sequence.min_value = double_array_min(n * m->cn[0], u);
  cochain_sequence.max_value = double_array_max(n * m->cn[0], u);

  animation.data = (void *) &cochain_sequence;
  animation.update_new_index = update_index;

  animation.draw_snapshot
  = cmc_graphics_mesh_2d_0_cochain_sequence_draw_snapshot;

  cmc_animation_read_and_apply_backends(
    &animation, &status,
    argc, argv, output_name,
    canvas_library, canvas_backend, animation_library, animation_backend);
  if (status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot read and apply backends\n", stderr);
  }

  free(cochain_sequence.point_sizes);
new_coordinates_free:
  free(new_coordinates);
u_free:
  free(u);
m_free:
  mesh_free(m);
end:
  return status;
}
