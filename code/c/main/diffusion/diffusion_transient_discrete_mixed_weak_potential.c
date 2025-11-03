#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "diffusion_transient_discrete_mixed_weak.h"
#include "double_array.h"
#include "double_array2.h"
#include "double_matrix.h"
#include "cmc_command_line.h"
#include "int.h"
#include "mesh_qc.h"

int main(int argc, char ** argv)
{
  char * data_name, * m_vol_format, * m_vol_name, * m_format, * m_name,
       * solution_name;
  int d, m_cn_dm1, m_cn_0, m_cn_d, number_of_steps, s, size, status;
  int * m_cn;
  double * flow_rate, * potential, * dual_potential;
  double ** m_vol;
  FILE * data_file, * m_file, * solution_file;
  struct mesh * m;
  struct diffusion_transient_discrete_mixed_weak * data;

  cmc_command_line no_positional_arguments, option_input_data, option_mesh,
                    option_mesh_format, option_mesh_vol, option_mesh_vol_format,
                    option_number_of_steps, option_solution;

  cmc_command_line *(options[]) =
  {
    &option_mesh_format,
    &option_mesh,
    &option_mesh_vol_format,
    &option_mesh_vol,
    &option_input_data,
    &option_number_of_steps,
    &option_solution,
    &no_positional_arguments
  };

  cmc_command_line_set_option_string(
    &option_mesh_format, &m_format, "--mesh-format", "--raw");

  cmc_command_line_set_option_string(&option_mesh, &m_name, "--mesh", NULL);

  cmc_command_line_set_option_string(
    &option_mesh_vol_format, &m_vol_format, "--mesh-volumes-format", "--raw");

  cmc_command_line_set_option_string(
    &option_mesh_vol, &m_vol_name, "--mesh-volumes", NULL);

  cmc_command_line_set_option_string(
    &option_input_data, &data_name, "--input-data", NULL);

  cmc_command_line_set_option_int(
    &option_number_of_steps, &number_of_steps, "--number-of-steps", NULL);

  cmc_command_line_set_option_string(
    &option_solution, &solution_name, "--solution", NULL);

  /* there are no positional arguments */
  cmc_command_line_set_option_no_arguments(
    &no_positional_arguments, NULL, NULL, NULL);

  size = (int) (sizeof(options) / sizeof(*options));
  status = 0;
  cmc_command_line_parse(options, &status, size, argc, argv);
  if (status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot parse command line options\n", stderr);
    return status;
  }

  if (number_of_steps < 0)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "the number of steps is %d but it must be at least 0\n", number_of_steps);
    goto end;
  }

  m_file = fopen(m_name, "r");
  if (m_file == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot open mesh file %s: %s\n", m_name, strerror(errno));
    goto end;
  }

  m = mesh_file_scan_by_name(m_name, m_format);
  if (m == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh m from file %s in format %s\n", m_name, m_format);
    goto end;
  }

  d = m->dim;
  m_cn = m->cn;
  m_cn_0 = m_cn[0];
  m_cn_dm1 = m_cn[d - 1];
  m_cn_d = m_cn[d];

  m->fc = mesh_fc(m);
  if (m->fc == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m->fc\n", stderr);
    goto m_free;
  }

  m_vol = double_array2_file_scan_by_name(
    m_vol_name, d + 1, m_cn, m_vol_format);
  if (m_vol == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan cells' measures from file %s in format %s\n",
      m_vol_name, m_vol_format);
    goto m_free;
  }

  data_file = fopen(data_name, "r");
  if (data_file == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open problem data file %s: %s\n", data_name, strerror(errno));
    goto m_vol_free;
  }
  data = diffusion_transient_discrete_mixed_weak_file_scan_raw(data_file);
  if (data == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan problem data from file %s\n", data_name);
    fclose(data_file);
    goto m_vol_free;
  }
  fclose(data_file);

  solution_file = fopen(solution_name, "r");
  if (solution_file == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open problem solution file %s: %s\n",
      solution_name, strerror(errno));
    goto data_free;
  }

  flow_rate = double_matrix_file_scan(solution_file,
    number_of_steps + 1, m_cn_dm1, "--raw");
  if (flow_rate == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan flow_rate from file %s in format --raw\n", solution_name);
    fclose(solution_file);
    goto data_free;
  }
  free(flow_rate);

  dual_potential = double_matrix_file_scan(solution_file,
    number_of_steps + 1, m_cn_d, "--raw");
  if (dual_potential == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan dual_potential from file in format --raw %s\n",
      solution_name);
    fclose(solution_file);
    goto data_free;
  }
  fclose(solution_file);

  potential = (double *) malloc(
    sizeof(double) * (number_of_steps + 1) * m_cn_0);
  if (potential == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * (number_of_steps + 1) * m_cn_0,
      "potential");
    goto dual_potential_free;
  }

  for (s = 0; s <= number_of_steps; ++s)
  {
    mesh_qc_hodge_star_d(potential + m_cn_0 * s,
      m, m_vol[d], dual_potential + m_cn_d * s);
    double_array_assemble_from_sparse_array(
      potential + m_cn_0 * s, data->boundary_dirichlet_0, data->g_dirichlet_0);
  }

  double_matrix_file_print(stdout,
    number_of_steps + 1, m_cn_0, potential, "--raw");

  free(potential);
dual_potential_free:
  free(dual_potential);
data_free:
  diffusion_transient_discrete_mixed_weak_free(data);
m_vol_free:
  double_array2_free(m_vol, d + 1);
m_free:
  mesh_free(m);
end:
  return errno;
}
