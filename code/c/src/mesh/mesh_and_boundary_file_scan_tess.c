#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "int.h"
#include "mesh.h"
#include "mesh_and_boundary.h"
#include "mesh_file_scan_tess_private.h"
#include "mesh_private.h"

static void mesh_file_scan_tess_set_cf_a4(
  int * cf_a4,
  int cn_1,
  int cn_2,
  int faces_total_edges,
  const int * edges_to_nodes,
  const int * faces_number_of_sides,
  const int * faces_to_subfaces)
{
  int i, index, index_local, j, sides;

  memcpy(cf_a4, edges_to_nodes, sizeof(int) * 2 * cn_1);
  index = 2 * cn_1;
  index_local = 0;
  for (i = 0; i < cn_2; ++i)
  {
    sides = faces_number_of_sides[i];
    for (j = 0; j < sides; ++j)
    {
      cf_a4[index + j] = faces_to_subfaces[index_local + j];
      cf_a4[faces_total_edges + index + j]
      = faces_to_subfaces[index_local + sides + j];
    }
    index += sides;
    index_local += 2 * sides;
  }
}

static void mesh_file_scan_tess_set_cf_a3(int * cf_a3, int cn_1, int cn_2,
  const int * faces_number_of_sides)
{
  int i, index, sides;

  for (i = 0; i < cn_1; ++i)
    cf_a3[i] = 2;
  index = cn_1;
  for (i = 0; i < cn_2; ++i)
  {
    sides = faces_number_of_sides[i];
    cf_a3[index] = sides;
    cf_a3[index + cn_2] = sides;
    ++index;
  }
}

static void mesh_file_scan_tess_set_boundary_values_1(double * bd_1_values, int cn_1)
{
  int i;

  for (i = 0; i < cn_1; ++i)
  {
    bd_1_values[2 * i] = -1;
    bd_1_values[2 * i + 1] = 1;
  }
}

static mesh_and_boundary *
mesh_and_boundary_file_scan_tess_private(int * error, FILE * in)
{
  int d, faces_total_edges, m_c_size, position;
  int cf_a2_size, cf_a3_size, cf_a4_size;
  int * c = NULL, * cn = NULL, * edges_to_nodes = NULL,
      * faces_number_of_sides = NULL, * faces_to_subfaces = NULL;
  double * bd_values_1 = NULL, * bd_values_2 = NULL, * coordinates = NULL;
  double ** bd_values = NULL;
  mesh * m = NULL;
  jagged4 * cf = NULL;
  mesh_and_boundary * m_and_bd = NULL;

  mesh_file_scan_tess_check_preamble(in, error);
  if (*error)
    goto clean_on_failure;

  d = mesh_file_scan_tess_get_dimension(in, error);
  if (*error)
    goto clean_on_failure;

  mesh_file_scan_tess_check_text_for_cell(in, error);
  if (*error)
    goto clean_on_failure;

  m_and_bd = (mesh_and_boundary *) malloc(sizeof(mesh_and_boundary));
  if (!m_and_bd)
  {
    *error = 1;
    fputs("Cannot allocate memory for mesh m_and_bd\n", stderr);
    goto clean_on_failure;
  }

  m = (mesh *) malloc(sizeof(mesh));
  if (!m)
  {
    *error = 1;
    fputs("Cannot allocate memory for mesh m\n", stderr);
    goto clean_on_failure;
  }

  m->dim = d;

  cn = (int *) malloc(sizeof(int) * (d + 1));
  if (!cn)
  {
    *error = 1;
    fputs("Cannot allocate memory for m->cn\n", stderr);
    goto clean_on_failure;
  }

  /* calculate the number of maximal cells */
  cn[d] = mesh_file_scan_tess_get_number_of_maximal_cells(in, error);
  if (*error)
    goto clean_on_failure;

  /* check for "\n  *id\n   " */
  mesh_file_scan_tess_check_text_for_id(in, error);
  if (*error)
    goto clean_on_failure;

  /* allocate memory for cell's IDs */
  c = (int *) malloc(sizeof(int) * cn[d]);
  if (!c)
  {
    *error = 1;
    fputs("Cannot allocate memory for c\n", stderr);
    goto clean_on_failure;
  }

  /* check for cells' IDs correctness */
  mesh_file_scan_tess_get_id(c, in, error, cn[d]);
  if (*error)
    goto clean_on_failure;

  /* check for "\n  *crysym\n   triclinic\n  *seed\n" */
  mesh_file_scan_tess_check_text_for_crysym(in, error);
  if (*error)
    goto clean_on_failure;

  mesh_file_scan_tess_skip_seed(in, error, cn[d], c);
  if (*error)
    goto clean_on_failure;

  /* check for "\n  *ori\n   " */
  mesh_file_scan_tess_check_text_for_ori(in, error);
  if (*error)
    goto clean_on_failure;

  /* ignore orientation values */
  mesh_file_scan_tess_skip_ori(in, error, cn[d]);
  if (*error)
    goto clean_on_failure;


  /* check for "\n **vertex\n " */
  mesh_file_scan_tess_check_text_for_vertex(in, error);
  if (*error)
    goto clean_on_failure;

  /* scan cn[0] */
  cn[0] = mesh_file_scan_tess_get_number_of_nodes(in, error);
  if (*error)
    goto clean_on_failure;

  /* allocate memory for coordinates */
  coordinates = (double *) malloc(sizeof(double) * cn[0] * d);
  if (!coordinates)
  {
    *error = 1;
    fputs("Unable to allocate memory for coordinates\n", stderr);
    goto clean_on_failure;
  }

  /* scan coordinates */
  mesh_file_scan_tess_get_coordinates(coordinates, in, error, d, cn[0]);
  if (*error)
    goto clean_on_failure;

  /* check for "\n **edge\n " */
  mesh_file_scan_tess_check_text_for_edge(in, error);
  if (*error)
    goto clean_on_failure;

  /* scan cn[1] */
  cn[1] = mesh_file_scan_tess_get_number_of_edges(in, error);
  if (*error)
    goto clean_on_failure;

  /* allocate memory for edges_to_nodes */
  edges_to_nodes = (int *) malloc(sizeof(int) * 2 * cn[1]);
  if (!edges_to_nodes)
  {
    *error = 1;
    fputs("Unable to allocate memory for edges_to_nodes\n", stderr);
    goto clean_on_failure;
  }
  /* scan edges_to_nodes */
  mesh_file_scan_tess_get_edges_to_nodes(edges_to_nodes, in, error, cn[1]);
  if (*error)
    goto clean_on_failure;

  bd_values = (double **) malloc(sizeof(double *) * d);
  if (bd_values == NULL)
  {
    *error = 1;
    fprintf(stderr,
      "%s:%d: cannot allocate %zu bytes of memory for bd_values\n",
      __FILE__, __LINE__, sizeof(double *) * d);
    goto clean_on_failure;
  }

  bd_values_1 = (double *) malloc(sizeof(double) * 2 * cn[1]);
  if (bd_values_1 == NULL)
  {
    *error = 1;
    fprintf(stderr,
      "%s:%d: cannot allocate %zu bytes of memory for bd_values_1\n",
      __FILE__, __LINE__, sizeof(double) * 2 * cn[1]);
    goto clean_on_failure;
  }
  mesh_file_scan_tess_set_boundary_values_1(bd_values_1, cn[1]);
  bd_values[0] = bd_values_1;

  /* todo: if (d == 1) */

  /* check for "\n **face\n " */
  mesh_file_scan_tess_check_text_for_face(in, error);
  if (*error)
    goto clean_on_failure;

  /* scan cn[2] */
  cn[2] = mesh_file_scan_tess_get_number_of_faces(in, error);
  if (*error)
    goto clean_on_failure;

  faces_number_of_sides = (int *) malloc(sizeof(int) * cn[2]);
  if (!faces_number_of_sides)
  {
    *error = 1;
    fputs("Unable to allocate memory for faces_number_of_sides\n", stderr);
    goto clean_on_failure;
  }

  position = ftell(in);
  mesh_file_scan_tess_get_faces_number_of_sides(faces_number_of_sides,
    in, error, cn[2]);
  if (*error)
    goto clean_on_failure;
  fseek(in, position, SEEK_SET);

  faces_total_edges = int_array_total_sum(cn[2], faces_number_of_sides);
  /* allocate memory for faces_to_subfaces */
  faces_to_subfaces = (int *) malloc(sizeof(int) * 2 * faces_total_edges);
  if (!faces_to_subfaces)
  {
    *error = 1;
    fputs("Cannot allocate memory for faces_to_edges\n", stderr);
    goto clean_on_failure;
  }

  position = ftell(in);
  mesh_file_scan_tess_get_faces_to_subfaces(faces_to_subfaces,
    in, cn[2], faces_total_edges);
  fseek(in, position, SEEK_SET);

  bd_values_2 = (double *) malloc(sizeof(double) * faces_total_edges);
  if (!bd_values_2)
  {
    *error = 1;
    fputs("Cannot allocate memory for bd_values_2\n", stderr);
    goto clean_on_failure;
  }
  mesh_file_scan_tess_get_boundary_values(bd_values_2,
    in, cn[2], faces_total_edges);
  bd_values[1] = bd_values_2;

  cf = (jagged4 *) malloc(sizeof(jagged4));
  if (errno)
  {
    fprintf(stderr, "%s:%d: cannot allocate memory\n", __FILE__, __LINE__);
    goto clean_on_failure;
  }

  cf->a0 = d;
  cf->a1 = (int *) malloc(sizeof(int) * cf->a0);
  if (errno)
  {
    fprintf(stderr, "%s:%d: cannot allocate memory\n", __FILE__, __LINE__);
    goto clean_on_failure;
  }
  mesh_cf_a1(cf->a1, d);

  cf_a2_size = int_array_total_sum(d, cf->a1);
  cf->a2 = (int *) malloc(sizeof(int) * cf_a2_size);
  if (errno)
  {
    fprintf(stderr, "%s:%d: cannot allocate memory\n", __FILE__, __LINE__);
    goto clean_on_failure;
  }
  mesh_cf_a2(cf->a2, d, cn);

  cf_a3_size = int_array_total_sum(cf_a2_size, cf->a2);
  cf->a3 = (int *) malloc(sizeof(int) * cf_a3_size);
  if (errno)
  {
    fprintf(stderr, "%s:%d: cannot allocate memory\n", __FILE__, __LINE__);
    goto clean_on_failure;
  }
  mesh_file_scan_tess_set_cf_a3(cf->a3, cn[1], cn[2], faces_number_of_sides);

  cf_a4_size = int_array_total_sum(cf_a3_size, cf->a3);
  cf->a4 = (int *) malloc(sizeof(int) * cf_a4_size);
  if (errno)
  {
    fprintf(stderr, "%s:%d: cannot allocate memory\n", __FILE__, __LINE__);
    goto clean_on_failure;
  }
  mesh_file_scan_tess_set_cf_a4(cf->a4, cn[1], cn[2], faces_total_edges,
    edges_to_nodes, faces_number_of_sides, faces_to_subfaces);
  m_c_size = int_array_total_sum(d + 1, cn);
  m->c = (int *) malloc(sizeof(int) * m_c_size);
  if (errno)
  {
    fprintf(stderr, "%s:%d: cannot allocate memory\n", __FILE__, __LINE__);
    goto clean_on_failure;
  }
  free(faces_to_subfaces);
  free(faces_number_of_sides);
  free(edges_to_nodes);
  free(c);

  m->dim = d;
  m->dim_embedded = d;
  m->coord = coordinates;
  m->cn = cn;
  mesh_c(m->c, d, cn);
  m->cf = cf;
  m->fc = NULL;
  m_and_bd->_mesh = m;
  m_and_bd->boundary = bd_values;

  return m_and_bd;

  /* cleaning if an error occurs */
clean_on_failure:
  free(m->c);
  jagged4_free(cf);
  free(bd_values_2);
  free(faces_to_subfaces);
  free(faces_number_of_sides);
  free(bd_values_1);
  free(bd_values);
  free(edges_to_nodes);
  free(coordinates);
  free(c);
  free(cn);
  free(m);
  free(m_and_bd);
  return NULL;
}

mesh_and_boundary * mesh_and_boundary_file_scan_tess(FILE * in)
{
  int error = 0;
  mesh_and_boundary * m_and_bd;

  m_and_bd = mesh_and_boundary_file_scan_tess_private(&error, in);
  errno = error;
  return m_and_bd;
}
