#include <stdlib.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "double_array2.h"
#include "mesh.h"

static void mesh_displacement_values(double ** result,
  const mesh * m, const matrix_sparse * m_bd_0, const double * u)
{
  int i, j, j_loc, m_cn_0, m_dim_embedded;
  double sign;
  double tmp[MAX_DIM];
  double * m_coord;
  jagged1 m_cf_1_0_j, m_fc_0_1_i;
  jagged2 m_cf_1_0, m_fc_0_1;

  m_dim_embedded = m->dim_embedded;
  m_cn_0 = m->cn[0];
  m_coord = m->coord;
  mesh_cf_part2(&m_cf_1_0, m, 1, 0);
  mesh_fc_part2(&m_fc_0_1, m, 0, 1);

  for (i = 0; i < m_cn_0; ++i)
  {
    jagged2_part1(&m_fc_0_1_i, &m_fc_0_1, i);
    for (j_loc = 0; j_loc < m_fc_0_1_i.a0; ++j_loc)
    {
      j = m_fc_0_1_i.a1[j_loc];
      jagged2_part1(&m_cf_1_0_j, &m_cf_1_0, j);
      sign = matrix_sparse_part(m_bd_0, i, j);
      double_array_difference(
        tmp, m_dim_embedded,
        m_coord + m_dim_embedded * m_cf_1_0_j.a1[0],
        m_coord + m_dim_embedded * m_cf_1_0_j.a1[1]);
      double_array_multiply_with(tmp, m_dim_embedded, - sign * u[j]);
      double_array_add_to(result[i], m_dim_embedded, tmp);
    }
  }
}

double ** mesh_displacement(
  const mesh * m, const matrix_sparse * m_bd_0, const double * u)
{
  int i, m_cn_0, m_dim_embedded;
  double ** result;

  m_dim_embedded = m->dim_embedded;
  m_cn_0 = m->cn[0];

  result = (double **) calloc(m_cn_0, sizeof(double *));
  if (result == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for result\n",
      sizeof(double *) * m_cn_0);
    return NULL;
  }

  for (i = 0; i < m_cn_0; ++i)
  {
    result[i] = (double *) calloc(m_dim_embedded, sizeof(double));
    if (result[i] == NULL)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr,
        "cannot allocate %zu bytes of memory for result[%d]\n",
        sizeof(double) * m_dim_embedded, i);
      double_array2_free(result, i);
      return NULL;
    }
  }

  mesh_displacement_values(result, m, m_bd_0, u);

  return result;
}

