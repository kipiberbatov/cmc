#include <stdlib.h>

#include "diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data.h"
#include "matrix_sparse.h"

void diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data_free(
  struct diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data * input)
{
  free(input->p_bar);
  free(input->v_tau);
  free(input->c_tau);
  matrix_sparse_free(input->l_tau);
  matrix_sparse_free(input->negative_r_bar);
  free(input->b->values);
  free(input->b);
  jagged1_free(input->boundary_neumann_dm1_bar);
  free(input);
}
