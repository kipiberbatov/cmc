#include <stdlib.h>

#include "cmc_error_message.h"
#include "mesh.h"

/* p = d - 1 */
/************************** mesh_boundary_hyperfaces **************************/
static int mesh_boundary_hyperfaces_size(const mesh * m)
{
  int d, i, m_cn_p, size;
  jagged1 m_fc_p_d_i;
  jagged2 m_fc_p_d;

  d = m->dim;
  m_cn_p = m->cn[d - 1];
  mesh_fc_part2(&m_fc_p_d, m, d - 1, d);

  size = 0;
  for (i = 0; i < m_cn_p; ++i)
  {
    jagged2_part1(&m_fc_p_d_i, &m_fc_p_d, i);
    if (m_fc_p_d_i.a0 == 1)
      ++size;
  }
  return size;
}

static void mesh_boundary_hyperfaces_values(int * values, const mesh * m)
{
  int d, i, index, m_cn_p;
  jagged1 m_fc_p_d_i;
  jagged2 m_fc_p_d;

  d = m->dim;
  m_cn_p = m->cn[d - 1];
  mesh_fc_part2(&m_fc_p_d, m, d - 1, d);

  index = 0;
  for (i = 0; i < m_cn_p; ++i)
  {
    jagged2_part1(&m_fc_p_d_i, &m_fc_p_d, i);
    if (m_fc_p_d_i.a0 == 1)
    {
      values[index] = i;
      ++index;
    }
  }
}

jagged1 * mesh_boundary_hyperfaces(const mesh * m)
{
  jagged1 * result;

  result = (jagged1 *) malloc(sizeof(jagged1));
  if (result == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytes of memory for result\n",
      sizeof(jagged1));
    return NULL;
  }
  result->a0 = mesh_boundary_hyperfaces_size(m);

  result->a1 = (int *) malloc(sizeof(int) * result->a0);
  if (result->a1 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytes of memory for result->a1\n",
      sizeof(int) * result->a0);
    free(result);
    return NULL;
  }
  mesh_boundary_hyperfaces_values(result->a1, m);

  return result;
}
