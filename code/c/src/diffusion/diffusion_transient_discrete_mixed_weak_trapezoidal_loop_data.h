#ifndef _diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data_h
#define _diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data_h

struct diffusion_transient_discrete_mixed_weak;
struct jagged1;
struct matrix_sparse;
struct mesh;

struct diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data
{
  struct jagged1 * boundary_neumann_dm1_bar;
  struct matrix_sparse * b;
  struct matrix_sparse * negative_r_bar; /* - a_bar^{-1} b_bar^T */
  struct matrix_sparse * l_tau; /* cholesky_decomposition(n_tau) */
  double * c_tau; /* (2 / tau) * c */
  double * v_tau; /* b_bar a_bar^{-1} g_bar + tilde{f} */
  double * p_bar; /* a_bar^{-1} g_bar */
  const struct diffusion_transient_discrete_mixed_weak * data;
};

struct diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data *
diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data_initialize(
  const struct mesh * m,
  const struct matrix_sparse * m_cbd_dm1,
  const double * m_inner_dm1,
  const double * m_inner_d,
  const struct diffusion_transient_discrete_mixed_weak * data,
  double time_step);

void diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data_free(
  struct diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data * input);

#endif /* _diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data_h */
