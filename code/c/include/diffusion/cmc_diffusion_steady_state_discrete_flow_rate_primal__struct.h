#ifndef _cmc_diffusion_steady_state_discrete_flow_rate_primal__struct_h
#define _cmc_diffusion_steady_state_discrete_flow_rate_primal__struct_h

struct mesh;
struct matrix_sparse;

struct cmc_diffusion_steady_state_discrete_flow_rate_primal
{
  struct mesh * m;
  struct matrix_sparse * m_bd_1;
  struct matrix_sparse ** m_hodge;
  double * dual_conductivity;
  double * potential;
};

#endif /* _cmc_diffusion_steady_state_discrete_flow_rate_primal__struct_h */
