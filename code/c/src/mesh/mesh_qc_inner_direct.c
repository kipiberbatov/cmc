#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "double_array2.h"
#include "mesh_private.h"
#include "mesh_qc.h"
#include "mesh_qc_private.h"

static double *
mesh_qc_inner_direct_d(const mesh_qc * m, const double * m_vol_d)
{
  int d, i, m_cn_d;
  double * m_inner_d;

  d = m->dim;
  m_cn_d = m->cn[d];

  m_inner_d = (double *) malloc(sizeof(double) * m_cn_d);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for m_inner[%d]\n",
      sizeof(double) * m_cn_d, d);
    return NULL;
  }
  for (i = 0; i < m_cn_d; ++i)
    m_inner_d[i] = 1 / m_vol_d[i];
  return m_inner_d;
}

static double *
mesh_qc_inner_direct_0(const mesh_qc * m, const double * m_vol_d)
{
  int i, k, k_loc, m_cn_0;
  int * m_fc_0_d_i;
  double d_exp;
  double * m_inner_0;
  jagged2 m_fc_0_d;

  d_exp = (double) (1 << m->dim);
  m_cn_0 = m->cn[0];
  mesh_fc_part2(&m_fc_0_d, m, 0, m->dim);
  m_fc_0_d_i = m_fc_0_d.a2;

  m_inner_0 = (double *) calloc(m_cn_0, sizeof(double));
  if (m_inner_0 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for m_inner[0]\n",
      sizeof(double) * m_cn_0);
    return NULL;
  }
  for (i = 0; i < m_cn_0; ++i)
  {
    for (k_loc = 0; k_loc < m_fc_0_d.a1[i]; ++k_loc)
    {
      k = m_fc_0_d_i[k_loc];
      m_inner_0[i] += m_vol_d[k];
    }
    m_inner_0[i] /= d_exp;
    m_fc_0_d_i += m_fc_0_d.a1[i];
  }
  return m_inner_0;
}

static double * mesh_qc_inner_direct_nontrivial(
  const mesh_qc * m,
  int p,
  const double * m_vol_p,
  const double * m_vol_q)
{
  int i, j, j_loc, k, k_loc, m_cn_p, m_dim, p_exp, q;
  double d_exp, denominator;
  int nodes[8], perp[8]; /* #nodes(quasi_cube) = 2^3 = 8 */
  jagged1 m_fc_p_d_i;
  jagged2 m_cf_d_q, m_cf_p_0, m_cf_q_0, m_fc_p_d;
  double * m_inner_p;

  m_dim = m->dim;
  m_cn_p = m->cn[p];
  p_exp = 1 << p;
  d_exp = (double) (1 << m_dim);
  q = m_dim - p;
  mesh_fc_part2(&m_fc_p_d, m, p, m_dim);
  mesh_cf_part2(&m_cf_d_q, m, m_dim, q);
  mesh_cf_part2(&m_cf_p_0, m, p, 0);
  mesh_cf_part2(&m_cf_q_0, m, q, 0);

  m_inner_p = (double *) calloc(m_cn_p, sizeof(double));
  if (m_inner_p == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for m_inner[%d]\n",
      sizeof(double) * m_cn_p, p);
    return NULL;
  }

  for (i = 0; i < m_cn_p; ++i)
  {
    jagged2_part1(&m_fc_p_d_i, &m_fc_p_d, i);
    for (k_loc = 0; k_loc < m_fc_p_d_i.a0; ++k_loc)
    {
      k = m_fc_p_d_i.a1[k_loc];
      mesh_qc_perpendicular(nodes, perp, &m_cf_d_q, &m_cf_p_0, &m_cf_q_0, i, k);
      for (j_loc = 0; j_loc < p_exp; ++j_loc)
      {
        j = perp[j_loc];
        m_inner_p[i] += m_vol_q[j];
      }
    }
    denominator = d_exp * m_vol_p[i];
    m_inner_p[i] /= denominator;
  }
  return m_inner_p;
}

double * mesh_qc_inner_direct_p(
  const mesh_qc * m,
  int p,
  const double * m_vol_p,
  const double * m_vol_q)
{
  if (p == 0)
    return mesh_qc_inner_direct_0(m, m_vol_q);
  if (p == m->dim)
    return mesh_qc_inner_direct_d(m, m_vol_p);
  return mesh_qc_inner_direct_nontrivial(m, p, m_vol_p, m_vol_q);
}

/* finds all inner products */
double ** mesh_qc_inner_direct(const mesh_qc * m)
{
  int d, p;
  double ** m_inner = NULL, ** m_vol;

  d = m->dim;

  m_vol = mesh_qc_vol(m);
  if (m_vol == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m_vol\n", stderr);
    goto end;
  }

  m_inner = (double **) malloc(sizeof(double *) * (d + 1));
  if (m_inner == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for m_inner\n",
      sizeof(double *) * (d + 1));
    goto m_vol_free;
  }

  for (p = 0; p <= d; ++p)
  {
    m_inner[p] = mesh_qc_inner_direct_p(m, p, m_vol[p], m_vol[d - p]);
    if (m_inner[p] == NULL)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot calculate m_inner[%d]\n", p);
      double_array2_free(m_inner, p);
      goto m_vol_free;
      return NULL;
    }
  }

m_vol_free:
  double_array2_free(m_vol, d + 1);
end:
  return m_inner;
}
