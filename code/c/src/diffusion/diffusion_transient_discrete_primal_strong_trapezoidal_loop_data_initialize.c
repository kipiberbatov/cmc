#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "diffusion_transient_discrete_primal_strong.h"
#include "diffusion_transient_discrete_primal_strong_trapezoidal_loop_data.h"
#include "double_array.h"
#include "mesh.h"
#include "mesh_qc_set_neumann_rows.h"

struct diffusion_transient_discrete_primal_strong_trapezoidal_loop_data *
diffusion_transient_discrete_primal_strong_trapezoidal_loop_data_initialize(
  const struct mesh * m,
  const struct matrix_sparse * m_cbd_0,
  const struct matrix_sparse * m_cbd_star_1,
  const struct diffusion_transient_discrete_primal_strong * data,
  double time_step)
{
  int n;
  double * a, * free_part;
  struct matrix_sparse * b, * lhs, * rhs;

  struct diffusion_transient_discrete_primal_strong_trapezoidal_loop_data *
  result;

  *(void **) (&result) = malloc(sizeof(*result));
  if (result == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(*result), "result");
    goto end;
  }

  n = m->cn[0];
  a = data->pi_0;

  b = matrix_sparse_material_product(m_cbd_0, data->kappa_1, m_cbd_star_1);
  if (b == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate matrix b\n", stderr);
    goto result_free;
  }

  /* $lhs = a + (time_step / 2) * b$ */
  lhs = matrix_sparse_copy(b);
  if (lhs == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot initialize matrix lhs\n", stderr);
    goto b_free;
  }
  matrix_sparse_scalar_multiply(lhs, time_step / 2);
  matrix_sparse_add_with_diagonal_matrix(lhs, a);

  /* $rhs = a - (time_step / 2) * b$ */
  rhs = b;
  matrix_sparse_scalar_multiply(rhs, - time_step / 2);
  matrix_sparse_add_with_diagonal_matrix(rhs, a);

  /* $free_part = time_step * data->source$ */
  free_part = (double *) malloc(sizeof(double) * n);
  if (free_part == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * n, "free_part");
    goto lhs_free;
  }
  memcpy(free_part, data->source, sizeof(double) * n);
  double_array_multiply_with(free_part, n, time_step);

  /* apply Dirichlet boundary condition on matrix $lhs$ */
  matrix_sparse_set_identity_rows(lhs, data->boundary_dirichlet);

  /* apply Neumann boundary condition on matrix $lhs$ */
  mesh_qc_set_neumann_rows(
    lhs, m, data->boundary_neumann, data->kappa_1);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot apply Neumann boundary condition\n", stderr);
    goto free_part_free;
  }
  result->lhs = lhs;
  result->rhs = rhs;
  result->free_part = free_part;
  result->data = data;
  return result;

  /* cleaning if an error occurs */
free_part_free:
  free(free_part);
lhs_free:
  matrix_sparse_free(lhs);
b_free:
  matrix_sparse_free(b);
result_free:
  free(result);
end:
  return NULL;
}
