#include <errno.h>

#include "cmc_error_message.h"
#include "diffusion_steady_state_continuous.h"
#include "diffusion_steady_state_discrete_primal_strong.h"
#include "mesh.h"

double * diffusion_steady_state_continuous_primal_strong_cochain_solve(
  const struct mesh * m,
  const struct matrix_sparse * m_cbd_0,
  const struct matrix_sparse * m_cbd_star_1,
  const struct diffusion_steady_state_continuous * data_continuous)
{
  double * result = NULL;
  struct diffusion_steady_state_discrete_primal_strong * data_discrete;

  data_discrete =
  diffusion_steady_state_discrete_primal_strong_from_continuous(
    m, data_continuous);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot discretize continuous data\n", stderr);
    goto end;
  }

  result = diffusion_steady_state_discrete_primal_strong_solve(
    m, m_cbd_0, m_cbd_star_1, data_discrete);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot find discretized result\n");
    goto data_discrete_free;
  }

data_discrete_free:
  diffusion_steady_state_discrete_primal_strong_free(data_discrete);
end:
  return result;
}
