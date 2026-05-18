#include "mesh_qc.h"

/*
Consider the linear form
F: C^D M -> R,
F(w) := <source, w>.
We are calculating its vector
f in R^{cn[d]}
in the standard basis, that is,
f_i := <source, c^{d, i}> = <c^{d, i}, c^{d, i}> * source[i].

Here, we work with a preallocated array f in R^{cn[d]}.
*/
void mesh_qc_vector_from_inner_of_basis_d_cochain_and_d_cochain(
  double * f,
  const mesh_qc * m,
  const double * m_inner_d,
  const double * source)
{
  int d, i, m_cn_d;

  d = m->dim;
  m_cn_d = m->cn[d];

  for (i = 0; i < m_cn_d; ++i)
    f[i] = m_inner_d[i] * source[i];
}
