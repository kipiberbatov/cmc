#include <stdio.h>
#include <stdlib.h>

#include "mesh_qc.h"

/*
Consider the linear form
G: C^0 M -> R,
G(w) := (tr_{gamma_neumann, 0} w \_/ g_neumann)[gamma_neumann].
We are calculating its vector
g in R^{cn[0]}
in the standard basis, that is,
g_i := (N^i \_/ g_neumann)[gamma_neumann].
It is nonzero only if N_i is on gamma_neumann, in which case
g_i = sum_{c_{d - 1, j} in gamma_neumann and c_{d - 1, j} > N_i}
        g_neumann[j] / 2^{d - 1}.

In this particular case we are subtracting these values from a populated array
g in R^{cn[0]}.
*/
void mesh_qc_vector_from_boundary_integral_of_basis_0_cup_dm1_cochain(
  double * g,
  const mesh * m,
  const jagged1 * boundary_neumann_dm1,
  const double * g_neumann)
{
  int boundary_neumann_dm1_a0, dm1, i, i_local, j, j_local;
  int * boundary_neumann_dm1_a1;
  double g_neumann_j, pow_2_dm1;
  jagged1 m_cf_dm1_0_j;
  jagged2 m_cf_dm1_0;

  dm1 = m->dim - 1;
  pow_2_dm1 = (double) (1 << dm1);
  mesh_cf_part2(&m_cf_dm1_0, m, dm1, 0);
  boundary_neumann_dm1_a0 = boundary_neumann_dm1->a0;
  boundary_neumann_dm1_a1 = boundary_neumann_dm1->a1;

  for (j_local = 0; j_local < boundary_neumann_dm1_a0; ++j_local)
  {
    j = boundary_neumann_dm1_a1[j_local];
    g_neumann_j = g_neumann[j_local];
    jagged2_part1(&m_cf_dm1_0_j, &m_cf_dm1_0, j);
    for (i_local = 0; i_local < m_cf_dm1_0_j.a0; ++i_local)
    {
      i = m_cf_dm1_0_j.a1[i_local];
      g[i] -= g_neumann_j / pow_2_dm1;
    }
  }
}
