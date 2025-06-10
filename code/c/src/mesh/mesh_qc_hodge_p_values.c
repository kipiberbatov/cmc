#include "mesh_qc_private.h"

static void mesh_qc_hodge_p_values_d(
  double * m_hodge_p_values, const mesh * m,
  const double * m_inner_q, const double * m_coeff_q)
{
  int d, d_exp, i, ind, j, j_loc, m_cn_d;
  jagged1 m_cf_d_0_i;
  jagged2 m_cf_d_0;

  d = m->dim;
  d_exp = 1 << d;
  m_cn_d = m->cn[d];
  mesh_cf_part2(&m_cf_d_0, m, d, 0);

  ind = 0;
  for (i = 0; i < m_cn_d; ++i)
  {
    jagged2_part1(&m_cf_d_0_i, &m_cf_d_0, i);
    for (j_loc = 0; j_loc < d_exp; ++j_loc)
    {
      j = m_cf_d_0_i.a1[j_loc];
      m_hodge_p_values[ind] = (1. / d_exp) * (m_coeff_q[j] / m_inner_q[j]);
      ++ind;
    }
  }
}

static void mesh_qc_hodge_p_values_0(
  double * m_hodge_p_values, const mesh * m,
  const double * m_inner_q, const double * m_coeff_q)
{
  int d, d_exp, i, ind, k, k_loc, m_cn_0;
  jagged1 m_fc_0_d_i;
  jagged2 m_fc_0_d;

  d = m->dim;
  d_exp = 1 << d;
  m_cn_0 = m->cn[0];
  mesh_fc_part2(&m_fc_0_d, m, 0, d);

  ind = 0;
  for (i = 0; i < m_cn_0; ++i)
  {
    jagged2_part1(&m_fc_0_d_i, &m_fc_0_d, i);
    for (k_loc = 0; k_loc < m_fc_0_d_i.a0; ++k_loc)
    {
      k = m_fc_0_d_i.a1[k_loc];
      m_hodge_p_values[ind] = (1. / d_exp) * (m_coeff_q[k] / m_inner_q[k]);
      ++ind;
    }
  }
}

static void mesh_qc_hodge_p_values_nontrivial(
  double * m_hodge_p_values, const mesh * m, matrix_sparse ** m_bd, int p,
  const double * m_inner_q, const double * m_coeff_q)
{
  int d, d_exp, i, ind, j, j_loc, k, k_loc, m_cn_p, node, p_exp, q;
  int nodes[8], perp[8]; /* #nodes(quasi_cube) = 2^3 = 8 */
  double sign;
  jagged1 m_fc_p_d_i;
  jagged2 m_cf_d_q, m_cf_p_0, m_cf_q_0, m_fc_p_d;

  d = m->dim;
  d_exp = 1 << d;
  m_cn_p = m->cn[p];
  p_exp = 1 << p;
  q = d - p;
  mesh_fc_part2(&m_fc_p_d, m, p, d);
  mesh_cf_part2(&m_cf_d_q, m, d, q);
  mesh_cf_part2(&m_cf_p_0, m, p, 0);
  mesh_cf_part2(&m_cf_q_0, m, q, 0);

  ind = 0;
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
        node = nodes[j_loc];
        sign = mesh_qc_cup_product_sign(m_bd, node, q, j, p, i, d, k);
        m_hodge_p_values[ind] = (sign / d_exp) * (m_coeff_q[j] / m_inner_q[j]);
        ++ind;
      }
    }
  }
}

void mesh_qc_hodge_p_values(
  double * m_hodge_p_values, const mesh * m, matrix_sparse ** m_bd, int p,
  const double * m_inner_q, const double * m_coeff_q)
{
  if (p == m->dim)
    mesh_qc_hodge_p_values_d(m_hodge_p_values, m, m_inner_q, m_coeff_q);
  else if (p == 0)
    mesh_qc_hodge_p_values_0(m_hodge_p_values, m, m_inner_q, m_coeff_q);
  else
    mesh_qc_hodge_p_values_nontrivial(m_hodge_p_values, m, m_bd, p, m_inner_q,
                                      m_coeff_q);
}
