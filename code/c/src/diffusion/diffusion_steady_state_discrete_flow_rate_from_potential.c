#include <stdlib.h>

#include "cmc_error_message.h"
#include "diffusion_steady_state_discrete_flow_rate_from_potential.h"
#include "diffusion_steady_state_discrete_dual_flow_rate_from_potential.h"
#include "mesh.h"

void diffusion_steady_state_discrete_flow_rate_from_potential(
  double * flow_rate,
  const struct mesh * m,
  const struct matrix_sparse * m_bd_1,
  const double * kappa_1,
  const double * potential,
  const struct matrix_sparse * m_hodge_1)
{
  double * dual_flow_rate;

  dual_flow_rate = (double *) malloc(sizeof(double) * m->cn[1]);
  if (dual_flow_rate == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m->cn[1], "dual_flow_rate");
    return;
  }

  diffusion_steady_state_discrete_dual_flow_rate_from_potential(
    dual_flow_rate, m, m_bd_1, kappa_1, potential);

  matrix_sparse_vector_multiply_add(flow_rate, m_hodge_1, dual_flow_rate);
  free(dual_flow_rate);
}
