#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "matrix_sparse.h"

matrix_sparse *
matrix_sparse_laplacian_0(const matrix_sparse * a_0, const matrix_sparse * b_1)
{
  matrix_sparse * delta_0;

  delta_0 = matrix_sparse_product(b_1, a_0);
  if (delta_0 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate delta_0\n", stderr);
    return NULL;
  }
  return delta_0;
}

matrix_sparse * matrix_sparse_laplacian_p(
  const matrix_sparse * a_p_minus_1, const matrix_sparse * a_p,
  const matrix_sparse * b_p, const matrix_sparse * b_p_plus_1)
{
  matrix_sparse * delta_p, * tmp1, * tmp2;

  delta_p = NULL;
  tmp1 = matrix_sparse_product(b_p_plus_1, a_p);
  if (tmp1 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate tmp1\n", stderr);
    goto end;
  }

  tmp2 = matrix_sparse_product(a_p_minus_1, b_p);
  if (tmp2 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate tmp2\n", stderr);
    goto tmp1_free;
  }

  delta_p = matrix_sparse_add(tmp1, tmp2);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate delta_p\n", stderr);
    goto tmp2_free;
  }

tmp2_free:
  free(tmp2);
tmp1_free:
  free(tmp1);
end:
  return delta_p;
}

matrix_sparse * matrix_sparse_laplacian_d(
  const matrix_sparse * a_d_minus_1, const matrix_sparse * b_d)
{
  matrix_sparse * delta_d;

  delta_d = matrix_sparse_product(a_d_minus_1, b_d);
  if (delta_d == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate delta_d\n", stderr);
  }
  return delta_d;
}

matrix_sparse ** matrix_sparse_laplacian(
  int d, matrix_sparse ** a, matrix_sparse ** b)
{
  int p;
  matrix_sparse ** delta;

  delta = (matrix_sparse **) malloc(sizeof(matrix_sparse *) * (d + 1));
  if (delta == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for delta\n",
      sizeof(matrix_sparse *) * (d + 1));
    return NULL;
  }
  delta[0] = matrix_sparse_product(b[0], a[0]);
  if (delta[0] == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate delta[0]\n", stderr);
    matrix_sparse_array_free(delta, 1);
    return NULL;
  }
  for (p = 1; p < d; ++p)
  {
    delta[p] = matrix_sparse_laplacian_p(a[p - 1], a[p], b[p - 1], b[p]);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot calculate delta[%d]\n", p);
      matrix_sparse_array_free(delta, p + 1);
      return NULL;
    }
  }
  delta[d] = matrix_sparse_product(a[d - 1], b[d - 1]);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot calculate delta[%d]\n", p);
    matrix_sparse_array_free(delta, d + 1);
    return NULL;
  }
  return delta;
}

void matrix_sparse_laplacian_file_print(
  FILE * out, int d, matrix_sparse ** a, matrix_sparse ** b,
  const char * format)
{
  int p;
  matrix_sparse * delta_p;

  /* p = d */
  p = 0;
  delta_p = matrix_sparse_product(b[p], a[p]);
  if (delta_p == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot calculate %d-laplacian\n", p);
    return;
  }
  matrix_sparse_file_print(out, delta_p, format);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot print %d-laplacian in format %s\n", p, format);
    matrix_sparse_free(delta_p);
    return;
  }
  matrix_sparse_free(delta_p);
  fputc('\n', out);

  /* p = 1 ... d - 1 */
  for (p = 1; p < d; ++p)
  {
    delta_p = matrix_sparse_laplacian_p(a[p - 1], a[p], b[p - 1], b[p]);
    if (delta_p == NULL)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot calculate %d-laplacian\n", p);
      return;
    }
    matrix_sparse_file_print(out, delta_p, format);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot print %d-laplacian in format %s\n", p, format);
      matrix_sparse_free(delta_p);
      return;
    }
    matrix_sparse_free(delta_p);
    fputc('\n', out);
  }

  /* p = d */
  p = d;
  delta_p = matrix_sparse_product(a[p - 1], b[p - 1]);
  if (delta_p == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot calculate %d-laplacian\n", p);
    return;
  }
  matrix_sparse_file_print(out, delta_p, format);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot print %d-laplacian in format %s\n", p, format);
    matrix_sparse_free(delta_p);
    return;
  }
  matrix_sparse_free(delta_p);
}
