#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "diffusion_transient_discrete_mixed_weak.h"
#include "diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data.h"
#include "double_array.h"
#include "cmc_error_message.h"
#include "mesh_qc.h"

static void set_f_tilde(
  double * f_tilde,
  const struct matrix_sparse * b,
  const struct jagged1 * boundary_neumann,
  const double * g_neumann)
{
  int boundary_neumann_a0, i, i_local, k, k_local;
  int * b_cols_total, * b_row_indices, * boundary_neumann_a1;
  double lambda_i;
  double * b_values;

  boundary_neumann_a0 = boundary_neumann->a0;
  boundary_neumann_a1 = boundary_neumann->a1;
  b_cols_total = b->cols_total;
  b_row_indices = b->row_indices;
  b_values = b->values;

  for (i_local = 0; i_local < boundary_neumann_a0; ++i_local)
  {
    i = boundary_neumann_a1[i_local];
    lambda_i = g_neumann[i_local];
    for (k_local = b_cols_total[i]; k_local < b_cols_total[i + 1]; ++k_local)
    {
      k = b_row_indices[k_local];
      f_tilde[k] += b_values[k_local] * lambda_i;
    }
  }
}

static void update_g_neumann_sign(
  const struct matrix_sparse * m_cbd_dm1,
  const struct jagged1 * boundary_neumann_dm1,
  double * g_neumann_dm1)
{
  int i, i_local, index;
  double sign;
  for (i_local = 0; i_local < boundary_neumann_dm1->a0; ++i_local)
  {
    i = boundary_neumann_dm1->a1[i_local];
    index = m_cbd_dm1->cols_total[i];
    sign = m_cbd_dm1->values[index];
    g_neumann_dm1[i_local] *= sign;
  }
}

static void set_a_bar_inverse(
  double * a_bar_inverse,
  const struct jagged1 * boundary_neumann_dm1_bar,
  const double * m_inner_dm1,
  const double * kappa_dm1)
{
  int i, i_local, m_cn_dm1_bar;
  int * boundary_neumann_dm1_bar_a1;

  m_cn_dm1_bar = boundary_neumann_dm1_bar->a0;
  boundary_neumann_dm1_bar_a1 = boundary_neumann_dm1_bar->a1;
  for (i_local = 0; i_local < m_cn_dm1_bar; ++i_local)
  {
    i = boundary_neumann_dm1_bar_a1[i_local];
    a_bar_inverse[i_local] = kappa_dm1[i] / m_inner_dm1[i];
  }
}

static void set_g_bar(
  double * g_bar,
  const struct mesh * m,
  const struct matrix_sparse * m_cbd_dm1,
  const struct jagged1 * boundary_neumann_dm1_bar,
  const struct diffusion_transient_discrete_mixed_weak * data)
{
  int d;
  double * g, * g_dirichlet_0_big;

  d = m->dim;

  g = (double *) malloc(sizeof(double) * m->cn[d - 1]);
  if (g == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m->cn[d - 1], "g");
    return;
  }

  g_dirichlet_0_big = (double *) calloc(m->cn[0], sizeof(double));
  if (g_dirichlet_0_big == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m->cn[0], "g_dirichlet_0_big");
    free(g);
    return;
  }

  double_array_assemble_from_sparse_array(
    g_dirichlet_0_big, data->boundary_dirichlet_0, data->g_dirichlet_0);
  mesh_qc_vector_from_boundary_integral_of_basis_dm1_cup_0_cochain(
    g, m, m_cbd_dm1, data->boundary_dirichlet_dm1, g_dirichlet_0_big);
  free(g_dirichlet_0_big);

#if progress
  fputs("\n" color_red "g_i := (c^{d - 1, i} \\/ g_D)[Gamma_D]" color_none "\n",
    stderr);
  double_array_file_print(stderr, m_cn_dm1, g, "--raw");
#endif

  double_array_compress_to_sparse_array(g_bar, boundary_neumann_dm1_bar, g);
  free(g);
}

/*
Indices i, j span from 0 to cn_{d - 1} - 1
Indices k, l span from 0 to cn_d - 1

Calculate in order:
  tau = time_step
  A[i, j] = <c^{d - 1, j}, kappa_{d - 1}^{-1} c^{d - 1, i}>
  B[k, i] = <delta_{d - 1} c^{d - 1, i}, c^{d, k}>
  C[k, l] = <pi_d c^{d, l}, c^{d, k}>
  g_d_big[k] = (c^{d, k} \/ g_D^0)[Gamma_D]
  g[i] = g_N(c_{d - 1, i}) on Gamma_N[d - 1] (zero elsewhere)
  f[k] = <f^d, c^{d, k}>
  J = boundary_neumann_dm1
  J_bar = jagged1_complement(m_cn_dm1, boundary_neumann_dm1)
  A_bar = matrix_sparse_diagonal_restrict(a, J_bar, J_bar)
  B_bar = matrix_sparse_columns_restrict(b, J_bar)
  g_new_bar = double_array_restrict(g, J_bar) // because a is diagonal
  g_neumann = double_array_restrict(g, J)
  B_neumann = matrix_sparse_columns_restrict(b, J)
  f_new[k] = f[k] + (b_neumann g_neumann)[k]
  p_bar = A_bar^{-1} g_new_bar
  B_bar_transpose = matrix_sparse_transpose(B_bar)
  S_bar = B_bar A_bar^{-1}
  N = S_bar B_bar^T + (2 / tau) C
  L = Cholesky(N)
  z = S_bar g_new_bar + f_new
  v = N^{-1} z = right_transpose_solve(L, left_transpose_solve(L, z))
return
  (J_bar, B, - B_bar_transpose, L, (2 / tau) C, v, p_bar, g_neumann)
delete everything else:
  (A, g_d_big, g, f, A_bar, B_bar, g_new_bar, B_neumann, f_new, S_bar, N, z)
*/

#define progress 0

struct diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data *
diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data_initialize(
  const struct mesh * m,
  const struct matrix_sparse * m_cbd_dm1,
  const double * m_inner_dm1,
  const double * m_inner_d,
  const struct diffusion_transient_discrete_mixed_weak * data,
  double time_step)
{
  int d, m_cn_dm1, m_cn_dm1_bar, m_cn_d;
  double * a_bar_inverse, * c, * c_tau, * f, * f_tilde, * g_bar, * p_bar,
         * v_tau, * z;
  struct jagged1 * boundary_neumann_dm1_bar;
  struct matrix_sparse * b, * b_bar, * b_bar_transpose, /* * l_tau, */ * n_tau;
  struct diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data * input;

  /* temporary hack to patch the wrong orientation coming from discretizing
   * the Neumann boundary condition
   */
  update_g_neumann_sign(
    m_cbd_dm1, data->boundary_neumann_dm1, data->g_neumann_dm1);

  d = m->dim;
  m_cn_dm1 = m->cn[d - 1];
  m_cn_dm1_bar = m_cn_dm1 - data->boundary_neumann_dm1->a0;
  m_cn_d = m->cn[d];

  *(void **) (&input) = malloc(sizeof(*input));
  if (input == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(*input), "input");
    goto end;
  }

  boundary_neumann_dm1_bar = jagged1_complement(
    m_cn_dm1, data->boundary_neumann_dm1);
  if (boundary_neumann_dm1_bar == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate boundary_neumann_dm1_bar\n", stderr);
    goto input_free;
  }

#if progress
  fputs("\n" color_red "boundary_neumann_dm1_bar:" color_none "\n", stderr);
  jagged1_file_print(stderr, boundary_neumann_dm1_bar, "--raw");
#endif

  b = mesh_qc_matrix_sparse_from_inner_of_basis_d_cup_delta_basis_dm1(
    m_cbd_dm1, m_inner_d);
  if (b == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate b\n", stderr);
    goto boundary_neumann_dm1_bar_free;
  }

#if progress
  fputs("\n" color_red "b:" color_none "\n", stderr);
  matrix_sparse_file_print(stderr, b, "--matrix-form-raw");
#endif

  c_tau = (double *) malloc(sizeof(double) * m_cn_dm1_bar);
  if (c_tau == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m_cn_dm1_bar, "c_tau");
    goto b_free;
  }

  v_tau = (double *) malloc(sizeof(double) * m_cn_d);
  if (v_tau == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m_cn_d, "v_tau");
    goto c_tau_free;
  }

  p_bar = (double *) malloc(sizeof(double) * m_cn_dm1_bar);
  if (p_bar == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m_cn_dm1_bar, "p_bar");
    goto v_tau_free;
  }

  c = c_tau;
  memcpy(c, m_inner_d, sizeof(double) * m_cn_d);
  double_array_pointwise_multiply(c, m_cn_d, data->pi_d);
  double_array_multiply_with(c_tau, m_cn_d, 2. / time_step);

#if progress
  fputs("\n" color_red "diagonal_values(c_tau):" color_none "\n", stderr);
  double_array_file_print(stderr, m_cn_d, c_tau, "--raw");
#endif

  a_bar_inverse = (double *) malloc(sizeof(double) * m_cn_dm1_bar);
  if (a_bar_inverse == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m_cn_dm1_bar, "v_tau");
    goto v_tau_free;
  }

  set_a_bar_inverse(a_bar_inverse,
    boundary_neumann_dm1_bar, m_inner_dm1, data->kappa_dm1);

#if progress
  fputs("\n" color_red "a_bar^{-1}:" color_none "\n", stderr);
  double_array_file_print(stderr, m_cn_dm1_bar, a_bar_inverse, "--raw");
#endif

  g_bar = p_bar; /* share memory */
  set_g_bar(g_bar, m, m_cbd_dm1, boundary_neumann_dm1_bar, data);
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot set g_bar\n", stderr);
    free(a_bar_inverse);
    goto p_bar_free;
  }

#if progress
  fputs("\n" color_red "g_bar:" color_none "\n", stderr);
  double_array_file_print(stderr, m_cn_dm1_bar, g_bar, "--raw");
#endif

  /* now p_bar = g_bar -> we update to p_bar = a_bar^{-1} g_bar */
  double_array_pointwise_multiply(p_bar, m_cn_dm1_bar, a_bar_inverse);

#if progress
  fputs("\n" color_red "p_bar:" color_none "\n", stderr);
  double_array_file_print(stderr, m_cn_dm1_bar, p_bar, "--raw");
#endif

  f = v_tau; /* share memory */
  mesh_qc_vector_from_inner_of_basis_d_cup_d_cochain(
    f, m, m_inner_d, data->source);
  f_tilde = f;
  double_array_multiply_with(f_tilde, m_cn_d, 2.);
  set_f_tilde(f_tilde, b, data->boundary_neumann_dm1, data->g_neumann_dm1);

#if progress
  fputs("\n" color_red "~f:" color_none "\n", stderr);
  double_array_file_print(stderr, m_cn_d, f_tilde, "--raw");
#endif

  z = f_tilde;
  b_bar = matrix_sparse_columns_restrict(b, boundary_neumann_dm1_bar);
  if (b_bar == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate b_bar\n", stderr);
    free(a_bar_inverse);
    goto p_bar_free;
  }

  b_bar_transpose = matrix_sparse_transpose(b_bar);
  if (b_bar_transpose == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate b_bar_transpose\n", stderr);
    matrix_sparse_free(b_bar);
    free(a_bar_inverse);
    goto p_bar_free;
  }

  matrix_sparse_vector_multiply_add(z, b_bar, p_bar);
  matrix_sparse_multiply_with_diagonal_matrix(b_bar, a_bar_inverse);

#if progress
  fputs("\n" color_red "z:" color_none "\n", stderr);
  double_array_file_print(stderr, m_cn_d, z, "--raw");
#endif

  n_tau = matrix_sparse_product(b_bar, b_bar_transpose);
  if (n_tau == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate n_tau\n", stderr);
    matrix_sparse_free(b_bar);
    goto b_bar_transpose_free;
  }
  matrix_sparse_free(b_bar);

#if progress
  fputs("\n" color_red "b_bar a_bar^{-1} b_bar^T:" color_none "\n", stderr);
  matrix_sparse_file_print(stderr, n_tau, "--matrix-form-raw");
#endif

  matrix_sparse_add_with_diagonal_matrix(n_tau, c_tau);

#if progress
  {
    struct matrix_sparse * l_tau, * l_tau_transpose, * n_tau_1;

    fputs("\n# n_tau:\n", stderr);
    matrix_sparse_file_print(stderr, n_tau, "--matrix-form-curly");

    l_tau = matrix_sparse_cholesky_decomposition(n_tau);
    fputs("\n# l_tau:\n", stderr);
    matrix_sparse_file_print(stderr, l_tau, "--matrix-form-curly");

    l_tau_transpose = matrix_sparse_transpose(l_tau);
    fputs("\n# l_tau^T:\n", stderr);
    matrix_sparse_file_print(stderr, l_tau_transpose, "--matrix-form-curly");

    n_tau_1 = matrix_sparse_product(l_tau, l_tau_transpose);
    fputs("\n# l_tau l_tau^T:\n", stderr);
    matrix_sparse_file_print(stderr, n_tau_1, "--matrix-form-curly");

    matrix_sparse_free(n_tau_1);
    matrix_sparse_free(l_tau_transpose);
    matrix_sparse_free(l_tau);
  }
#endif

  /* error check */
  //matrix_sparse_free(n_tau);

#if progress
  fputs("\n" color_red "n_tau = b_bar a_bar^{-1} b_bar^T + (2 / tau) c:"
    color_none "\n", stderr);
  matrix_sparse_file_print(stderr, n_tau, "--matrix-form-raw");
#endif

  /* v_tau = n_tau^{-1} z = l_tau^{-T} l_tau^{-1} z */
  v_tau = z;
  // matrix_sparse_lower_triangular_linear_solve(v_tau, l_tau);
  // matrix_sparse_lower_triangular_transpose_linear_solve(v_tau, l_tau);
  matrix_sparse_linear_solve(n_tau, v_tau, "--cholesky");
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot solve v_tau := n_tau^{-1} v_tau with --cholesky \n", stderr);
    goto n_tau_free;
  }

#if progress
  fputs("\n" color_red "v_tau:" color_none "\n", stderr);
  double_array_file_print(stderr, m_cn_d, v_tau, "--raw");
#endif

#if progress
  fputs("\n" color_red "b_bar^T:" color_none "\n", stderr);
  matrix_sparse_file_print(stderr, b_bar_transpose, "--matrix-form-raw");
#endif

  matrix_sparse_scalar_multiply(b_bar_transpose, -1);
  matrix_sparse_multiply_with_diagonal_matrix_on_the_left(
    b_bar_transpose, a_bar_inverse);
  free(a_bar_inverse);

#if progress
  fputs("\n" color_red "-b_bar^T:" color_none "\n", stderr);
  matrix_sparse_file_print(stderr, b_bar_transpose, "--matrix-form-raw");
#endif

  input->boundary_neumann_dm1_bar = boundary_neumann_dm1_bar;
  input->b = b;
  input->negative_r_bar = b_bar_transpose;
  /* input->l_tau = l_tau; */
  input->l_tau = n_tau;
  input->c_tau = c_tau;
  input->v_tau = v_tau;
  input->p_bar = p_bar;
  input->data = data;

#if progress
  fputs("\n" color_red "boundary_neumann_dm1_bar:" color_none "\n", stderr);
  jagged1_file_print(stderr, boundary_neumann_dm1_bar, "--raw");

  fputs("\n" color_red "b:" color_none "\n", stderr);
  matrix_sparse_file_print(stderr, b, "--matrix-form-raw");

  fputs("\n" color_red "-b_bar^T:" color_none "\n", stderr);
  matrix_sparse_file_print(stderr, b_bar_transpose, "--matrix-form-raw");

  fputs("\n" color_red "n_tau:" color_none "\n", stderr);
  matrix_sparse_file_print(stderr, n_tau, "--matrix-form-raw");

  fputs("\n" color_red "diagonal_values(c_tau):" color_none "\n", stderr);
  double_array_file_print(stderr, m_cn_d, c_tau, "--raw");

  fputs("\n" color_red "v_tau:" color_none "\n", stderr);
  double_array_file_print(stderr, m_cn_d, v_tau, "--raw");

  fputs("\n" color_red "p_bar:" color_none "\n", stderr);
  double_array_file_print(stderr, m_cn_dm1_bar, p_bar, "--raw");
#endif

  return input;

  /* cleaning if an error occurs */
n_tau_free:
  matrix_sparse_free(n_tau);
b_bar_transpose_free:
  matrix_sparse_free(b_bar_transpose);
p_bar_free:
  free(p_bar);
v_tau_free:
  free(v_tau);
c_tau_free:
  free(c_tau);
b_free:
  free(b->values);
  free(b);
boundary_neumann_dm1_bar_free:
  jagged1_free(boundary_neumann_dm1_bar);
input_free:
  free(input);
end:
  return NULL;
}
