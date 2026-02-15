#include "cmc_command_line.h"
#include "cmc_diffusion_steady_state_discrete_flow_rate_primal__struct.h"
#include "cmc_diffusion_steady_state_discrete_flow_rate_primal_arguments__struct.h"
#include "cmc_diffusion_steady_state_discrete_flow_rate_primal_options__struct.h"
#include "cmc_double_array__struct.h"
#include "cmc_error_message.h"
#include "cmc_main__struct.h"
#include "cmc_main_run.h"
#include "cmc_main_state__struct.h"

extern const struct cmc_main_type
cmc_diffusion_steady_state_discrete_flow_rate_primal_type;

int main(int argc, char ** argv)
{
  enum
  {
    SIZE =
    sizeof(struct cmc_diffusion_steady_state_discrete_flow_rate_primal_options)
    / sizeof(size_t)
  };
  struct cmc_command_line options_list[SIZE];
  struct cmc_diffusion_steady_state_discrete_flow_rate_primal_options options;
  struct cmc_diffusion_steady_state_discrete_flow_rate_primal_arguments
    arguments;
  struct cmc_diffusion_steady_state_discrete_flow_rate_primal input;
  struct cmc_double_array data;
  struct cmc_main_state state =
  {
    options_list,
    (struct cmc_command_line **) &options,
    (void *) &arguments,
    (void *) &input,
    (void *) &data
  };
  struct cmc_main runner =
  {
    &cmc_diffusion_steady_state_discrete_flow_rate_primal_type,
    &state
  };
  int status = 0;

  cmc_main_run(&runner, &status, argc, argv);
  if (status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_string("failed to execute\n");
  }
  return status;
}
