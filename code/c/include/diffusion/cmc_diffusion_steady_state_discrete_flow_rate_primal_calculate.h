struct cmc_diffusion_steady_state_discrete_flow_rate_primal;
struct cmc_double_array;

void cmc_diffusion_steady_state_discrete_flow_rate_primal_calculate(
  struct cmc_double_array * data,
  int * status,
  const struct
    cmc_diffusion_steady_state_discrete_flow_rate_primal * input);
