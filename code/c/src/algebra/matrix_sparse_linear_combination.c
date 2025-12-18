#include "cmc_error_message.h"
#include "matrix_sparse_private.h"

matrix_sparse * matrix_sparse_linear_combination(
  const matrix_sparse * a, const matrix_sparse * b, double alpha, double beta)
{
  cs a0, b0;
  cs * result0;
  matrix_sparse * result = NULL;

  matrix_sparse_to_cs(&a0, a);
  matrix_sparse_to_cs(&b0, b);
  result0 = cs_add(&a0, &b0, alpha, beta);
  if (result0 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot find linear combination via cs_add\n", stderr);
    goto end;
  }
  result = (matrix_sparse *) malloc(sizeof(matrix_sparse));
  if (result == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for result\n",
      sizeof(matrix_sparse));
    goto result0_free;
  }
  matrix_sparse_from_cs(result, result0);
result0_free:
  free(result0);
end:
  return result;
}
