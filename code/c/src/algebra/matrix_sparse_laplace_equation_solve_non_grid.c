#include <errno.h>
#include <math.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "matrix_sparse_private.h"

static void dirichlet_bc_apply(
  double * b_bd, int m_dim_embedded, const double * m_coord,
  const double * m_inner, const jagged1 * m_nodes_bd, scalar_field g_d)
{
  int j, j_loc, m_nodes_bd_a0;
  int * m_nodes_bd_a1;

  m_nodes_bd_a0 = m_nodes_bd->a0;
  m_nodes_bd_a1 = m_nodes_bd->a1;
  for (j_loc = 0; j_loc < m_nodes_bd_a0; ++j_loc)
  {
    j = m_nodes_bd_a1[j_loc];
    b_bd[j_loc] = g_d(m_coord + m_dim_embedded * j) * sqrt(m_inner[j]);
  }
}

static void rhs_vector_initialise(
  double * b_in, int m_dim_embedded, const double * m_coord,
  const double * m_inner, const jagged1 * m_nodes_in, scalar_field f)
{
  int i, i_loc, m_nodes_in_a0;
  int * m_nodes_in_a1;

  m_nodes_in_a0 = m_nodes_in->a0;
  m_nodes_in_a1 = m_nodes_in->a1;
  for (i_loc = 0; i_loc < m_nodes_in_a0; ++i_loc)
  {
    i = m_nodes_in_a1[i_loc];
    b_in[i_loc] = f(m_coord + m_dim_embedded * i) * sqrt(m_inner[i]);
  }
}

static void coordinates_in_standard_basis(
  double * x, int m_cn_0, const double * m_inner)
{
  int i;

  for (i  = 0; i < m_cn_0; ++i)
    x[i] /= sqrt(m_inner[i]);
}

/* g_d is the Dirichlet boundary condition */
double * matrix_sparse_laplace_equation_solve_non_grid(
  const matrix_sparse * m_laplacian, int m_dim_embedded, const double * m_coord,
  const double * m_inner, const jagged1 * m_nodes_bd, scalar_field f,
  scalar_field g_d)
{
  double * b_in, * b_bd, * x = NULL;
  jagged1 * m_nodes_in;
  matrix_sparse * m_laplacian_in;

  b_bd = (double *) malloc(sizeof(double) * m_nodes_bd->a0);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for b_bd\n",
      sizeof(double) * m_nodes_bd->a0);
    goto end;
  }
  dirichlet_bc_apply(b_bd, m_dim_embedded, m_coord, m_inner, m_nodes_bd, g_d);

  m_nodes_in = jagged1_complement(m_laplacian->cols, m_nodes_bd);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m_nodes_in\n", stderr);
    goto b_bd_free;
  }

  b_in = (double *) malloc(sizeof(double) * m_nodes_in->a0);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for b_in\n",
      sizeof(double) * m_nodes_in->a0);
    goto m_nodes_in_free;
  }
  rhs_vector_initialise(b_in, m_dim_embedded, m_coord, m_inner, m_nodes_in, f);
  matrix_sparse_laplace_equation_rhs_vector_modify(
    b_in, m_laplacian, m_nodes_in, m_nodes_bd, b_bd);

  m_laplacian_in = matrix_sparse_restrict_symmetric(m_laplacian, m_nodes_in);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m_laplacian_in\n", stderr);
    goto b_in_free;
  }

  matrix_sparse_linear_solve(m_laplacian_in, b_in, "--cholesky");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs(
      "cannot solve the reduced linear system using Cholesky decomposition\n",
      stderr);
    goto m_laplacian_in_free;
  }

  x = (double *) malloc(sizeof(double) * m_laplacian->rows);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for x\n",
      sizeof(double) * m_laplacian->rows);
    goto m_laplacian_in_free;
  }
  double_array_assemble_from_sparse_array(x, m_nodes_in, b_in);
  double_array_assemble_from_sparse_array(x, m_nodes_bd, b_bd);
  coordinates_in_standard_basis(x, m_laplacian->rows, m_inner);

m_laplacian_in_free:
  matrix_sparse_free(m_laplacian_in);
b_in_free:
  free(b_in);
m_nodes_in_free:
  jagged1_free(m_nodes_in);
b_bd_free:
  free(b_bd);
end:
  return x;
}
