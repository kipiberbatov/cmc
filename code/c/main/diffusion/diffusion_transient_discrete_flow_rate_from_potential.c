#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "double_matrix.h"
#include "diffusion_transient_discrete_flow_rate_from_potential.h"
#include "cmc_command_line.h"
#include "int.h"
#include "mesh.h"

int main(int argc, char ** argv)
{
  char * flow_rate_format, * kappa_1_format, * kappa_1_name, * m_format,
       * m_name, * m_hodge_format, * m_hodge_name, * potential_format,
       * potential_name;
  int d, m_cn_dm1, number_of_steps, size, status;
  double * flow_rate, * kappa_1, * potential;
  FILE * m_file;
  struct mesh * m;
  struct matrix_sparse * m_bd_1;
  struct matrix_sparse ** m_hodge;

  cmc_command_line no_positional_arguments, option_flow_rate_format,
                    option_kappa_1, option_kappa_1_format, option_mesh,
                    option_mesh_format, option_mesh_hodge,
                    option_mesh_hodge_format, option_number_of_steps,
                    option_potential_format, option_potential;

  cmc_command_line *(options[]) =
  {
    &option_mesh_format,
    &option_mesh,
    &option_mesh_hodge,
    &option_mesh_hodge_format,
    &option_kappa_1,
    &option_kappa_1_format,
    &option_potential,
    &option_potential_format,
    &option_number_of_steps,
    &option_flow_rate_format,
    &no_positional_arguments
  };

  cmc_command_line_set_option_string(&option_mesh, &m_name, "--mesh", NULL);

  cmc_command_line_set_option_string(
    &option_mesh_format, &m_format, "--mesh-format", "--raw");

  cmc_command_line_set_option_string(
    &option_mesh_hodge_format, &m_hodge_format, "--mesh-hodge-format", "--raw");

  cmc_command_line_set_option_string(
    &option_mesh_hodge, &m_hodge_name, "--mesh-hodge", NULL);

  cmc_command_line_set_option_string(
    &option_kappa_1_format, &kappa_1_format, "--kappa-1-format", NULL);

  cmc_command_line_set_option_string(
    &option_kappa_1, &kappa_1_name, "--kappa-1", NULL);

  cmc_command_line_set_option_string(
    &option_potential_format, &potential_format, "--potential-format", "--raw");

  cmc_command_line_set_option_string(
    &option_potential, &potential_name, "--potential", NULL);

  cmc_command_line_set_option_int(
    &option_number_of_steps, &number_of_steps, "--number-of-steps", NULL);

  cmc_command_line_set_option_string(
    &option_flow_rate_format, &flow_rate_format, "--flow_rate-format", "--raw");

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
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot open mesh file %s\n", m_name);
    goto end;
  }
  m = mesh_file_scan(m_file, m_format);
  if (m == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh m from file %s in format %s\n",
      m_name, m_format);
    fclose(m_file);
    goto end;
  }
  d = m->dim;
  m_cn_dm1 = m->cn[d - 1];

  m_bd_1 = mesh_file_scan_boundary_p(m_file, m, 1);
  if (m_bd_1 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan m_bd_1 from file %s\n", m_name);
    fclose(m_file);
    goto m_free;
  }
  fclose(m_file);

  m_hodge = matrix_sparse_array_file_scan_by_name(
    m_hodge_name, m->dim + 1, m_hodge_format);
  if (m_hodge == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan m_hodge form file %s in format %s\n",
      m_hodge_name, m_hodge_format);
    goto m_bd_1_free;
  }

  kappa_1 = double_array_file_scan_by_name(
    kappa_1_name, m->cn[1],kappa_1_format);
  if (kappa_1 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan kappa_1 form file %s in format %s\n",
      kappa_1_name, kappa_1_format);
    goto m_hodge_free;
  }

  potential = double_matrix_file_scan_by_name(
    potential_name, number_of_steps + 1, m->cn[0], potential_format);
  if (potential == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan potential form file %s in format %s\n",
      potential_name, potential_format);
    goto kappa_1_free;
  }

  flow_rate
  = (double *) calloc((number_of_steps + 1) * m_cn_dm1, sizeof(double));
  if (flow_rate == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(
      sizeof(double) * (number_of_steps + 1) * m_cn_dm1, "flow_rate");
    goto potential_free;
  }

  diffusion_transient_discrete_flow_rate_from_potential(
    flow_rate, m, m_bd_1, kappa_1, potential, m_hodge[1], number_of_steps);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate flow_rate %s\n", stderr);
    goto flow_rate_free;
  }

  double_matrix_file_print(
    stdout, number_of_steps + 1, m_cn_dm1, flow_rate, flow_rate_format);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot print flow_rate in format %s\n", flow_rate_format);
    goto flow_rate_free;
  }

flow_rate_free:
  free(flow_rate);
potential_free:
  free(potential);
kappa_1_free:
  free(kappa_1);
m_hodge_free:
  matrix_sparse_array_free(m_hodge, d + 1);
m_bd_1_free:
  matrix_sparse_free(m_bd_1);
m_free:
  mesh_free(m);
end:
  return errno;
}
