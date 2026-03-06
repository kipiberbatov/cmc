#include <stdlib.h>
#include "matrix_sparse.h"
#include "mesh.h"

matrix_sparse * mesh_coboundary_p(matrix_sparse * m_bd_p)
{
  matrix_sparse * m_cbd_p;

  m_cbd_p = matrix_sparse_transpose(m_bd_p);
  /* NULL pointer check */
  return m_cbd_p;
}

matrix_sparse ** mesh_coboundary(int m_dim, matrix_sparse ** m_bd)
{
  int p;
  matrix_sparse ** m_cbd;

  m_cbd = (matrix_sparse **) malloc(sizeof(matrix_sparse *) * m_dim);
  /* NULL pointer check */

  for (p = 0; p < m_dim; ++p)
  {
    m_cbd[p] = mesh_coboundary_p(m_bd[p]);
    /* NULL pointer check */
  }
  return m_cbd;
}

// void mesh_coboundary_file_print(FILE * out, int m_dim, matrix_sparse ** m_bd)
// {
//   int p;
//   matrix_sparse * m_bd_p_plus_1, * m_cbd_p;
//   //matrix_sparse * m_cbd;
//
//   //m_cbd = mesh_coboundary(m_bd);
//   /* NULL pointer check */
//   for (p = 0; p < m_dim; ++p)
//   {
//     m_bd_p_plus_1 = m_bd[p];
//     m_cbd_p = matrix_sparse_transpose(m_bd_p_plus_1, 1);
//     /* NULL pointer check */
//     double_file_print_array_raw(out, m_cbd_p->nzmax, m_cbd_p->x);
//     matrix_sparse_free(m_cbd_p);
//   }
// }
//
// void mesh_coboundary_file_print_file_scan(FILE * out, FILE * in)
// {
//   int m_dim;
//   mesh * m;
//   matrix_sparse ** m_bd;
//
//   m = mesh_file_scan(in);
//   /* NULL pointer check */
//   m_dim = m->dim;
//   m_bd = mesh_file_scan_boundary(in, m);
//   /* NULL pointer check */
//   mesh_coboundary_file_print(out, m_dim, m_bd);
//   /* NULL pointer check */
//   matrix_sparse_free_array(m_bd, m_dim);
//   mesh_free(m);
// }
