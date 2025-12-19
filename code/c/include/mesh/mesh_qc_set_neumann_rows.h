#ifndef _mesh_qc_set_neumann_rows_h
#define _mesh_qc_set_neumann_rows_h

struct jagged1;
struct matrix_sparse;
struct mesh;

void mesh_qc_set_neumann_rows(
  struct matrix_sparse * lhs,
  const struct mesh * m,
  const struct jagged1 * boundary_neumann_discrete,
  const double * kappa_1);

#endif /* _mesh_qc_set_neumann_rows_h */
