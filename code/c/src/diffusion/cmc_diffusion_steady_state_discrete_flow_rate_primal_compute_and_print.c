#include "cmc_diffusion_steady_state_discrete_flow_rate_primal_calculate.h"
#include "cmc_diffusion_steady_state_discrete_flow_rate_primal_free_values.h"
#include "cmc_diffusion_steady_state_discrete_flow_rate_primal_scan_input.h"
#include "cmc_double_array_file_print.h"
#include "cmc_double_array_free_values.h"
#include "cmc_main_compute_and_print__struct.h"
#include "cmc_main_compute_and_print_functions_one_pass__struct.h"

static const struct cmc_main_compute_and_print_functions_one_pass
cmc_diffusion_steady_state_discrete_flow_rate_primal_one_pass =
{
  (void (*)(void *, int *, const void *))
    cmc_diffusion_steady_state_discrete_flow_rate_primal_scan_input,
  (void (*)(void *, int *, const void *))
    cmc_diffusion_steady_state_discrete_flow_rate_primal_calculate,
  (void (*)(void *))
    cmc_diffusion_steady_state_discrete_flow_rate_primal_free_values,
  (void (*)(void *, int *, const void *, const char *))
    cmc_double_array_file_print,
  (void (*)(void *)) cmc_double_array_free_values
};

const struct cmc_main_compute_and_print
cmc_diffusion_steady_state_discrete_flow_rate_primal_compute_and_print =
{
  .id = cmc_main_compute_and_print_id_one_pass,
  .functions.one_pass =
    &cmc_diffusion_steady_state_discrete_flow_rate_primal_one_pass
};
