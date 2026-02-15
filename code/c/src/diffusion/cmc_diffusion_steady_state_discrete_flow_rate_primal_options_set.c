#include "cmc_command_line.h"
#include "cmc_diffusion_steady_state_discrete_flow_rate_primal_arguments__struct.h"
#include "cmc_diffusion_steady_state_discrete_flow_rate_primal_options__struct.h"
#include "cmc_diffusion_steady_state_discrete_flow_rate_primal_options_set.h"

void cmc_diffusion_steady_state_discrete_flow_rate_primal_options_set(
  struct cmc_diffusion_steady_state_discrete_flow_rate_primal_options * options,
  struct cmc_diffusion_steady_state_discrete_flow_rate_primal_arguments *
    arguments)
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
