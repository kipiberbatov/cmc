#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "int.h"
#include "mesh_private.h"
#include "quasi_cube.h"
#include "simplex.h"

void mesh_measure_single(double * m_measure_p, const mesh * m, int p)
{
  int i, m_dim_embedded, m_cn_p;
  int * m_cn;
  double * m_coord;
  double s_coord[24]; /* m_dim_embeddded = 3 -> nodes = 8 -> product = 24 */
  simplex s;
  quasi_cube qc;
  jagged1 m_cf_p_0_i;
  jagged2 m_cf_p_0;

  if (p == 0)
  {
    double_array_assign_constant(m_measure_p, m->cn[0], 1.);
    return;
  }

  m_dim_embedded = m->dim_embedded;
  m_cn = m->cn;
  m_coord = m->coord;

  s.dim_embedded = m_dim_embedded;
  qc.dim_embedded = m_dim_embedded;
  s.coord = s_coord;
  qc.coord = s_coord;

  s.dim = p;
  s.coord = s_coord;
  mesh_cf_part2(&m_cf_p_0, m, p, 0);
  m_cn_p = m_cn[p];
  for (i = 0; i < m_cn_p; ++i)
  {
    jagged2_part1(&m_cf_p_0_i, &m_cf_p_0, i);
    mesh_cell_coord(s_coord, &m_cf_p_0_i, m_dim_embedded, m_coord);
    if (m_cf_p_0_i.a0 == p + 1)
      m_measure_p[i] = simplex_measure(&s);
    else if (m_cf_p_0_i.a0 == (1 << p))
      m_measure_p[i] = quasi_cube_measure(&qc);
  }
}

/* finds the volumes of a simplicial mesh or of a quasi-cubical mesh */
double * mesh_measure(const mesh * m)
{
  int i, ind, m_dim_embedded, d, m_cn_p, m_vol_size, p;
  int * m_cn;
  double * m_coord, * m_vol;
  double s_coord[24]; /* m_dim_embeddded = 3 -> nodes = 8 -> product = 24 */
  simplex s;
  quasi_cube s2;
  jagged1 m_cf_p_0_i;
  jagged2 m_cf_p_0;

  m_dim_embedded = m->dim_embedded;
  d = m->dim;
  m_cn = m->cn;
  m_coord = m->coord;

  s.dim_embedded = m_dim_embedded;
  s2.dim_embedded = m_dim_embedded;
  s.coord = s_coord;
  s2.coord = s_coord;

  m_vol_size = int_array_total_sum(d + 1, m_cn);
  m_vol = (double *) malloc(sizeof(double) * m_vol_size);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m_vol_size, "m_vol");
    return NULL;
  }

  double_array_assign_constant(m_vol, m_cn[0], 1.);

  ind = m_cn[0];
  for (p = 1; p <= d; ++p)
  {
    s.dim = p;
    s.coord = s_coord;
    mesh_cf_part2(&m_cf_p_0, m, p, 0);
    m_cn_p = m_cn[p];
    for (i = 0; i < m_cn_p; ++i)
    {
      jagged2_part1(&m_cf_p_0_i, &m_cf_p_0, i);
      mesh_cell_coord(s_coord, &m_cf_p_0_i, m_dim_embedded, m_coord);
      if (m_cf_p_0_i.a0 == p + 1)
        m_vol[ind] = simplex_measure(&s);
      else if (m_cf_p_0_i.a0 == (1 << p))
        m_vol[ind] = quasi_cube_measure(&s2);
      ++ind;
    }
  }
  return m_vol;
}
