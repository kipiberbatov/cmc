#include <stdlib.h>

#include "cmc_error_message.h"
#include "double.h"
#include "matrix.h"
#include "mesh.h"

double * mesh_boundary_neumann_coefficients(const mesh * m, int i)
{
  int d, size;
  jagged1 m_fc_0_1_i;
  jagged2 m_fc_0_1;
  double * l, * l_inverse; /* matrices */
  double * result; /* vector */
  double normal[2]; /* vector */

  d = m->dim_embedded;
  mesh_fc_part2(&m_fc_0_1, m, 0, 1);
  jagged2_part1(&m_fc_0_1_i, &m_fc_0_1, i);

  size = m_fc_0_1_i.a0;

  l = mesh_boundary_node_vectors_matrix(m, i);
  if (l == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate l", stderr);
    result = NULL;
    goto end;
  }

  l_inverse = (double *) malloc(sizeof(double) * size * d);
  if (l_inverse == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for l_inverse\n",
      sizeof(double) * size * d);
    result = NULL;
    goto l_free;
  }

  result = (double *) calloc(size, sizeof(double));
  if (result == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for result\n",
      sizeof(double) * size);
    goto l_inverse_free;
  }

  matrix_moore_penrose_inverse(l_inverse, d, size, l);
  mesh_boundary_node_normal(normal, m, i);
  matrix_times_vector(result, size, d, l_inverse, normal);

l_inverse_free:
  free(l_inverse);
l_free:
  free(l);
end:
  return result;
}
