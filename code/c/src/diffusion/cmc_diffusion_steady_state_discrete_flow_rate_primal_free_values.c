#include "cmc_diffusion_steady_state_discrete_flow_rate_primal__struct.h"
#include "cmc_diffusion_steady_state_discrete_flow_rate_primal_free_values.h"
#include "cmc_memory.h"
#include "matrix_sparse.h"
#include "mesh.h"

void cmc_diffusion_steady_state_discrete_flow_rate_primal_free_values(
  struct cmc_diffusion_steady_state_discrete_flow_rate_primal * input)
{
  cmc_memory_free(input->potential);
  cmc_memory_free(input->dual_conductivity);
  matrix_sparse_array_free(input->m_hodge, 2);
  matrix_sparse_free(input->m_bd_1);
  mesh_free(input->m);
}
