#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "matrix.h"
#include "mesh.h"
#include "mesh_qc_set_neumann_rows.h"

void mesh_qc_set_neumann_rows(
  struct matrix_sparse * lhs,
  const struct mesh * m,
  const struct jagged1 * boundary_neumann_discrete,
  const double * kappa_1)
{
  int d, i, i_local, m_dim_embedded, neumann_size, size_i, size_max,
      size_max_dm1;
  int * neighbors, * neumann_nodes;
  struct jagged1 * boundary_hyperfaces;
  struct jagged1 m_fc_0_1_i;
  struct jagged2 m_cf_1_0, m_cf_dm1_0, m_fc_0_1, m_fc_0_dm1;
  double m_size;
  double * l, * l_inverse; /* matrices */
  double * hyperface_normals; /* list of vectors */
  double * coefficients; /* vector */
  double normal[3]; /* vector */

  d = m->dim;
  m_dim_embedded = m->dim_embedded;
  mesh_cf_part2(&m_cf_1_0, m, 1, 0);
  mesh_fc_part2(&m_fc_0_1, m, 0, 1);
  mesh_cf_part2(&m_cf_dm1_0, m, d - 1, 0);
  mesh_fc_part2(&m_fc_0_dm1, m, 0, d - 1);
  m_size = mesh_size(m);

  boundary_hyperfaces = mesh_boundary_hyperfaces(m);
  if (boundary_hyperfaces == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate oundary_hyperfaces\n", stderr);
    goto end;
  }

  size_max_dm1 = jagged2_subset_maximal_size(
    boundary_neumann_discrete, &m_fc_0_dm1);

  hyperface_normals = (double *) malloc(sizeof(double) * d * size_max_dm1);
  if (hyperface_normals == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * d * size_max_dm1,
      "hyperface_normals");
    goto boundary_hyperfaces_free;
  }

  size_max = jagged2_subset_maximal_size(boundary_neumann_discrete, &m_fc_0_1);
  l = (double *) malloc(sizeof(double) * m_dim_embedded * size_max);
  if (l == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m_dim_embedded * size_max, "l");
    goto hyperface_normals_free;
  }

  l_inverse = (double *) malloc(sizeof(double) * size_max * m_dim_embedded);
  if (l_inverse == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * size_max * m_dim_embedded,
      "l_inverse");
    goto l_free;
  }

  coefficients = (double *) malloc(sizeof(double) * size_max);
  if (coefficients == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * size_max, "coefficients");
    goto l_inverse_free;
  }

  neighbors = (int *) malloc(sizeof(int) * size_max);
  if (neighbors == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(int) * size_max, "neighbors");
    goto coefficients_free;
  }

  neumann_size = boundary_neumann_discrete->a0;
  neumann_nodes = boundary_neumann_discrete->a1;
  for (i_local = 0; i_local < neumann_size; ++i_local)
  {
    i = neumann_nodes[i_local];
    jagged2_part1(&m_fc_0_1_i, &m_fc_0_1, i);
    size_i = m_fc_0_1_i.a0;

    jagged2_node_neighbors(neighbors, &m_cf_1_0, i, &m_fc_0_1_i);

    mesh_boundary_node_coordinate_vectors_matrix(
      l, m, i, neighbors, &m_fc_0_1_i);

    matrix_moore_penrose_inverse(l_inverse, m_dim_embedded, size_i, l);

    mesh_node_normal(normal, hyperface_normals,
      m, boundary_hyperfaces, &m_cf_dm1_0, &m_fc_0_dm1, m_size, i);

    /* $coefficients = kappa_1[i] * (l_inverse . normal)$ */
    memset(coefficients, 0, sizeof(double) * size_i);
    matrix_times_vector(
      coefficients, size_i, m_dim_embedded, l_inverse, normal);
    double_array_multiply_with(coefficients, size_i, kappa_1[i]);
    matrix_sparse_neumann_modify(lhs, i, size_i, neighbors, coefficients);
  }

  free(neighbors);
coefficients_free:
  free(coefficients);
l_inverse_free:
  free(l_inverse);
l_free:
  free(l);
hyperface_normals_free:
  free(hyperface_normals);
boundary_hyperfaces_free:
  jagged1_free(boundary_hyperfaces);
end:
  return;
}
