#ifndef _cmc_diffusion_steady_state_discrete_flow_rate_primal_options__struct_h
#define _cmc_diffusion_steady_state_discrete_flow_rate_primal_options__struct_h

struct cmc_command_line;

struct cmc_diffusion_steady_state_discrete_flow_rate_primal_options
{
  struct cmc_command_line * dual_conductivity_format;
  struct cmc_command_line * dual_conductivity_name;
  struct cmc_command_line * mesh_format;
  struct cmc_command_line * mesh_name;
  struct cmc_command_line * mesh_hodge_format;
  struct cmc_command_line * mesh_hodge_name;
  struct cmc_command_line * potential_format;
  struct cmc_command_line * potential_name;
  struct cmc_command_line * output_format;
  struct cmc_command_line * output_name;
  struct cmc_command_line * no_positional_arguments;
};

#endif /* _cmc_diffusion_steady_state_discrete_flow_rate_primal_options__struct_h */
