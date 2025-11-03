#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "double_array2.h"
#include "double_matrix.h"
#include "diffusion_transient_discrete_mixed_weak.h"
#include "cmc_command_line.h"
#include "int.h"
#include "mesh.h"

int main(int argc, char ** argv)
{
  char * data_name, * m_inner_format, * m_inner_name, * m_format, * m_name;
  int d, m_cn_dm1, m_cn_d, number_of_steps, size, status;
  int * m_cn;
  double time_step;
  double * dual_potential, * flow_rate;
  double ** m_inner;
  FILE * data_file, * m_file;
  struct matrix_sparse * m_cbd_dm1;
  struct matrix_sparse ** m_bd;
  struct mesh * m;
  struct diffusion_transient_discrete_mixed_weak * data;

  cmc_command_line no_positional_arguments, option_input_data, option_mesh,
                    option_mesh_format, option_mesh_inner,
                    option_mesh_inner_format, option_number_of_steps,
                    option_time_step;

  cmc_command_line *(options[]) =
  {
    &option_mesh,
    &option_mesh_format,
    &option_mesh_inner,
    &option_mesh_inner_format,
    &option_input_data,
    &option_time_step,
    &option_number_of_steps,
    &no_positional_arguments
  };

  cmc_command_line_set_option_string(
    &option_mesh_format, &m_format, "--mesh-format", "--raw");

  cmc_command_line_set_option_string(&option_mesh, &m_name, "--mesh", NULL);

  cmc_command_line_set_option_string(
    &option_mesh_inner_format, &m_inner_format, "--mesh-inner-format", "--raw");

  cmc_command_line_set_option_string(
    &option_mesh_inner, &m_inner_name, "--mesh-inner", NULL);

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
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot parse command line options\n", stderr);
    return status;
  }

  if (time_step <= 0.)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "the time step is %g but it must be positive\n", time_step);
    goto end;
  }

  if (number_of_steps < 0)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "the number of steps is %d but it must be at least 0\n",
      number_of_steps);
    goto end;
  }

  m_file = fopen(m_name, "r");
  if (m_file == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot open mesh file %s: %s\n", m_name, strerror(errno));
    goto end;
  }

  m = mesh_file_scan(m_file, m_format);
  if (m == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh m from file %s in format %s\n", m_name, m_format);
    fclose(m_file);
    goto end;
  }

  m->fc = mesh_fc(m);
  if (m->fc == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m->fc\n", stderr);
    goto m_free;
  }

  m_bd = mesh_file_scan_boundary(m_file, m);
  if (m_bd == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan m_bd\n", stderr);
    fclose(m_file);
    goto m_free;
  }

  fclose(m_file);

  d = m->dim;
  m_cn = m->cn;
  m_cn_dm1 = m_cn[d - 1];
  m_cn_d = m_cn[d];

  m_cbd_dm1 = matrix_sparse_transpose(m_bd[d - 1]);
  if (m_cbd_dm1 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m->fc\n", stderr);
    goto m_bd_free;
  }

  m_inner = double_array2_file_scan_by_name(
    m_inner_name, d + 1, m_cn, m_inner_format);
  if (m_inner == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan inner products from file %s in format %s\n",
      m_inner_name, m_inner_format);
    goto m_cbd_dm1_free;
  }

  data_file = fopen(data_name, "r");
  if (data_file == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open problem data file %s for reading: %s\n",
      data_name, strerror(errno));
    goto m_inner_free;
  }
  data = diffusion_transient_discrete_mixed_weak_file_scan_raw(data_file);
  if (data == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan problem data from file %s\n", data_name);
    fclose(data_file);
    goto m_inner_free;
  }
  fclose(data_file);

  flow_rate
  = (double *) malloc(sizeof(double) * (number_of_steps + 1) * m_cn_dm1);
  if (flow_rate == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * (number_of_steps + 1) * m_cn_dm1,
      "flow_rate");
    goto data_free;
  }

  dual_potential = (double *) malloc(
    sizeof(double) * (number_of_steps + 1) * m_cn_d);
  if (dual_potential == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * (number_of_steps + 1) * m_cn_d,
      "dual_potential");
    goto flow_rate_free;
  }

  diffusion_transient_discrete_mixed_weak_solve_trapezoidal(
    flow_rate, dual_potential,
    m, m_cbd_dm1, m_inner[d - 1], m_inner[d], data, time_step, number_of_steps);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot find flow_rate and dual_potential\n", stderr);
    goto dual_potential_free;
  }

  double_matrix_file_print(
    stdout, number_of_steps + 1, m_cn_dm1, flow_rate, "--raw");
  fputc('\n', stdout);
  double_matrix_file_print(
    stdout, number_of_steps + 1, m_cn_d, dual_potential, "--raw");

dual_potential_free:
  free(dual_potential);
flow_rate_free:
  free(flow_rate);
data_free:
  diffusion_transient_discrete_mixed_weak_free(data);
m_inner_free:
  double_array2_free(m_inner, d + 1);
m_cbd_dm1_free:
  matrix_sparse_free(m_cbd_dm1);
m_bd_free:
  matrix_sparse_array_free(m_bd, d);
m_free:
  mesh_free(m);
end:
  return errno;
}
