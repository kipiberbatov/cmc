#include "cmc_diffusion_discrete_primal_weak_a_advective.h"
#include "cmc_diffusion_discrete_primal_weak_a_advective_private.h"
#include "cmc_error_message.h"
#include "cmc_memory.h"
#include "int.h"
#include "mesh.h"

void cmc_diffusion_discrete_primal_weak_a_advective(
  struct matrix_sparse ** a_advective_pointer,
  int * status,
  const struct mesh * K,
  const struct matrix_sparse * cbd_dm1,
  const double * dual_capacity,
  const double * volumetric_flow_rate)
{
  int a_advective_nonzero_max;
  int * a_advective_row_indices;
  double * a_advective_values;
  struct matrix_sparse * a_advective;

  cmc_diffusion_discrete_primal_weak_a_advective_allocate(
    a_advective_pointer, status, K);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_cannot_calculate("a_advective");
    return;
  }
  a_advective = *a_advective_pointer;

  cmc_diffusion_discrete_primal_weak_a_advective_calculate(
    a_advective, K, cbd_dm1, dual_capacity, volumetric_flow_rate);

  a_advective_nonzero_max = a_advective->cols_total[K->cn[0]];
  cmc_memory_reallocate(
    (void **) &a_advective_row_indices,
    status,
    (void *) a_advective->row_indices,
    sizeof(int) * a_advective_nonzero_max);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("a_advective_row_indices");
    matrix_sparse_free(a_advective);
    return;
  }
  a_advective->row_indices = a_advective_row_indices;

  cmc_memory_reallocate(
    (void **) &a_advective_values,
    status,
    (void *) a_advective->values,
    sizeof(double) * a_advective_nonzero_max);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("a_advective_row_indices");
    matrix_sparse_free(a_advective);
    return;
  }
  a_advective->values = a_advective_values;
}
