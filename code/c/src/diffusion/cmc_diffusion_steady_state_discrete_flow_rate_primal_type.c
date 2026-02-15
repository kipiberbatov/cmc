#include "cmc_diffusion_steady_state_discrete_flow_rate_primal__struct.h"
#include "cmc_diffusion_steady_state_discrete_flow_rate_primal_arguments__struct.h"
#include "cmc_diffusion_steady_state_discrete_flow_rate_primal_options__struct.h"
#include "cmc_diffusion_steady_state_discrete_flow_rate_primal_options_set.h"
#include "cmc_file_open_output_channel.h"
#include "cmc_file_close_output_channel.h"
#include "cmc_main_type__struct.h"

extern const struct cmc_main_compute_and_print
cmc_diffusion_steady_state_discrete_flow_rate_primal_compute_and_print;

static char * get_output_channel_name(const struct
  cmc_diffusion_steady_state_discrete_flow_rate_primal_arguments * arguments)
{
  return arguments->output_name;
}

static char * get_output_channel_format(const struct
  cmc_diffusion_steady_state_discrete_flow_rate_primal_arguments * arguments)
{
  return arguments->output_format;
}

static void do_nothing(void * p){}

const struct cmc_main_type
cmc_diffusion_steady_state_discrete_flow_rate_primal_type =
{
  sizeof(struct cmc_diffusion_steady_state_discrete_flow_rate_primal_options)
  / sizeof(size_t),
  (void (*)(struct cmc_command_line **, void *)) cmc_diffusion_steady_state_discrete_flow_rate_primal_options_set,
  (char * (*)(const void *)) get_output_channel_name,
  (char * (*)(const void *)) get_output_channel_format,
  (void (*)(void **, int *, const char * )) cmc_file_open_output_channel,
  &cmc_diffusion_steady_state_discrete_flow_rate_primal_compute_and_print,
  (void (*)(void *, int *)) cmc_file_close_output_channel,
  do_nothing
};
