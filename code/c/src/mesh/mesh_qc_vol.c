#include <stdlib.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "double_array2.h"
#include "mesh_private.h"
#include "mesh_qc.h"

static double mesh_qc_vol_p_i(const jagged2 * m_cf_p_0, int m_dim_embedded,
                              double * m_coord, int p, int i)
{
  double s_coord[24]; /* m_dim_embeddded = 3 -> nodes = 8 -> product = 24 */
  quasi_cube s;
  jagged1 m_cf_p_0_i;

  s.dim_embedded = m_dim_embedded;
  s.dim = p;
  jagged2_part1(&m_cf_p_0_i, m_cf_p_0, i);
  mesh_cell_coord(s_coord, &m_cf_p_0_i, m_dim_embedded, m_coord);
  s.coord = s_coord;
  return quasi_cube_measure(&s);
}

static void mesh_qc_vol_nonzero(double * m_vol_p, const mesh_qc * m, int p)
{
  int i, m_cn_p;
  jagged2 m_cf_p_0;

  m_cn_p = m->cn[p];
  mesh_cf_part2(&m_cf_p_0, m, p, 0);
  for (i = 0; i < m_cn_p; ++i)
    m_vol_p[i] = mesh_qc_vol_p_i(&m_cf_p_0, m->dim_embedded, m->coord, p, i);
}

double * mesh_qc_vol_p(const mesh_qc * m, int p)
{
  double * m_vol_p;

  m_vol_p = (double *) malloc(sizeof(double) * m->cn[p]);
  if (m_vol_p == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytes of memory for m_vol[%d]\n",
      sizeof(double) * m->cn[p], p);
    return NULL;
  }

  if (p == 0)
    double_array_assign_constant(m_vol_p, m->cn[p], 1.);
  else
    mesh_qc_vol_nonzero(m_vol_p, m, p);

  return m_vol_p;
}

double ** mesh_qc_vol(const mesh_qc * m)
{
  int d, p;
  double ** m_vol;

  d = m->dim;

  m_vol = (double **) malloc(sizeof(double *) * (d + 1));
  if (m_vol == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytes of memory for m_vol\n",
      sizeof(double *) * (d + 1));
    return NULL;
  }

  for(p = 0; p <= d; ++p)
  {
    m_vol[p] = mesh_qc_vol_p(m, p);
    if (m_vol[p] == NULL)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot calculate m_vol[%d]\n", p);
      double_array2_free(m_vol, p);
      return NULL;
    }
  }

  return m_vol;
}
