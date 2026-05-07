#include <string.h>

#include "double.h"
#include "mesh_qc.h"

/*
Consider the linear form
G: C^{D - 1} M -> R,
G(r) := (tr_{gamma_dirichlet, d - 1} r \_/ g_dirichlet)[gamma_dirichlet].
We are calculating its vector
g in R^{cn[d - 1]}
in the standard basis, that is,
g_i := (c^{d - 1, i} \_/ g_dirichlet)[gamma_dirichlet].
It is nonzero only if c^{d - 1, i} is on gamma_dirichlet, in which case
g_i = sum_{N_j < c_{d - 1, i}} g_dirichlet[j] / 2^{d - 1}.

In this implementation we are starting with a zero-allocated g in R^{cn[d - 1]}.
Because of how orientation comes on the boundary, signs are used as well.
*/
void mesh_qc_vector_from_boundary_integral_of_basis_dm1_cup_0_cochain(
  double * g,
  const mesh * m,
  const matrix_sparse * m_cbd_dm1,
  const jagged1 * boundary_dirichlet_dm1,
  const double * g_dirichlet)
{
  int boundary_dirichlet_dm1_a0, d, dm1, i, i_local, index, j_local, j;
  int * boundary_dirichlet_dm1_a1;
  double g_i, pow_2_dm1, sign;
  jagged1 m_cf_dm1_0_i, m_fc_dm1_d_i;
  jagged2 m_cf_dm1_0, m_fc_dm1_d;

  d = m->dim;
  dm1 = d - 1;
  pow_2_dm1 = (double) (1 << dm1);
  mesh_cf_part2(&m_cf_dm1_0, m, dm1, 0);
  mesh_fc_part2(&m_fc_dm1_d, m, dm1, d);
  boundary_dirichlet_dm1_a0 = boundary_dirichlet_dm1->a0;
  boundary_dirichlet_dm1_a1 = boundary_dirichlet_dm1->a1;

  for (i_local = 0; i_local < boundary_dirichlet_dm1_a0; ++i_local)
  {
    i = boundary_dirichlet_dm1_a1[i_local];
    g_i = 0;
    jagged2_part1(&m_cf_dm1_0_i, &m_cf_dm1_0, i);
    for (j_local = 0; j_local < m_cf_dm1_0_i.a0; ++j_local)
    {
      j = m_cf_dm1_0_i.a1[j_local];
      g_i += g_dirichlet[j];
    }
    jagged2_part1(&m_fc_dm1_d_i, &m_fc_dm1_d, i);
    index = m_cbd_dm1->cols_total[i];
    sign = m_cbd_dm1->values[index];
    g[i] = g_i * sign / pow_2_dm1;
  }
}
