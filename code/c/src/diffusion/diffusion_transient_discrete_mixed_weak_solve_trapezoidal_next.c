#include <string.h>

#include "cmc_error_message.h"
#include "diffusion_transient_discrete_mixed_weak.h"
#include "diffusion_transient_discrete_mixed_weak_solve_trapezoidal_next.h"
#include "diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data.h"
#include "double_array.h"
#include "mesh.h"

static void double_array_diagonal_matrix_multiply_add(
  double * y, int n, const double * d, const double * x)
{
  int i;

  for (i = 0; i < n; ++i)
    y[i] += d[i] * x[i];
}

void diffusion_transient_discrete_mixed_weak_solve_trapezoidal_next(
  double * flow_rate_next,
  double * dual_potential_next,
  double * y,
  double * flow_rate_reduced,
  const double * flow_rate_current,
  const double * dual_potential_current,
  const struct diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data *
    input)
{
  int m_cn_dm1, m_cn_dm1_bar, m_cn_d;
  double * w;

  m_cn_dm1 = input->data->number_of_cells_dm1;
  m_cn_dm1_bar = m_cn_dm1 - input->data->boundary_neumann_dm1->a0;
  m_cn_d = input->data->number_of_cells_d;

  /* calculate y^s := b q^s + c_tau u^s */
  memset(y, 0, sizeof(double) * m_cn_d);

  matrix_sparse_vector_multiply_add(y, input->b, flow_rate_current);
  double_array_multiply_with(y, m_cn_d, -1);

  double_array_diagonal_matrix_multiply_add(
    y, m_cn_d, input->c_tau, dual_potential_current);

  /* calculate w^s := n_tau^{-1} y = l_tau^{-t} l_tau^{-1} y */
  w = y;
  matrix_sparse_linear_solve(input->n_tau, w, "--cholesky");

  /* TODO: */
  /* matrix_sparse_lower_triangular_linear_solve(w, input->l_tau); */
  /* matrix_sparse_lower_triangular_transpose_linear_solve(w, input->l_tau); */

  /* calculate u^{s + 1} := v + w^s */
  memcpy(dual_potential_next, input->v_tau, sizeof(double) * m_cn_d);
  double_array_add_to(dual_potential_next, m_cn_d, w);

  /* calculate q_bar^s := - p_bar + a_bar^{-1} b_bar^T u^{s + 1} */
  double_array_negate(flow_rate_reduced, m_cn_dm1_bar, input->p_bar);
  matrix_sparse_vector_multiply_add(
    flow_rate_reduced, input->r_bar, dual_potential_next);

  /* calculate q^{s + 1} from q_bar^s and Neumann boundary conditions */
  double_array_assemble_from_sparse_array(
    flow_rate_next, input->boundary_neumann_dm1_bar, flow_rate_reduced);
  double_array_assemble_from_sparse_array(flow_rate_next,
    input->data->boundary_neumann_dm1, input->data->g_neumann_dm1);
}
