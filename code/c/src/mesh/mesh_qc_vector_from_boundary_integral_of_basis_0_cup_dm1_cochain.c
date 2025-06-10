#include <stdio.h>
#include <stdlib.h>

#include "mesh_qc.h"

/*
subtract from vector g,
$(N^i \_/ g_{gamma}^{d - 1})[gamma]$,
for $N_i$ on the Neumann boundary
*/
void mesh_qc_vector_from_boundary_integral_of_basis_0_cup_dm1_cochain(
  double * g,
  const mesh * m,
  const jagged1 * boundary_hyperfaces,
  const double * coefficients_dm1)
{
  int boundary_hyperfaces_a0, dm1, i, i_local, j, j_local;
  int * boundary_hyperfaces_a1;
  double coefficients_dm1_j, pow_2_dm1;
  jagged1 m_cf_dm1_0_j;
  jagged2 m_cf_dm1_0;

  dm1 = m->dim - 1;
  pow_2_dm1 = (double) (1 << dm1);
  mesh_cf_part2(&m_cf_dm1_0, m, dm1, 0);
  boundary_hyperfaces_a0 = boundary_hyperfaces->a0;
  boundary_hyperfaces_a1 = boundary_hyperfaces->a1;

  for (j_local = 0; j_local < boundary_hyperfaces_a0; ++j_local)
  {
    j = boundary_hyperfaces_a1[j_local];
    coefficients_dm1_j = coefficients_dm1[j_local];
    jagged2_part1(&m_cf_dm1_0_j, &m_cf_dm1_0, j);
    for (i_local = 0; i_local < m_cf_dm1_0_j.a0; ++i_local)
    {
      i = m_cf_dm1_0_j.a1[i_local];
      g[i] -= coefficients_dm1_j / pow_2_dm1;
    }
  }
}
