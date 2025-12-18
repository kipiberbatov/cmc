#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "int.h"
#include "mesh.h"
#include "mesh_file_scan_tess_private.h"
#include "mesh_private.h"

static mesh * mesh_file_scan_tess_private(int * error, FILE * in);

mesh * mesh_file_scan_tess(FILE * in)
{
  int error = 0;
  mesh * m;

  m = mesh_file_scan_tess_private(&error, in);
  errno = error;
  return m;
}

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

mesh * mesh_file_scan_tess_private(int * error, FILE * in)
{
  int d, faces_total_edges, m_c_size, position;
  int cf_a2_size, cf_a3_size, cf_a4_size;
  int * c = NULL, * cn = NULL, * edges_to_nodes = NULL,
      * faces_number_of_sides = NULL, * faces_to_subfaces = NULL;
  double * coordinates = NULL;
  mesh * m = NULL;
  jagged4 * cf = NULL;


  mesh_file_scan_tess_check_preamble(in, error);
  if (*error)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("incorrect preamble\n", stderr);
    goto clean_on_failure;
  }

  d = mesh_file_scan_tess_get_dimension(in, error);
  if (*error)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan mesh dimension\n", stderr);
    goto clean_on_failure;
  }

  mesh_file_scan_tess_check_text_for_cell(in, error);
  if (*error)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("incorrect text for cell\n", stderr);
    goto clean_on_failure;
  }

  m = (mesh *) malloc(sizeof(mesh));
  if (m == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for m\n",
      sizeof(mesh));
    *error = 1;
    goto clean_on_failure;
  }

  m->dim = d;

  cn = (int *) malloc(sizeof(int) * (d + 1));
  if (cn == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for cn\n",
      sizeof(int) * (d + 1));
    *error = 1;
    goto clean_on_failure;
  }

  /* calculate the number of maximal cells */
  cn[d] = mesh_file_scan_tess_get_number_of_maximal_cells(in, error);
  if (*error)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan number of maximal cells\n", stderr);
    goto clean_on_failure;
  }

  /* check for "\n  *id\n   " */
  mesh_file_scan_tess_check_text_for_id(in, error);
  if (*error)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("incorrect text for IDs\n", stderr);
    goto clean_on_failure;
  }

  /* allocate memory for cell's IDs */
  c = (int *) malloc(sizeof(int) * cn[d]);
  if (c == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for c\n",
      sizeof(int) * cn[d]);
    *error = 1;
    goto clean_on_failure;
  }

  /* check for cells' IDs correctness */
  mesh_file_scan_tess_get_id(c, in, error, cn[d]);
  if (*error)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("incorrect cell IDs\n", stderr);
    goto clean_on_failure;
  }

  /* check for "\n  *crysym\n   triclinic\n  *seed\n" */
  mesh_file_scan_tess_check_text_for_crysym(in, error);
  if (*error)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("incorrect text for crystal symmetry field\n", stderr);
    goto clean_on_failure;
  }

  mesh_file_scan_tess_skip_seed(in, error, cn[d], c);
  if (*error)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("incorrect seed values\n", stderr);
    goto clean_on_failure;
  }

  /* check for "\n  *ori\n   " */
  mesh_file_scan_tess_check_text_for_ori(in, error);
  if (*error)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("incorrect text for orientation field\n", stderr);
    goto clean_on_failure;
  }

  /* ignore orientation values */
  mesh_file_scan_tess_skip_ori(in, error, cn[d]);
  if (*error)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("incorrect orientation values\n", stderr);
    goto clean_on_failure;
  }


  /* check for "\n **vertex\n " */
  mesh_file_scan_tess_check_text_for_vertex(in, error);
  if (*error)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("incorrect text for vertex field\n", stderr);
    goto clean_on_failure;
  }

  /* scan cn[0] */
  cn[0] = mesh_file_scan_tess_get_number_of_nodes(in, error);
  if (*error)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan number of nodes\n", stderr);
    goto clean_on_failure;
  }

  /* allocate memory for coordinates */
  coordinates = (double *) malloc(sizeof(double) * cn[0] * d);
  if (coordinates == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for coordinates\n",
      sizeof(double) * cn[0] * d);
    *error = 1;
    goto clean_on_failure;
  }

  /* scan coordinates */
  mesh_file_scan_tess_get_coordinates(coordinates, in, error, d, cn[0]);
  if (*error)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan coordinates\n", stderr);
    goto clean_on_failure;
  }

  /* check for "\n **edge\n " */
  mesh_file_scan_tess_check_text_for_edge(in, error);
  if (*error)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("incorrect text for edge field\n", stderr);
    goto clean_on_failure;
  }

  /* scan cn[1] */
  cn[1] = mesh_file_scan_tess_get_number_of_edges(in, error);
  if (*error)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan cn[1]\n", stderr);
    goto clean_on_failure;
  }

  /* allocate memory for edges_to_nodes */
  edges_to_nodes = (int *) malloc(sizeof(int) * 2 * cn[1]);
  if (edges_to_nodes == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for edges_to_nodes\n",
      sizeof(int) * 2 * cn[1]);
    *error = 1;
    goto clean_on_failure;
  }

  /* scan edges_to_nodes */
  mesh_file_scan_tess_get_edges_to_nodes(edges_to_nodes, in, error, cn[1]);
  if (*error)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan edges_to_nodes\n", stderr);
    goto clean_on_failure;
  }

  /* todo: if (d == 1) */

  /* check for "\n **face\n " */
  mesh_file_scan_tess_check_text_for_face(in, error);
  if (*error)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("incorrect text for face field\n", stderr);
    goto clean_on_failure;
  }

  /* scan cn[2] */
  cn[2] = mesh_file_scan_tess_get_number_of_faces(in, error);
  if (*error)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan cn[2]\n", stderr);
    goto clean_on_failure;
  }

  faces_number_of_sides = (int * ) malloc(sizeof(int) * cn[2]);
  if (faces_number_of_sides == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for faces_number_of_sides\n",
      sizeof(int) * cn[2]);
    *error = 1;
    goto clean_on_failure;
  }

  position = ftell(in);
  mesh_file_scan_tess_get_faces_number_of_sides(faces_number_of_sides,
    in, error, cn[2]);
  if (*error)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan faces_number_of_sides\n", stderr);
    goto clean_on_failure;
  }
  fseek(in, position, SEEK_SET);

  faces_total_edges = int_array_total_sum(cn[2], faces_number_of_sides);
  /* allocate memory for faces_to_subfaces */
  faces_to_subfaces = (int * ) malloc(sizeof(int) * 2 * faces_total_edges);
  if (faces_to_subfaces == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for faces_to_subfaces\n",
      sizeof(int) * 2 * faces_total_edges);
    *error = 1;
    goto clean_on_failure;
  }

  mesh_file_scan_tess_get_faces_to_subfaces(faces_to_subfaces,
    in, cn[2], faces_total_edges);

  cf = (jagged4 *) malloc(sizeof(jagged4));
  if (cf == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for cf\n",
      sizeof(jagged4));
    *error = 1;
    goto clean_on_failure;
  }

  cf->a0 = d;
  cf->a1 = (int *) malloc(sizeof(int) * cf->a0);
  if (cf->a1 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for cf->a1\n",
      sizeof(int) * cf->a0);
    *error = 1;
    goto clean_on_failure;
  }
  mesh_cf_a1(cf->a1, d);

  cf_a2_size = int_array_total_sum(d, cf->a1);
  cf->a2 = (int *) malloc(sizeof(int) * cf_a2_size);
  if (cf->a2 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for cf->a2\n",
      sizeof(int) * cf_a2_size);
    *error = 1;
    goto clean_on_failure;
  }
  mesh_cf_a2(cf->a2, d, cn);

  cf_a3_size = int_array_total_sum(cf_a2_size, cf->a2);
  cf->a3 = (int *) malloc(sizeof(int) * cf_a3_size);
  if (cf->a3 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for cf->a3\n",
      sizeof(int) * cf_a3_size);
    *error = 1;
    goto clean_on_failure;
  }
  mesh_file_scan_tess_set_cf_a3(cf->a3, cn[1], cn[2], faces_number_of_sides);

  cf_a4_size = int_array_total_sum(cf_a3_size, cf->a3);
  cf->a4 = (int *) malloc(sizeof(int) * cf_a4_size);
  if (cf->a4 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for cf->a4\n",
      sizeof(int) * cf_a4_size);
    *error = 1;
    goto clean_on_failure;
  }
  mesh_file_scan_tess_set_cf_a4(cf->a4, cn[1], cn[2], faces_total_edges,
    edges_to_nodes, faces_number_of_sides, faces_to_subfaces);
  m_c_size = int_array_total_sum(d + 1, cn);
  m->c = (int *) malloc(sizeof(int) * m_c_size);
  if (m->c == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for m->c\n",
      sizeof(int) * m_c_size);
    *error = 1;
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

  return m;

  /* cleaning if an error occurs */
clean_on_failure:
  free(m->c);
  jagged4_free(cf);
  free(faces_to_subfaces);
  free(faces_number_of_sides);
  free(edges_to_nodes);
  free(coordinates);
  free(c);
  free(cn);
  free(m);
  return NULL;
}
