#ifndef _diffusion_transient_discrete_primal_strong_solve_trapezoidal_next_h
#define _diffusion_transient_discrete_primal_strong_solve_trapezoidal_next_h

#include "diffusion_transient_discrete_primal_strong_trapezoidal_loop_data.h"

void diffusion_transient_discrete_primal_strong_solve_trapezoidal_next(
  double * potential_next,
  double * rhs_final,
  const double * potential_current,
  const struct diffusion_transient_discrete_primal_strong_trapezoidal_loop_data
    * input);

#endif /* _diffusion_transient_discrete_primal_strong_solve_trapezoidal_next_h */
