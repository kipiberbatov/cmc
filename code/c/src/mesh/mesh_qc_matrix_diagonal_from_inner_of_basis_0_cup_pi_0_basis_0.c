#include "mesh_qc.h"

/*
Consider the bilinear form
A: C^0 M * C^0 M -> R,
A(u, w) := <w, pi_0 u>.
We are calculating its matrix
a in M_{cn[0] * cn_[0]}(R)
in the standard bases, that is,
a_{i, j} := <N^j, pi_0 N^i>.
Its nonzero values are along the diagonal, i.e.,
a_{i, i} = <N^i, pi_0 N^i> = <N^i, N^i> * pi_0[i].

For the actual implementation we only calculate and store the diagonal values
in a preallocated array a of size cn[0].
*/
void mesh_qc_matrix_diagonal_from_inner_of_basis_0_cup_pi_0_basis_0(
  double * a,
  const mesh * m,
  const double * m_inner_0,
  const double * pi_0)
{
  int i, m_cn_0;

  m_cn_0 = m->cn[0];
  for (i = 0; i < m_cn_0; ++i)
    a[i] = m_inner_0[i] * pi_0[i];
}
