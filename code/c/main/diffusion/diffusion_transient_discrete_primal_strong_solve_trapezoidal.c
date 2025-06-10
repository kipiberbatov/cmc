#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <dlfcn.h>

#include "color.h"
#include "double_matrix.h"
#include "diffusion_transient_discrete_primal_strong.h"
#include "cmc_command_line.h"
#include "int.h"
#include "mesh.h"

int main(int argc, char ** argv)
{
  char * data_name, * m_cbd_0_name, * m_cbd_star_1_name, * m_format, * m_name;
  int number_of_steps, size, status;
  double time_step;
  double * potential;
  FILE * data_file, * m_cbd_star_1_file;
  struct matrix_sparse * m_cbd_0, * m_cbd_star_1;
  struct mesh * m;
  struct diffusion_transient_discrete_primal_strong * data;

  cmc_command_line no_positional_arguments, option_input_data, option_mesh,
                    option_mesh_format, option_mesh_cbd_0,
                    option_mesh_cbd_star_1, option_number_of_steps,
                    option_time_step;

  cmc_command_line *(options[]) =
  {
    &option_mesh,
    &option_mesh_format,
    &option_mesh_cbd_0,
    &option_mesh_cbd_star_1,
    &option_input_data,
    &option_time_step,
    &option_number_of_steps,
    &no_positional_arguments
  };

  cmc_command_line_set_option_string(
    &option_mesh_format, &m_format, "--mesh-format", "--raw");

  cmc_command_line_set_option_string(&option_mesh, &m_name, "--mesh", NULL);

  cmc_command_line_set_option_string(
    &option_mesh_cbd_0, &m_cbd_0_name, "--mesh-coboundary-0", NULL);

  cmc_command_line_set_option_string(
    &option_mesh_cbd_star_1, &m_cbd_star_1_name,
    "--mesh-coboundary-star-1", NULL);

  cmc_command_line_set_option_string(
    &option_input_data, &data_name, "--input-data", NULL);

  cmc_command_line_set_option_double(&option_time_step, &time_step,
    "--time-step", NULL);

  cmc_command_line_set_option_int(
    &option_number_of_steps, &number_of_steps, "--number-of-steps", NULL);

  /* there are no positional arguments */
  cmc_command_line_set_option_no_arguments(
    &no_positional_arguments, NULL, NULL, NULL);

  size = (int) (sizeof(options) / sizeof(*options));
  status = 0;
  cmc_command_line_parse(options, &status, size, argc, argv);
  if (status)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot parse command line options\n", stderr);
    return status;
  }

  if (time_step <= 0.)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "the time step is %g but it must be positive\n", time_step);
    goto end;
  }

  if (number_of_steps < 0)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "the number of steps is %d but it must be at least 0\n", number_of_steps);
    goto end;
  }

  m = mesh_file_scan_by_name(m_name, m_format);
  if (m == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh m from file %s in format %s\n",
      m_name, m_format);
    goto end;
  }

  m->fc = mesh_fc(m);
  if (m->fc == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate m->fc\n", stderr);
    goto m_free;
  }

  m_cbd_0 = matrix_sparse_file_scan_by_name(m_cbd_0_name, "--raw");
  if (m_cbd_0 == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan m_cbd[0] from file %s in format %s\n",
      m_cbd_0_name, "--raw");
    goto m_free;
  }

  m_cbd_star_1_file = fopen(m_cbd_star_1_name, "r");
  if (m_cbd_star_1_file == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open file %s: %s\n",
      m_cbd_star_1_name, strerror(errno));
    goto m_cbd_0_free;
  }
  m_cbd_star_1 = mesh_file_scan_boundary_p(m_cbd_star_1_file, m, 1);
  if (m_cbd_star_1 == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan m_cbd_star_1 from file %s\n",
      m_cbd_star_1_name);
    fclose(m_cbd_star_1_file);
    goto m_cbd_0_free;
  }
  fclose(m_cbd_star_1_file);

  data_file = fopen(data_name, "r");
  if (data_file == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open problem data file %s: %s\n", data_name, strerror(errno));
    goto m_cbd_star_1_free;
  }
  data = diffusion_transient_discrete_primal_strong_file_scan_raw(data_file);
  if (data == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan problem data from file %s\n", data_name);
    fclose(data_file);
    goto m_cbd_star_1_free;
  }
  fclose(data_file);

  potential = diffusion_transient_discrete_primal_strong_solve_trapezoidal(
    m, m_cbd_0, m_cbd_star_1, data, time_step, number_of_steps);
  // potential = (double *) calloc(
  //   (number_of_steps + 1) * m->cn[0], sizeof(double));
  if (potential == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate potential\n", stderr);
    goto data_free;
  }

  double_matrix_file_print(
    stdout, number_of_steps + 1, m->cn[0], potential, "--raw");

  free(potential);
data_free:
  diffusion_transient_discrete_primal_strong_free(data);
m_cbd_star_1_free:
  matrix_sparse_free(m_cbd_star_1);
m_cbd_0_free:
  matrix_sparse_free(m_cbd_0);
m_free:
  mesh_free(m);
end:
  return errno;
}
