#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "diffusion_steady_state_discrete_primal_weak.h"
#include "double.h"
#include "mesh_qc.h"

static double * matrix_sparse_symmetric_constrained_solve(
  struct matrix_sparse * a,
  double * f,
  const struct jagged1 * rows,
  const double * values)
{
  int i, i_local, rows_a0;
  int * rows_a1;
  double * u;

  rows_a0 = rows->a0;
  rows_a1 = rows->a1;
  matrix_sparse_set_identity_rows(a, rows);
  for (i_local = 0; i_local < rows_a0; ++i_local)
  {
    i = rows_a1[i_local];
    f[i] = values[i_local];
  }

  u = (double *) malloc(sizeof(double) * a->cols);
  if (u == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * a->cols, "u");
    return NULL;
  }
  memcpy(u, f, sizeof(double) * a->cols);

  matrix_sparse_linear_solve(a, u, "--lu");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot solve linear system using LU decomposition\n", stderr);
    free(u);
    return NULL;
  }

  return u;
}

double * diffusion_steady_state_discrete_primal_weak_solve(
  const struct mesh * m,
  const double * m_inner_1,
  const struct diffusion_steady_state_discrete_primal_weak * data)
{
  int m_cn_0;
  double * f, * u = NULL;
  struct matrix_sparse * a;

  m_cn_0 = m->cn[0];

  a =
  mesh_qc_matrix_sparse_from_inner_of_delta_basis_0_cup_kappa_1_delta_basis_0(
    m, m_inner_1, data->kappa_1);
  if (a == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate a\n", stderr);
    goto end;
  }

  f = (double *) malloc(sizeof(double) * m_cn_0);
  if (f == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m_cn_0, "f");
    goto a_free;
  }

  mesh_qc_vector_from_integral_of_basis_0_cup_d_cochain(f, m, data->source);

  /* add contributions from Neumann boundary condition */
  mesh_qc_vector_from_boundary_integral_of_basis_0_cup_dm1_cochain(
    f, m, data->boundary_neumann, data->g_neumann);

  u = matrix_sparse_symmetric_constrained_solve(
    a, f, data->boundary_dirichlet, data->g_dirichlet);
  if (u == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot solve constrained system\n", stderr);
    goto f_free;
  }

f_free:
  free(f);
a_free:
  matrix_sparse_free(a);
end:
  return u;
}
