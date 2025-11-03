#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "double.h"
#include "diffusion_steady_state_continuous.h"
#include "diffusion_steady_state_discrete_mixed_weak.h"
#include "mesh.h"

void diffusion_steady_state_continuous_mixed_weak_cochain_solve(
  double * flow_rate,
  double * dual_potential,
  const struct mesh * m,
  const struct matrix_sparse * m_cbd_dm1,
  const double * m_vol_dm1,
  const double * m_vol_d,
  const double * m_inner_dm1,
  const double * m_inner_d,
  const struct diffusion_steady_state_continuous * data_continuous)
{
  struct diffusion_steady_state_discrete_mixed_weak * data_discrete;

  data_discrete = diffusion_steady_state_discrete_mixed_weak_from_continuous(
    m, m_vol_dm1, m_vol_d, data_continuous);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot discretize continuous data\n", stderr);
    return;
  }

  diffusion_steady_state_discrete_mixed_weak_solve(
    flow_rate, dual_potential,
    m, m_cbd_dm1, m_inner_dm1, m_inner_d, data_discrete);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot solve discretized problem\n", stderr);
    goto data_discrete_free;
  }

data_discrete_free:
  diffusion_steady_state_discrete_mixed_weak_free(data_discrete);
}
