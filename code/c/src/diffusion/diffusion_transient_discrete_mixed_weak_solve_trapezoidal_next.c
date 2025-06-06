#include <string.h>

#include "color.h"
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

#define progress 0

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

#if progress
  fputs("\n" color_red "u^s:" color_none "\n", stderr);
  double_array_file_print(stderr, m_cn_d, dual_potential_current, "--raw");
#endif

  /* calculate y^s := b q^s + c_tau u^s */
  memset(y, 0, sizeof(double) * m_cn_d);

#if progress
  fputs("\n" color_red "y = 0:" color_none "\n", stderr);
  double_array_file_print(stderr, m_cn_d, y, "--raw");
#endif

  matrix_sparse_vector_multiply_add(y, input->b, flow_rate_current);

#if progress
  fputs("\n" color_red "y = b q^s:" color_none "\n", stderr);
  double_array_file_print(stderr, m_cn_d, y, "--raw");
#endif

  double_array_diagonal_matrix_multiply_add(
    y, m_cn_d, input->c_tau, dual_potential_current);

#if progress
  fputs("\n" color_red "y^s = b q^s + c_tau u^s:" color_none "\n", stderr);
  double_array_file_print(stderr, m_cn_d, y, "--raw");
#endif

  /* calculate w^s := n^{-1} y = l^{-t} l^{-1} y */
  w = y;
  // matrix_sparse_lower_triangular_linear_solve(w, input->l_tau);
  // matrix_sparse_lower_triangular_transpose_linear_solve(w, input->l_tau);
  /* temporary, until proper Cholesky decomposition is used */
  matrix_sparse_linear_solve(input->l_tau, w, "--cholesky");

#if progress
  fputs("\n" color_red "w^s = n_tau^{-1} y^s:" color_none "\n", stderr);
  double_array_file_print(stderr, m_cn_d, w, "--raw");
#endif

  /* calculate u^{s + 1} := v + w^s */
  memcpy(dual_potential_next, input->v_tau, sizeof(double) * m_cn_d);
  double_array_add_to(dual_potential_next, m_cn_d, w);

#if progress
  fputs("\n" color_red "u^{s + 1} = v + w^s:" color_none "\n", stderr);
  double_array_file_print(stderr, m_cn_d, dual_potential_next, "--raw");
#endif

  /* calculate q_bar^s := p_bar - a_bar^{-1} b_bar^T u^{s + 1} */
  memcpy(flow_rate_reduced, input->p_bar, sizeof(double) * m_cn_dm1_bar);
  matrix_sparse_vector_multiply_add(
    flow_rate_reduced, input->negative_r_bar, dual_potential_next);

#if progress
  fputs("\n" color_red "q_bar^s := p_bar - b_bar^T u^{s + 1}:" color_none "\n",
    stderr);
  double_array_file_print(stderr, m_cn_dm1_bar, flow_rate_reduced, "--raw");
#endif

  /* calculate q^{s + 1} from q_bar^s and Neumann boundary conditions */
  double_array_assemble_from_sparse_array(
    flow_rate_next, input->boundary_neumann_dm1_bar, flow_rate_reduced);
  double_array_assemble_from_sparse_array(flow_rate_next,
    input->data->boundary_neumann_dm1, input->data->g_neumann_dm1);

#if progress
  fputs("\n" color_red "q^{s + 1}:" color_none "\n", stderr);
  double_array_file_print(stderr, m_cn_dm1, flow_rate_next, "--raw");
#endif
}
