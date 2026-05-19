struct mesh;
struct matrix_sparse;

void cmc_diffusion_discrete_primal_weak_a_advective(
  struct matrix_sparse ** a_advective_pointer,
  int * status,
  const struct mesh * K,
  const struct matrix_sparse * cbd_dm1,
  const double * dual_capacity,
  const double * volumetric_flow_rate);
