#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "mesh.h"

static int mesh_boundary_lower_subfaces_size(
  const mesh * m,
  int p,
  const jagged1 * m_boundary_hyperfaces)
{
  int d, i, j, j_local, m_cn_p, size;
  int m_boundary_hyperfaces_a0 = m_boundary_hyperfaces->a0;
  int * m_boundary_hyperfaces_a1 = m_boundary_hyperfaces->a1;
  jagged1 m_cf_dm1_p_j;
  jagged2 m_cf_dm1_p; /* dm1 = d - 1 */

  d = m->dim;
  m_cn_p = m->cn[p];
  mesh_cf_part2(&m_cf_dm1_p, m, d - 1, p);

  size = 0;
  for (i = 0; i < m_cn_p; ++i)
  {
    for (j_local = 0; j_local < m_boundary_hyperfaces_a0; ++j_local)
    {
      j = m_boundary_hyperfaces_a1[j_local];
      jagged2_part1(&m_cf_dm1_p_j, &m_cf_dm1_p, j);
      if (jagged1_member(&m_cf_dm1_p_j, i))
      {
        ++size;
        break;
      }
    }
  }
  return size;
}

static void mesh_boundary_lower_subfaces_values(
  int * values,
  const mesh * m,
  int p,
  const jagged1 * m_boundary_hyperfaces)
{
  int d, i, index, j, j_local, m_cn_p;
  int m_boundary_hyperfaces_a0 = m_boundary_hyperfaces->a0;
  int * m_boundary_hyperfaces_a1 = m_boundary_hyperfaces->a1;
  jagged1 m_cf_dm1_p_j;
  jagged2 m_cf_dm1_p; /* dm1 = d - 1 */

  d = m->dim;
  m_cn_p = m->cn[p];
  mesh_cf_part2(&m_cf_dm1_p, m, d - 1, p);

  index = 0;
  for (i = 0; i < m_cn_p; ++i)
  {
    for (j_local = 0; j_local < m_boundary_hyperfaces_a0; ++j_local)
    {
      j = m_boundary_hyperfaces_a1[j_local];
      jagged2_part1(&m_cf_dm1_p_j, &m_cf_dm1_p, j);
      if (jagged1_member(&m_cf_dm1_p_j, i))
      {
        values[index] = i;
        ++index;
        break;
      }
    }
  }
}

jagged1 * mesh_boundary_lower_subfaces(
  const mesh * m,
  int p,
  const jagged1 * m_boundary_hyperfaces)
{
  jagged1 * result;

  result = (jagged1 *) malloc(sizeof(jagged1));
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(jagged1), "result");
    return NULL;
  }
  result->a0 = mesh_boundary_lower_subfaces_size(m, p, m_boundary_hyperfaces);

  result->a1 = (int *) malloc(sizeof(int) * result->a0);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(int) * result->a0, "result->a1");
    free(result);
    return NULL;
  }
  mesh_boundary_lower_subfaces_values(result->a1, m, p, m_boundary_hyperfaces);

  return result;
}
