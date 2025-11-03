#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "diffusion_steady_state_discrete_flow_rate_from_potential.h"
#include "cmc_command_line.h"
#include "int.h"
#include "mesh.h"

int main(int argc, char ** argv)
{
  char * dual_conductivity_format, * dual_conductivity_name, * m_format,
       * m_name, * m_hodge_format, * m_hodge_name, * potential_format,
       * potential_name, * output_format, * output_name;
  int d, size, status;
  int * m_cn;
  double * flow_rate, * dual_conductivity, * potential;
  FILE * m_file, * output_file;
  struct mesh * m;
  struct matrix_sparse * m_bd_1;
  struct matrix_sparse ** m_hodge;

  cmc_command_line
    option_dual_conductivity_format,
    option_dual_conductivity_name,
    option_mesh_format,
    option_mesh_name,
    option_mesh_hodge_format,
    option_mesh_hodge_name,
    option_no_positional_arguments,
    option_output_format,
    option_output_name,
    option_potential_format,
    option_potential_name;

  cmc_command_line *(options[]) =
  {
    &option_mesh_format,
    &option_mesh_name,
    &option_mesh_hodge_format,
    &option_mesh_hodge_name,
    &option_dual_conductivity_format,
    &option_dual_conductivity_name,
    &option_potential_format,
    &option_potential_name,
    &option_output_format,
    &option_output_name,
    &option_no_positional_arguments
  };

  cmc_command_line_set_option_string(
    &option_mesh_format, &m_format, "--mesh-format", "--raw");

  cmc_command_line_set_option_string(
    &option_mesh_name, &m_name, "--mesh", NULL);

  cmc_command_line_set_option_string(
    &option_mesh_hodge_format, &m_hodge_format,
    "--hodge-star-format", "--raw");

  cmc_command_line_set_option_string(
    &option_mesh_hodge_name, &m_hodge_name, "--hodge-star", NULL);

  cmc_command_line_set_option_string(
    &option_dual_conductivity_format, &dual_conductivity_format,
    "--dual-conductivity-format", "--steady-state-dual-conductivity-raw");

  cmc_command_line_set_option_string(
    &option_dual_conductivity_name, &dual_conductivity_name,
    "--dual-conductivity", NULL);

  cmc_command_line_set_option_string(
    &option_potential_format, &potential_format, "--potential-format", "--raw");

  cmc_command_line_set_option_string(
    &option_potential_name, &potential_name, "--potential", NULL);

  cmc_command_line_set_option_string(
    &option_output_format, &output_format, "--output-format", "--raw");

  cmc_command_line_set_option_string(
    &option_output_name, &output_name, "--output", NULL);
  option_output_name.minimal_number_of_arguments = 0;

  /* there are no positional arguments */
  cmc_command_line_set_option_no_arguments(
    &option_no_positional_arguments, NULL, NULL, NULL);

  size = (int) (sizeof(options) / sizeof(*options));
  status = 0;
  cmc_command_line_parse(options, &status, size, argc, argv);
  if (status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot parse command line options\n", stderr);
    return status;
  }

  m_file = fopen(m_name, "r");
  if (m_file == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open mesh file %s for reading: %s\n",
      m_name, strerror(errno));
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
  m_cn = m->cn;

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
    m_hodge_name, 2, m_hodge_format);
  if (m_hodge == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan m_hodge form file %s in format %s\n",
      m_hodge_name, m_hodge_format);
    goto m_bd_1_free;
  }

  dual_conductivity = double_array_file_scan_by_name(
    dual_conductivity_name, m_cn[1], dual_conductivity_format);
  if (dual_conductivity == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan dual_conductivity form file %s%s%s in format %s%s%s\n",
      color_variable, dual_conductivity_name, color_none,
      color_variable, dual_conductivity_format, color_none);
    goto m_hodge_free;
  }

  potential = double_array_file_scan_by_name(
    potential_name, m_cn[0], potential_format);
  if (potential == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan potential form file %s in format %s\n",
      potential_name, potential_format);
    goto dual_conductivity_free;
  }

  flow_rate = (double *) calloc(m_cn[d - 1], sizeof(double));
  if (flow_rate == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m_cn[d - 1], "flow_rate");
    goto potential_free;
  }

  diffusion_steady_state_discrete_flow_rate_from_potential(
    flow_rate, m, m_bd_1, dual_conductivity, potential, m_hodge[1]);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate flow_rate %s\n", stderr);
    goto flow_rate_free;
  }

  if (output_name == NULL)
  {
    double_array_file_print(stdout, m_cn[d - 1], flow_rate, output_format);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fputs("failed to print\n", stderr);
      status = errno;
      goto potential_free;
    }
  }
  else
  {
    output_file = fopen(output_name, "w");
    if (output_file == NULL)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr,
        "cannot open output file %s: %s\n",
        output_name, strerror(errno));
      status = errno;
      goto potential_free;
    }
    double_array_file_print(output_file, m_cn[d - 1], flow_rate, output_format);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fputs("failed to print\n", stderr);
      status = errno;
      fclose(output_file);
      goto potential_free;
    }
    fclose(output_file);
  }

flow_rate_free:
  free(flow_rate);
potential_free:
  free(potential);
dual_conductivity_free:
  free(dual_conductivity);
m_hodge_free:
  matrix_sparse_array_free(m_hodge, 2);
m_bd_1_free:
  matrix_sparse_free(m_bd_1);
m_free:
  mesh_free(m);
end:
  return errno;
}
