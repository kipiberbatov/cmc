#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "diffusion_steady_state_discrete_flow_rate_from_potential.h"
#include "cmc_command_line.h"
#include "int.h"
#include "mesh.h"

struct problem_options
{
  cmc_command_line * dual_conductivity_format;
  cmc_command_line * dual_conductivity_name;
  cmc_command_line * mesh_format;
  cmc_command_line * mesh_name;
  cmc_command_line * mesh_hodge_format;
  cmc_command_line * mesh_hodge_name;
  cmc_command_line * potential_format;
  cmc_command_line * potential_name;
  cmc_command_line * output_format;
  cmc_command_line * output_name;
  cmc_command_line * no_positional_arguments;
};

#define SIZE ((int) (sizeof(struct problem_options) / sizeof(size_t)))

struct problem_arguments
{
  char * dual_conductivity_format;
  char * dual_conductivity_name;
  char * m_format;
  char * m_name;
  char * m_hodge_format;
  char * m_hodge_name;
  char * potential_format;
  char * potential_name;
  char * output_format;
  char * output_name;
};

static void problem_options_set(
  struct problem_options * options,
  struct problem_arguments * arguments)
{
  cmc_command_line_set_option_string(
    options->mesh_format, &(arguments->m_format), "--mesh-format", "--raw");

  cmc_command_line_set_option_string(
    options->mesh_name, &(arguments->m_name), "--mesh", NULL);

  cmc_command_line_set_option_string(
    options->mesh_hodge_format, &(arguments->m_hodge_format),
    "--hodge-star-format", "--raw");

  cmc_command_line_set_option_string(
    options->mesh_hodge_name, &(arguments->m_hodge_name), "--hodge-star", NULL);

  cmc_command_line_set_option_string(
    options->dual_conductivity_format, &(arguments->dual_conductivity_format),
    "--dual-conductivity-format", "--steady-state-dual-conductivity-raw");

  cmc_command_line_set_option_string(
    options->dual_conductivity_name, &(arguments->dual_conductivity_name),
    "--dual-conductivity", NULL);

  cmc_command_line_set_option_string(
    options->potential_format, &(arguments->potential_format),
    "--potential-format", "--raw");

  cmc_command_line_set_option_string(
    options->potential_name, &(arguments->potential_name), "--potential", NULL);

  cmc_command_line_set_option_string(
    options->output_format, &(arguments->output_format),
    "--output-format", "--raw");

  cmc_command_line_set_option_string(
    options->output_name, &(arguments->output_name), "--output", NULL);
  options->output_name->minimal_number_of_arguments = 0;

  /* there are no positional arguments */
  cmc_command_line_set_option_no_arguments(
    options->no_positional_arguments, NULL, NULL, NULL);
}

static void
arguments_run(const struct problem_arguments * arguments, int * status)
{
  int d;
  int * m_cn;
  double * flow_rate, * dual_conductivity, * potential;
  FILE * m_file, * output_file;
  struct mesh * m;
  struct matrix_sparse * m_bd_1;
  struct matrix_sparse ** m_hodge;

  m_file = fopen(arguments->m_name, "r");
  if (m_file == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open mesh file %s for reading: %s\n",
      arguments->m_name, strerror(errno));
    *status = errno;
    goto end;
  }
  m = mesh_file_scan(m_file, arguments->m_format);
  if (m == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh m from file %s in format %s\n",
      arguments->m_name, arguments->m_format);
    fclose(m_file);
    *status = errno;
    goto end;
  }

  d = m->dim;
  m_cn = m->cn;

  m_bd_1 = mesh_file_scan_boundary_p(m_file, m, 1);
  if (m_bd_1 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan m_bd_1 from file %s\n", arguments->m_name);
    fclose(m_file);
    *status = errno;
    goto m_free;
  }
  fclose(m_file);

  m_hodge = matrix_sparse_array_file_scan_by_name(
    arguments->m_hodge_name, 2, arguments->m_hodge_format);
  if (m_hodge == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan m_hodge form file %s in format %s\n",
      arguments->m_hodge_name, arguments->m_hodge_format);
    *status = errno;
    goto m_bd_1_free;
  }

  dual_conductivity = double_array_file_scan_by_name(
    arguments->dual_conductivity_name,
    m_cn[1],
    arguments->dual_conductivity_format);
  if (dual_conductivity == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan dual_conductivity form file %s%s%s in format %s%s%s\n",
      color_variable, arguments->dual_conductivity_name, color_none,
      color_variable, arguments->dual_conductivity_format, color_none);
    *status = errno;
    goto m_hodge_free;
  }

  potential = double_array_file_scan_by_name(
    arguments->potential_name, m_cn[0], arguments->potential_format);
  if (potential == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan potential form file %s in format %s\n",
      arguments->potential_name, arguments->potential_format);
    *status = errno;
    goto dual_conductivity_free;
  }

  flow_rate = (double *) calloc(m_cn[d - 1], sizeof(double));
  if (flow_rate == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m_cn[d - 1], "flow_rate");
    *status = errno;
    goto potential_free;
  }

  diffusion_steady_state_discrete_flow_rate_from_potential(
    flow_rate, m, m_bd_1, dual_conductivity, potential, m_hodge[1]);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate flow_rate %s\n", stderr);
    *status = errno;
    goto flow_rate_free;
  }

  if (arguments->output_name == NULL)
  {
    output_file = stdout;
  }
  else
  {
    output_file = fopen(arguments->output_name, "w");
    if (output_file == NULL)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr,
        "cannot open output file %s: %s\n",
        arguments->output_name, strerror(errno));
      *status = errno;
      goto potential_free;
    }
  }

  double_array_file_print(
    output_file, m_cn[d - 1], flow_rate, arguments->output_format);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("failed to print\n", stderr);
    *status = errno;
    if (arguments->output_name != NULL)
      fclose(output_file);
    goto potential_free;
  } 
  if (arguments->output_name != NULL)
    fclose(output_file);

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
  return;
}

int main(int argc, char ** argv)
{
  int status = 0;
  cmc_command_line options_list[SIZE];
  struct problem_options options;
  struct problem_arguments arguments;

  cmc_command_line_bind((cmc_command_line **) &options, options_list, SIZE);
  problem_options_set(&options, &arguments);

  cmc_command_line_parse(
    (cmc_command_line **) &options, &status, SIZE, argc, argv);
  if (status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot parse command line options\n", stderr);
    goto end;
  }

  arguments_run(&arguments, &status);
  if (status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("failed to execute\n", stderr);
    goto end;
  }

end:
  return status;
}
