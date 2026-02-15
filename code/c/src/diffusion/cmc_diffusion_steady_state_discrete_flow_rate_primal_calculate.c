#include <errno.h>

#include "cmc_diffusion_steady_state_discrete_flow_rate_primal_calculate.h"
#include "cmc_diffusion_steady_state_discrete_flow_rate_primal__struct.h"
#include "cmc_double_array__struct.h"
#include "cmc_double_array_free_values.h"
#include "cmc_error_message.h"
#include "cmc_memory.h"
#include "diffusion_steady_state_discrete_flow_rate_from_potential.h"
#include "mesh.h"

void cmc_diffusion_steady_state_discrete_flow_rate_primal_calculate(
  struct cmc_double_array * data,
  int * status,
  const struct
    cmc_diffusion_steady_state_discrete_flow_rate_primal * input)
{
  struct mesh * m = input->m;

  data->size = m->cn[m->dim - 1];
  cmc_memory_allocate_zeros(
    (void **) &(data->values),
    status,
    sizeof(double) * data->size);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("flow_rate");
    goto end;
  }

  diffusion_steady_state_discrete_flow_rate_from_potential(
    data->values,
    input->m,
    input->m_bd_1,
    input->dual_conductivity,
    input->potential,
    input->m_hodge[1]);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_string("cannot calculate flow_rate");
    *status = errno;
    goto flow_rate_free;
  }

  return;

  /* cleaning if an error occurs */
flow_rate_free:
  cmc_double_array_free_values(data);
end:
  return;
}
