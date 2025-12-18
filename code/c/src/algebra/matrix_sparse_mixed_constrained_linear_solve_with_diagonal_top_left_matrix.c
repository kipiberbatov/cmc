#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "matrix_sparse.h"

static void set_f_new(
  double * f_new,
  const double * f,
  const matrix_sparse * b,
  const jagged1 * boundary_neumann,
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

  memcpy(f_new, f, sizeof(double) * b->rows);
  for (i_local = 0; i_local < boundary_neumann_a0; ++i_local)
  {
    i = boundary_neumann_a1[i_local];
    lambda_i = g_neumann[i_local];
    for (k_local = b_cols_total[i]; k_local < b_cols_total[i + 1]; ++k_local)
    {
      k = b_row_indices[k_local];
      f_new[k] -= b_values[k_local] * lambda_i;
    }
  }
}

/*
Solve the following mixed problem for q = flow_rate and u = potential:
    (a q)[i] - (b^T u)[i] = - g[i], text{for $i$ not in $boundary_neumann$},
  - (b q)[k]              = - f[k], text{for all $k$},
  q[boundary_neumann->a1[i_local]] = g_neumann[i_local].
*/

void matrix_sparse_mixed_constrained_linear_solve_with_diagonal_top_left_matrix(
  double * flow_rate,
  double * dual_potential,
  const double * a,
  const matrix_sparse * b,
  const double * g,
  const double * f,
  const jagged1 * boundary_neumann,
  const double * g_neumann)
{
  int restrict_size;
  double * a_restrict, * flow_rate_restrict, * f_new, * g_new_restrict;
  jagged1 * boundary_neumann_complement;
  matrix_sparse * b_restrict;

  boundary_neumann_complement = jagged1_complement(b->cols, boundary_neumann);
  if (boundary_neumann_complement == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate boundary_neumann_complement\n", stderr);
    return;
  }
  restrict_size = boundary_neumann_complement->a0;

  a_restrict = (double *) malloc(sizeof(double) * restrict_size);
  if (a == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for a_restrict\n",
      sizeof(double) * restrict_size);
    goto boundary_neumann_complement_free;
  }
  double_array_compress_to_sparse_array(
    a_restrict, boundary_neumann_complement, a);

  b_restrict = matrix_sparse_columns_restrict(b, boundary_neumann_complement);
  if (b_restrict == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate b_restrict\n", stderr);
    goto a_restrict_free;
  }

  g_new_restrict = (double *) malloc(sizeof(double) * restrict_size);
  if (g_new_restrict == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for g_new_restrict\n",
      sizeof(double) * restrict_size);
    goto b_restrict_free;
  }
  double_array_compress_to_sparse_array(
    g_new_restrict, boundary_neumann_complement, g);

  f_new = (double *) malloc(sizeof(double) * b->rows);
  if (f_new == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for f_new\n",
      sizeof(double) * b->rows);
    goto g_new_restrict_free;
  }
  set_f_new(f_new, f, b, boundary_neumann, g_neumann);

  flow_rate_restrict = (double *) malloc(sizeof(double) * restrict_size);
  if (flow_rate_restrict == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for flow_rate_restrict\n",
      sizeof(double) * restrict_size);
    goto f_new_free;
  }

  matrix_sparse_mixed_linear_solve_with_diagonal_top_left_matrix(
    flow_rate_restrict, dual_potential,
    a_restrict, b_restrict, g_new_restrict, f_new);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot solve restricted mixed linear system\n", stderr);
    goto flow_rate_restrict_free;
  }

  double_array_assemble_from_sparse_array(
    flow_rate, boundary_neumann_complement, flow_rate_restrict);
  double_array_assemble_from_sparse_array(
    flow_rate, boundary_neumann, g_neumann);

flow_rate_restrict_free:
  free(flow_rate_restrict);
f_new_free:
  free(f_new);
g_new_restrict_free:
  free(g_new_restrict);
b_restrict_free:
  matrix_sparse_free(b_restrict);
a_restrict_free:
  free(a_restrict);
boundary_neumann_complement_free:
  jagged1_free(boundary_neumann_complement);
}
