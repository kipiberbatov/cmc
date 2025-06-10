#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "double_array.h"
#include "matrix_sparse.h"

/*
Let $a$ be a positive definite matrix, $b$ be a matrix, $g$ and $f$ be vectors.
This function solves the following mixed problem for $q$ and $u$:
    a q - b^T u = - g,
  - b q         = - f.

The implementation follows the following derivation:
q = a^{-1}(b^T u - g)
f = b q = b a^{-1}(b^T u - g) = b a^{-1} b^T u - b a^{-1} g
b a^{-1} b^T u = b a^{-1} g + f

Hence, we get:
u = linear_solve_cholesky(b a^{-1} b^T, b a^{-1} g + f)
q = a^{-1}(b^T u - g)
*/
void matrix_sparse_mixed_linear_solve_with_diagonal_top_left_matrix(
  double * q,
  double * u,
  const double * a,
  const matrix_sparse * b,
  const double * g,
  const double * f)
{
  int b_nonzero_max, m, n;
  matrix_sparse b_times_inverse_a;
  matrix_sparse * b_transpose, * c;

  m = b->cols;
  n = b->rows;
  b_nonzero_max = b->cols_total[b->cols];

  matrix_sparse_copy_topology(&b_times_inverse_a, b);
  b_times_inverse_a.values = (double *) malloc(sizeof(double) * b_nonzero_max);
  if (b_times_inverse_a.values == NULL)
  {
    color_error_position(__FILE__, __LINE__);
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
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate b_transpose = b^T\n", stderr);
    goto b_times_inverse_a_values_free;
  }

  c = matrix_sparse_product(&b_times_inverse_a, b_transpose);
  if (c == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate c = b a^{-1} b^T\n", stderr);
    goto b_transpose_free;
  }

  /* u = f */
  memcpy(u, f, sizeof(double) * n);
  /* u = b a^{-1} g + f */
  matrix_sparse_vector_multiply_add(u, &b_times_inverse_a, g);
  /* u = linear_solve_cholesky(b a^{-1} b^T, b a^{-1} g + f) */
  matrix_sparse_linear_solve(c, u, "--cholesky");
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    fputs("cannot calculate variable u\n", stderr);
    goto c_free;
  }

  /* q = - g */
  double_array_negate(q, m, g);
  /* q = b^T u - g */
  matrix_sparse_vector_multiply_add(q, b_transpose, u);
  /* q = a^{-1}(b^T u - g) */
  double_array_pointwise_divide(q, m, a);

c_free:
  matrix_sparse_free(c);
b_transpose_free:
  matrix_sparse_free(b_transpose);
b_times_inverse_a_values_free:
  free(b_times_inverse_a.values);
}
