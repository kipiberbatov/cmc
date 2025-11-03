#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "matrix_sparse_private.h"

/*
Applies the Dirichlet boundary condition.
Result: form the Diriclet boundary part part of the right hand side vector.
*/
static void dirichlet_bc_apply(
  double * b_bd,
  int m_dim_embedded,
  const double * m_coord,
  const jagged1 * m_nodes_bd,
  scalar_field g_d)
{
  int j, j_loc, m_nodes_bd_a0;
  int * m_nodes_bd_a1;

  m_nodes_bd_a0 = m_nodes_bd->a0;
  m_nodes_bd_a1 = m_nodes_bd->a1;
  for (j_loc = 0; j_loc < m_nodes_bd_a0; ++j_loc)
  {
    j = m_nodes_bd_a1[j_loc];
    b_bd[j_loc] = g_d(m_coord + m_dim_embedded * j);
  }
}

/*
Apply the body source.
Result: form the interior part part of the right hand side vector.
*/
static void rhs_vector_initialise(
  double * b_in,
  int m_dim_embedded,
  const double * m_coord,
  const jagged1 * m_nodes_in,
  scalar_field f)
{
  int i, i_loc, m_nodes_in_a0;
  int * m_nodes_in_a1;

  m_nodes_in_a0 = m_nodes_in->a0;
  m_nodes_in_a1 = m_nodes_in->a1;
  for (i_loc = 0; i_loc < m_nodes_in_a0; ++i_loc)
  {
    i = m_nodes_in_a1[i_loc];
    b_in[i_loc] = f(m_coord + m_dim_embedded * i);
  }
}

/*
Let:
  . X be an open region, S be its boundary;
  . f: X -> R be a function (body source);
  . g_d: S -> R be the Dirchlet boundary condition;
Consider the problem (0) of finding u: X -> R such that
  . -\Delta u = f on X;
  . u(x, y) = g_d(x, y) on S.
Consider its discrete version on a mesh.
Let:
  . m be the forman subdivision of some original mesh;
  . m_laplacian be its discrete Laplacian, constructed out of an inner product;
  . m_dim_embedded be the dimension of the space we are embedding in;
  . m_coord be the matrix of coordinates (represented as a single list);
  . m_nodes_bd be the indices of the Dirichlet boundary nodes;
We are solving problem (0) but now with discrete quantities and operators.
*/

double * matrix_sparse_laplace_equation_solve(
  const matrix_sparse * m_laplacian,
  int m_dim_embedded,
  const double * m_coord,
  const jagged1 * m_nodes_bd,
  scalar_field f,
  scalar_field g_d)
{
  /* x is the combined version of b_in and b_bd and stores the final result */
  double * b_in, * b_bd, * x = NULL;
  jagged1 * m_nodes_in;
  matrix_sparse * m_laplacian_in;

  b_bd = (double *) malloc(sizeof(double) * m_nodes_bd->a0);
  if (b_bd == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m_nodes_bd->a0, "b_bd");
    goto end;
  }
  dirichlet_bc_apply(b_bd, m_dim_embedded, m_coord, m_nodes_bd, g_d);

  m_nodes_in = jagged1_complement(m_laplacian->cols, m_nodes_bd);
  if (m_nodes_in == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_cannot_calculate("m_nodes_in");
    goto b_bd_free;
  }

  b_in = (double *) malloc(sizeof(double) * m_nodes_in->a0);
  if (b_in == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m_nodes_in->a0, "b_in");
    goto m_nodes_in_free;
  }
  rhs_vector_initialise(b_in, m_dim_embedded, m_coord, m_nodes_in, f);
  matrix_sparse_laplace_equation_rhs_vector_modify(
    b_in, m_laplacian, m_nodes_in, m_nodes_bd, b_bd);

  m_laplacian_in = matrix_sparse_restrict_symmetric(m_laplacian, m_nodes_in);
  if (m_laplacian_in == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_cannot_calculate("m_laplacian_in");
    goto b_in_free;
  }

  /* Old: matrix_sparse_linear_solve(m_laplacian_in, b_in, "--cholesky"); */

  /* Use the LU decomposition -- m_laplacian_in may not be symmetric */
  matrix_sparse_linear_solve(m_laplacian_in, b_in, "--lu");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot solve the reduced linear system\n", stderr);
    goto m_laplacian_in_free;
  }

  x = (double *) malloc(sizeof(double) * m_laplacian->rows);
  if (x == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m_laplacian->rows, "x");
    goto m_laplacian_in_free;
  }
  double_array_assemble_from_sparse_array(x, m_nodes_in, b_in);
  double_array_assemble_from_sparse_array(x, m_nodes_bd, b_bd);

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
