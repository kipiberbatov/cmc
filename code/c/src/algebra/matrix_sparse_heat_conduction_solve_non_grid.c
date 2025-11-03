/* the code in this file is probably broken in its current form */

#include <errno.h>
#include <math.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "int.h"
#include "matrix_sparse_private.h"

static int int_array_position(int n, const int * a, int element)
{
  int i;

  for (i = 0; i < n; ++i)
    if (element == a[i])
      return i;
  return -1;
}

/* what does this do ??? */
static void lhs_restricted_matrix_modify(
  matrix_sparse * a,
  const double * m_inner,
  double tau)
{
  int a_cols, a_col_j_nonzeroes, i_loc, j;
  int * a_cols_total, * a_row_indices, * a_row_indices_col_j;
  double * a_values, * a_values_col_j;

  a_cols_total = a->cols_total;
  a_row_indices = a->row_indices;
  a_values = a->values;
  a_cols = a->cols;

  for (j = 0; j < a_cols; ++j)
  {
    a_row_indices_col_j = a_row_indices + a_cols_total[j];
    a_values_col_j = a_values + a_cols_total[j];
    a_col_j_nonzeroes = a_cols_total[j + 1] - a_cols_total[j];
    i_loc = int_array_position(a_col_j_nonzeroes, a_row_indices_col_j, j);
    a_values_col_j[i_loc] -= sqrt(m_inner[j]) * tau;
  }
}

/* this should be fine */
static void dirichlet_bc_apply(
  double * b_bd,
  int m_dim_embedded,
  const double * m_coord,
  const double * m_inner,
  const jagged1 * m_nodes_bd,
  time_dependent_scalar_field g_d,
  double tau,
  int k)
{
  int j, j_loc, m_nodes_bd_a0;
  int * m_nodes_bd_a1;

  m_nodes_bd_a0 = m_nodes_bd->a0;
  m_nodes_bd_a1 = m_nodes_bd->a1;
  for (j_loc = 0; j_loc < m_nodes_bd_a0; ++j_loc)
  {
    j = m_nodes_bd_a1[j_loc];
    b_bd[j_loc] = g_d(tau * k, m_coord + m_dim_embedded * j) * sqrt(m_inner[j]);
  }
}

/* this should be fine */
static void rhs_vector_initialise(
  double * b_in,
  int m_dim_embedded,
  const double * m_coord,
  const double * m_inner,
  const jagged1 * m_nodes_in,
  time_dependent_scalar_field f,
  double tau,
  int k)
{
  int i, i_loc, m_nodes_in_a0;
  int * m_nodes_in_a1;

  m_nodes_in_a0 = m_nodes_in->a0;
  m_nodes_in_a1 = m_nodes_in->a1;
  for (i_loc = 0; i_loc < m_nodes_in_a0; ++i_loc)
  {
    i = m_nodes_in_a1[i_loc];
    b_in[i_loc] = f(tau * k, m_coord + m_dim_embedded * i) * sqrt(m_inner[i]);
  }
}

/* this should be fine */
static void rhs_vector_apply_initial(
  double * x,
  scalar_field u_0,
  int m_dim_embedded,
  const double * m_coord,
  int m_cn_0,
  const double * m_inner)
{
  int i;

  for (i  = 0; i < m_cn_0; ++i)
    x[i] = u_0(m_coord + m_dim_embedded * i) * sqrt(m_inner[i]);
}

/* y = x + m_laplacian->rows * (k - 1); */
static void matrix_sparse_heat_conduction_rhs_final_form(
  double * b_in,
  const jagged1 * m_nodes_in,
  const double * m_inner,
  const double * y,
  int tau)
{
  int i, i_loc, m_nodes_in_a0;
  int * m_nodes_in_a1;

  m_nodes_in_a0 = m_nodes_in->a0;
  m_nodes_in_a1 = m_nodes_in->a1;
  for (i_loc = 0; i_loc < m_nodes_in_a0; ++i_loc)
  {
    i = m_nodes_in_a1[i_loc];
    b_in[i_loc] += y[i] * sqrt(m_inner[i]) * tau;
  }
}

/* this should be fine */
static void coordinates_in_standard_basis(
  double * x, int m_cn_0, const double * m_inner)
{
  int i;

  for (i  = 0; i < m_cn_0; ++i)
    x[i] /= sqrt(m_inner[i]);
}

/* g_d is the Dirichlet boundary condition */
double * matrix_sparse_heat_conduction_solve_non_grid(
  const matrix_sparse * m_laplacian,
  int m_dim_embedded,
  const double * m_coord,
  const double * m_inner,
  const jagged1 * m_nodes_bd,
  time_dependent_scalar_field f,
  time_dependent_scalar_field g_d,
  scalar_field u_0,
  double tau,
  int N)
{
  int k;
  double * b_in, * b_bd, * x = NULL, * y;
  jagged1 * m_nodes_in;
  /* the next line may need to be commented and the code refactored */
  matrix_sparse * m_laplacian_in;
  matrix_sparse * identity, * matrix_lhs, * matrix_lhs_in;

  m_nodes_in = jagged1_complement(m_laplacian->cols, m_nodes_bd);
  if (m_nodes_in == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_cannot_calculate("m_nodes_in");
    goto end;
  }

  /* find the laplacian matrix for the interior -- this is wrong */
  identity = matrix_sparse_identity(m_laplacian->cols);
  matrix_lhs = matrix_sparse_linear_combination(identity, m_laplacian, 1, -tau);
  matrix_lhs_in = matrix_sparse_restrict_symmetric(m_laplacian, m_nodes_in);
  /* the next line may need to be commented and the code refactored */
  m_laplacian_in = matrix_sparse_restrict_symmetric(m_laplacian, m_nodes_in);
  if (m_laplacian_in == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_cannot_calculate("m_laplacian_in");
    goto m_nodes_in_free;
  }

  matrix_sparse_file_print(stdout, m_laplacian_in, "--matrix-form-curly");
  fputc('\n', stdout);

  lhs_restricted_matrix_modify(m_laplacian_in, m_inner, tau);
  matrix_sparse_file_print(stdout, m_laplacian_in, "--matrix-form-curly");
  fputc('\n', stdout);

  b_in = (double *) malloc(sizeof(double) * m_nodes_in->a0);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m_nodes_in->a0, "b_in");
    goto matrix_lhs_in_free;
  }

  b_bd = (double *) malloc(sizeof(double) * m_nodes_bd->a0);
  if (b_bd == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m_nodes_bd->a0, "b_bd");
    goto b_in_free;
  }

  x = (double *) malloc(sizeof(double) * (N + 1) * m_laplacian->cols);
  if (x == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * (N + 1) * m_laplacian->cols, "x");
    goto b_bd_free;
  }

  /* find the coordinates of the initial solution in the normalised basis */
  rhs_vector_apply_initial(
    x, u_0, m_dim_embedded, m_coord, m_laplacian->rows, m_inner);
  double_array_file_print(stdout, m_laplacian->rows, x, "--raw");
  fputc('\n', stdout);

  for (k = 1; k <= N; ++k)
  {
    /* find the temporary vector storing dirichlet boundary conditions
     * in the normalised basis
     */
    dirichlet_bc_apply(
      b_bd, m_dim_embedded, m_coord, m_inner, m_nodes_bd, g_d, tau, k);

    /* find the rhs vector for the interior calculations */
    rhs_vector_initialise(
      b_in, m_dim_embedded, m_coord, m_inner, m_nodes_in, f, tau, k);

    /* modify the rhs vector with the contributions of dirichlet boundary */
    matrix_sparse_laplace_equation_rhs_vector_modify(
      b_in, matrix_lhs, m_nodes_in, m_nodes_bd, b_bd);

    /* what does this do? */
    matrix_sparse_heat_conduction_rhs_final_form(
      b_in, m_nodes_in, m_inner, x + m_laplacian->rows * (k - 1), tau);
    matrix_sparse_linear_solve(matrix_lhs_in, b_in, "--cholesky");
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fputs("cannot solve the reduced linear system\n", stderr);
      goto b_bd_free;
    }
    y = x + m_laplacian->rows * k;
    double_array_assemble_from_sparse_array(y, m_nodes_in, b_in);
    double_array_assemble_from_sparse_array(y, m_nodes_bd, b_bd);
    coordinates_in_standard_basis(y, m_laplacian->rows, m_inner);
    double_array_file_print(stdout, m_laplacian->rows, y, "--raw");
    fputc('\n', stdout);
  }

b_bd_free:
  free(b_bd);
b_in_free:
  free(b_in);
matrix_lhs_in_free:
  matrix_sparse_free(matrix_lhs_in);
  matrix_sparse_free(matrix_lhs);
  matrix_sparse_free(identity);
m_nodes_in_free:
  jagged1_free(m_nodes_in);
end:
  return x;
}
