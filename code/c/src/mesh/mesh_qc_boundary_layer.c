#include <stdlib.h>

#include "cmc_error_message.h"
#include "mesh_qc.h"

jagged1 * mesh_qc_boundary_layer_0_hyperfaces(const mesh * m)
{
  int ind, j, m_dim, m_bd_layer_0_hyperfaces_a0;
  int * m_bd_layer_0_hyperfaces_a1;
  jagged1 m_hyperfaces_to_cells_sizes;
  jagged1 * m_bd_layer_0_hyperfaces;

  m_dim = m->dim;
  mesh_fcn_part2(&m_hyperfaces_to_cells_sizes, m, m_dim - 1, m_dim);
  m_bd_layer_0_hyperfaces = (jagged1 *) malloc(sizeof(jagged1));
  if (m_bd_layer_0_hyperfaces == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for m_bd_layer_0_hyperfaces\n",
      sizeof(jagged1));
    return NULL;
  }

  m_bd_layer_0_hyperfaces_a0 = 0;
  for (j = 0; j < m_hyperfaces_to_cells_sizes.a0; ++j)
    if (m_hyperfaces_to_cells_sizes.a1[j] == 1)
      ++m_bd_layer_0_hyperfaces_a0;
  m_bd_layer_0_hyperfaces->a0 = m_bd_layer_0_hyperfaces_a0;

  m_bd_layer_0_hyperfaces_a1 = (int *) malloc(
    sizeof(int) * m_bd_layer_0_hyperfaces_a0);
  if (m_bd_layer_0_hyperfaces_a1 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for m_bd_layer_0_hyperfaces_a0\n",
      sizeof(int) * m_bd_layer_0_hyperfaces_a0);
    free(m_bd_layer_0_hyperfaces);
    return NULL;
  }

  ind = 0;
  for (j = 0; j < m_hyperfaces_to_cells_sizes.a0; ++j)
    if (m_hyperfaces_to_cells_sizes.a1[j] == 1)
    {
      m_bd_layer_0_hyperfaces_a1[ind] = j;
      ++ind;
    }
  m_bd_layer_0_hyperfaces->a1 = m_bd_layer_0_hyperfaces_a1;
  return m_bd_layer_0_hyperfaces;
}

jagged1 * mesh_qc_boundary_layer_0_cells(
  const mesh * m, const jagged1 * m_bd_layer_0_hyperfaces)
{
  int ind, j, m_dim, m_bd_layer_0_cells_duplicated_a0,
      m_bd_layer_0_hyperfaces_a0;
  int * m_bd_layer_0_cells_duplicated_a1, * m_bd_layer_0_hyperfaces_a1;
  jagged1 m_hyperface_to_cells;
  jagged1 * m_bd_layer_0_cells, * m_bd_layer_0_cells_duplicated;
  jagged2 m_hyperfaces_to_cells;

  m_dim = m->dim;
  m_bd_layer_0_hyperfaces_a0 = m_bd_layer_0_hyperfaces->a0;
  m_bd_layer_0_hyperfaces_a1 = m_bd_layer_0_hyperfaces->a1;
  m_bd_layer_0_cells_duplicated = (jagged1 *) malloc(sizeof(jagged1));
  if (m_bd_layer_0_cells_duplicated == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for m_bd_layer_0_cells_duplicated\n",
      sizeof(jagged1));
    return NULL;
  }

  m_bd_layer_0_cells_duplicated_a0 = m_bd_layer_0_hyperfaces_a0;
  m_bd_layer_0_cells_duplicated->a0 = m_bd_layer_0_cells_duplicated_a0;

  m_bd_layer_0_cells_duplicated_a1 = (int *) malloc(
    sizeof(int) * m_bd_layer_0_cells_duplicated_a0);
  if (m_bd_layer_0_cells_duplicated_a1 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for "
      "m_bd_layer_0_cells_duplicated_a1\n",
      sizeof(int) * m_bd_layer_0_cells_duplicated_a0);
    free(m_bd_layer_0_cells_duplicated);
    return NULL;
  }

  mesh_fc_part2(&m_hyperfaces_to_cells, m, m_dim - 1, m_dim);
  for (ind = 0; ind < m_bd_layer_0_cells_duplicated_a0; ++ind)
  {
    j = m_bd_layer_0_hyperfaces_a1[ind];
    jagged2_part1(&m_hyperface_to_cells, &m_hyperfaces_to_cells, j);
    m_bd_layer_0_cells_duplicated_a1[ind] = m_hyperface_to_cells.a1[0];
  }
  m_bd_layer_0_cells_duplicated->a1 = m_bd_layer_0_cells_duplicated_a1;
  m_bd_layer_0_cells = jagged1_delete_duplicates(m_bd_layer_0_cells_duplicated);
  if (m_bd_layer_0_cells == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot delete duplicates\n", stderr);
  }

  jagged1_free(m_bd_layer_0_cells_duplicated);
  return m_bd_layer_0_cells;
}

jagged1 * mesh_qc_boundary_layer_0_1_nodes(
  const mesh * m, const jagged1 * m_bd_layer_0_cells)
{
  int i, i_loc, ind, j_loc, m_dim, m_bd_layer_0_cells_a0,
      m_bd_layer_0_1_nodes_original_a0;
  int * m_bd_layer_0_cells_a1, * m_bd_layer_0_1_nodes_original_a1;
  jagged1 face;
  jagged1 * m_bd_layer_0_1_nodes, * m_bd_layer_0_1_nodes_original;
  jagged2 faces;

  m_dim = m->dim;
  m_bd_layer_0_cells_a0 = m_bd_layer_0_cells->a0;
  m_bd_layer_0_cells_a1 = m_bd_layer_0_cells->a1;
  m_bd_layer_0_1_nodes_original = (jagged1 *) malloc(sizeof(jagged1));
  if (m_bd_layer_0_1_nodes_original == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for m_bd_layer_0_1_nodes_original\n",
      sizeof(jagged1));
    return NULL;
  }

  mesh_cf_part2(&faces, m, m_dim, 0);
  m_bd_layer_0_1_nodes_original_a0 = 0;
  for (i_loc = 0; i_loc < m_bd_layer_0_cells_a0; ++i_loc)
  {
    i = m_bd_layer_0_cells_a1[i_loc];
    jagged2_part1(&face, &faces, i);
    m_bd_layer_0_1_nodes_original_a0 += face.a0;
  }
  m_bd_layer_0_1_nodes_original->a0 = m_bd_layer_0_1_nodes_original_a0;

  m_bd_layer_0_1_nodes_original_a1 = (int *) malloc(
    m_bd_layer_0_1_nodes_original_a0 * sizeof(int));
  if (m_bd_layer_0_1_nodes_original_a1 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for "
      "m_bd_layer_0_cells_duplicated_a1\n",
      sizeof(int) * m_bd_layer_0_1_nodes_original_a0);
    free(m_bd_layer_0_1_nodes_original);
    return NULL;
  }

  ind = 0;
  for (i_loc = 0; i_loc < m_bd_layer_0_cells_a0; ++i_loc)
  {
    i = m_bd_layer_0_cells_a1[i_loc];
    jagged2_part1(&face, &faces, i);
    for (j_loc = 0; j_loc < face.a0; ++j_loc)
    {
      m_bd_layer_0_1_nodes_original_a1[ind] = face.a1[j_loc];
      ++ind;
    }
  }
  m_bd_layer_0_1_nodes_original->a1 = m_bd_layer_0_1_nodes_original_a1;

  m_bd_layer_0_1_nodes = jagged1_delete_duplicates(
    m_bd_layer_0_1_nodes_original);
  if (m_bd_layer_0_1_nodes == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot delete duplicates\n", stderr);
  }

  jagged1_free(m_bd_layer_0_1_nodes_original);
  return m_bd_layer_0_1_nodes;
}
