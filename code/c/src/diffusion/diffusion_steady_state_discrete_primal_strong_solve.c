#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "diffusion_steady_state_discrete_primal_strong.h"
#include "mesh.h"
#include "mesh_qc_set_neumann_rows.h"

double * diffusion_steady_state_discrete_primal_strong_solve(
  const struct mesh * m,
  const struct matrix_sparse * m_cbd_0,
  const struct matrix_sparse * m_cbd_star_1,
  const struct diffusion_steady_state_discrete_primal_strong * data)
{
  int n;
  double * result = NULL;
  struct matrix_sparse * lhs;

  lhs = matrix_sparse_material_product(m_cbd_0, data->kappa_1, m_cbd_star_1);
  if (lhs == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate lhs\n", stderr);
    goto end;
  }

  n = m->cn[0];
  result = (double *) malloc(sizeof(double) * n);
  if (result == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * n, "result");
    goto lhs_free;
  }
  memcpy(result, data->source, sizeof(double) * n);

  /* apply Dirichlet boundary conditions */
  matrix_sparse_set_identity_rows(lhs, data->boundary_dirichlet);
  double_array_assemble_from_sparse_array(
    result, data->boundary_dirichlet, data->g_dirichlet);

  /* apply Neumann boundary conditions */
  mesh_qc_set_neumann_rows(
    lhs, m, data->boundary_neumann, data->kappa_1);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot apply Neumann boundary condition\n", stderr);
    goto lhs_free;
  }
  double_array_assemble_from_sparse_array(
    result, data->boundary_neumann, data->g_neumann);

  matrix_sparse_linear_solve(lhs, result, "--lu");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot solve linear system using LU decomposition\n", stderr);
    goto lhs_free;
  }

lhs_free:
  matrix_sparse_free(lhs);
end:
  return result;
}
