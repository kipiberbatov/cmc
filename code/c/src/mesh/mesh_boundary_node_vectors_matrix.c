#include <stdlib.h>

#include "cmc_error_message.h"
#include "mesh.h"

double * mesh_boundary_node_vectors_matrix(const mesh * m, int i)
{
  int d, i0, j, j_local, s;
  jagged1 m_cf_1_0_j, m_fc_0_1_i;
  jagged2 m_cf_1_0, m_fc_0_1;
  double * m_coord, * result;

  d = m->dim_embedded;
  mesh_cf_part2(&m_cf_1_0, m, 1, 0);
  mesh_fc_part2(&m_fc_0_1, m, 0, 1);
  jagged2_part1(&m_fc_0_1_i, &m_fc_0_1, i);
  m_coord = m->coord;

  /* matrix in column major format */
  result = (double *) malloc(sizeof(double) * m_fc_0_1_i.a0 * d);
  if (result == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes memory for result\n",
      sizeof(double) * m_fc_0_1_i.a0 * d);
    return NULL;
  }

  for (j_local = 0; j_local < m_fc_0_1_i.a0; ++ j_local)
  {
    j = m_fc_0_1_i.a1[j_local];
    jagged2_part1(&m_cf_1_0_j, &m_cf_1_0, j);
    i0 = jagged1_couple_other_object(&m_cf_1_0_j, i);
    for (s = 0; s < d; ++s)
      result[d * j_local + s] = m_coord[d * i + s] - m_coord[d * i0 + s];
  }

  return result;
}
