#include "mesh_qc.h"

/*
Consider the bilinear form
A: C^{d - 1} M * C^{d - 1} M -> R,
A(q, r) := <r, kappa_{d - 1}^{-1} q>.
We are calculating its matrix
a in M_{cn[d - 1] * cn_[d - 1]}(R)
in the standard bases, that is,
a_{i, j} := <c^{d - 1, j}, kappa_{d - 1}^{-1} c^{d - 1, i}>.
Its nonzero values are along the diagonal, i.e.,
a_{i, i} = <c^{d - 1, i}, kappa_{d - 1}^{-1} c^{d - 1, i}>
         = <c^{d - 1, i}, c^{d - 1, i}> / kappa_{d - 1}[i].

For the actual implementation we only calculate and store the diagonal values
in a preallocated array a of size cn[d - 1].
*/

void
mesh_qc_matrix_diagonal_from_inner_of_basis_dm1_and_inverse_kappa_dm1_basis_dm1(
  double * a,
  const mesh * m,
  const double * m_inner_dm1,
  const double * kappa_dm1)
{
  int i, m_cn_dm1;

  m_cn_dm1 = m->cn[m->dim - 1];
  for (i = 0; i < m_cn_dm1; ++i)
    a[i] = m_inner_dm1[i] / kappa_dm1[i];
}
