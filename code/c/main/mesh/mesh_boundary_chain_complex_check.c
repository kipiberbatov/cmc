#include <errno.h>

#include "cmc_error_message.h"
#include "mesh.h"

int main(void)
{
  int d, j, nonzero_max, p;
  double * values;
  mesh * m;
  matrix_sparse ** m_bd, * product;
  FILE * in;

  in = stdin;

  m = mesh_file_scan(in, "--raw");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan m\n", stderr);
    goto end;
  }

  m_bd = mesh_file_scan_boundary(in, m);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan m->bd\n", stderr);
    goto m_free;
  }

  d = m->dim;
  for (p = 0; p < d - 1; ++p)
  {
    product = matrix_sparse_product(m_bd[p], m_bd[p + 1]);
    if (product == NULL)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot calculate product bd_%d * bd_%d\n", p + 1, p + 2);
      errno = -1;
      goto m_bd_free;
    }
    nonzero_max = product->cols_total[product->cols];
    values = product->values;
    for (j = 0; j < nonzero_max; ++j)
    {
      if (values[j] != 0)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fputs(
          "nonzero value: see the output file for the full matrix product\n",
          stderr);
        fprintf(stdout, "p = %d, %d |-> %g\n\n", p, j, values[j]);
        matrix_sparse_file_print(stdout, product, "--raw");
        matrix_sparse_free(product);
        errno = 1;
        goto m_bd_free;
      }
    }
    matrix_sparse_free(product);
  }

m_bd_free:
  matrix_sparse_array_free(m_bd, d);
m_free:
  mesh_free(m);
end:
  return errno;
}
