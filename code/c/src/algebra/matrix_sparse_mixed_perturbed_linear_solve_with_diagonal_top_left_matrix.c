#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "matrix_sparse.h"

/*
Let
  . $m$ and $n$ be integers, with $m >= n$
  . $a: M_{m * m}(R)$ be a positive diagonal matrix
  . $b: M_{n * m}(R)$ be a sparse matrix of full rank ($n$)
  . $c: M_{n * n}(R)$ be a positive diagonal matrix
  . $g, q: R^m$
  . $f, u: R^n$

We are solving the following linear system for unknowns $q$ and $u$
  | a q + b^t u = g
  | b q - c   u = f

From the first equation, we represent
  q = a^{-1}(g - b^t u)
Substituting in the second equation, we get
  b a^{-1}(g - b^t u) - c u = f
  b a^{-1} g - f = (b a^{-1} b^t + c) u
  u = (b a^{-1} b^t + c)^{-1} (b a^{-1} g - f)
*/
void matrix_sparse_mixed_perturbed_linear_solve_with_diagonal_top_left_matrix(
  double * q,
  double * u,
  const double * a,
  const matrix_sparse * b,
  const double * c,
  const double * g,
  const double * f)
{
  int b_nonzero_max, m, n;
  matrix_sparse b_times_inverse_a;
  matrix_sparse * b_transpose, * d;

  m = b->cols;
  n = b->rows;
  b_nonzero_max = b->cols_total[b->cols];

  matrix_sparse_copy_topology(&b_times_inverse_a, b);
  b_times_inverse_a.values = (double *) malloc(sizeof(double) * b_nonzero_max);
  if (b_times_inverse_a.values == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytes of memory for b_times_inverse_a.values\n",
      sizeof(double) * b_nonzero_max);
    return;
  }
  memcpy(b_times_inverse_a.values, b->values, sizeof(double) * b_nonzero_max);
  matrix_sparse_multiply_with_inverse_of_diagonal(&b_times_inverse_a, a);

  b_transpose = matrix_sparse_transpose(b);
  if (b_transpose == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate b_transpose = b^T\n", stderr);
    goto b_times_inverse_a_values_free;
  }

  d = matrix_sparse_product(&b_times_inverse_a, b_transpose);
  if (d == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate d = b a^{-1} b^T\n", stderr);
    goto b_transpose_free;
  }
  matrix_sparse_add_with_diagonal_matrix(d, c); /* d = b a^{-1} b^T + c */

  /* calculate $u := b a^{-1} g - f$ */
  double_array_negate(u, n, f);
  matrix_sparse_vector_multiply_add(u, &b_times_inverse_a, g);

  /* find u := d^{-1} u */
  matrix_sparse_linear_solve(d, u, "--cholesky");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate variable u\n", stderr);
    goto d_free;
  }
  memcpy(q, g, sizeof(double) * m);
  matrix_sparse_vector_subtract_product(q, b_transpose, u);

  double_array_pointwise_divide(q, m, a);

d_free:
  matrix_sparse_free(d);
b_transpose_free:
  matrix_sparse_free(b_transpose);
b_times_inverse_a_values_free:
  free(b_times_inverse_a.values);
}
