#include "cmc_error_message.h"
#include "cmc_memory.h"
#include "int.h"
#include "mesh.h"
#include "mesh_and_boundary.h"
#include "mesh_file_scan_tess_private.h"
#include "mesh_private.h"
#include "string_private.h"

void mesh_file_scan_tess_with_options(
  mesh_and_boundary ** m_and_bd, FILE * in, int * status, int has_boundary)
{
  int d, faces_total_edges, m_c_size, position;
  int cf_a2_size, cf_a3_size, cf_a4_size;
  int * cn = NULL, * edges_to_nodes = NULL, * faces_number_of_sides = NULL,
      * faces_to_subfaces = NULL;
  double * boundary_values_1 = NULL, * boundary_values_2 = NULL,
         * coordinates = NULL;
  double ** boundary_values = NULL;
  mesh * m = NULL;
  jagged4 * cf = NULL;

  mesh_file_scan_tess_check_preamble(in, status);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("the preamble is not in the right format\n", stderr);
    goto end;
  }

  d = mesh_file_scan_tess_get_dimension(in, status);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan dimension\n", stderr);
    goto end;
  }

  mesh_file_scan_tess_check_text_for_cell(in, status);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("the cell text is not in the right format\n", stderr);
    goto end;
  }

  cmc_memory_allocate((void **) m_and_bd, status, sizeof(mesh_and_boundary));
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("m_and_bd");
    goto end;
  }

  cmc_memory_allocate((void **) &m, status, sizeof(mesh));
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("m");
    goto m_and_bd_free;
  }

  m->dim = d;

  cmc_memory_allocate((void **) &cn, status, sizeof(int) * (d + 1));
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("cn");
    goto m_free;
  }

  cn[d] = mesh_file_scan_tess_get_number_of_maximal_cells(in, status);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan the number of maximal cells\n", stderr);
    goto cn_free;
  }

  string_locate_in_file_line(in, status, " **vertex");
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot find the vertex field\n", stderr);
    goto cn_free;
  }

  cn[0] = mesh_file_scan_tess_get_number_of_nodes(in, status);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannnot scan the number of nodes\n", stderr);
    goto cn_free;
  }

  cmc_memory_allocate(
    (void **) &coordinates, status, sizeof(double) * cn[0] * d);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("coordinates");
    goto cn_free;
  }

  mesh_file_scan_tess_get_coordinates(coordinates, in, status, d, cn[0]);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan coordinates\n", stderr);
    goto coordinates_free;
  }

  mesh_file_scan_tess_check_text_for_edge(in, status);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot find the edge field\n", stderr);
    goto coordinates_free;
  }

  cn[1] = mesh_file_scan_tess_get_number_of_edges(in, status);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan the number of edges\n", stderr);
    goto coordinates_free;
  }

  cmc_memory_allocate(
    (void **) &edges_to_nodes, status, sizeof(int) * 2 * cn[1]);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("edges_to_nodes");
    goto coordinates_free;
  }

  mesh_file_scan_tess_get_edges_to_nodes(edges_to_nodes, in, status, cn[1]);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan the edges' nodes\n", stderr);
    goto edges_to_nodes_free;
  }

  if (has_boundary)
  {
    cmc_memory_allocate((void **) &boundary_values, status, sizeof(double) * d);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      cmc_error_message_memory_allocate("boundary_values");
      goto edges_to_nodes_free;
    }
    cmc_memory_allocate(
      (void **) &boundary_values_1, status, sizeof(double) * 2 * cn[1]);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      cmc_error_message_memory_allocate("boundary_values_1");
      goto boundary_values_free;
    }
    mesh_file_scan_tess_set_boundary_values_1(boundary_values_1, cn[1]);
    boundary_values[0] = boundary_values_1;
  }

  mesh_file_scan_tess_check_text_for_face(in, status);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot find the face field\n", stderr);
    goto boundary_values_1_free;
  }

  cn[2] = mesh_file_scan_tess_get_number_of_faces(in, status);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan the number of faces\n", stderr);
    goto boundary_values_1_free;
  }

  cmc_memory_allocate(
    (void **) &faces_number_of_sides, status, sizeof(int) * cn[2]);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("faces_number_of_sides");
    goto boundary_values_1_free;
  }

  position = ftell(in);
  mesh_file_scan_tess_get_faces_number_of_sides(faces_number_of_sides,
    in, status, cn[2]);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan the number of sides per face\n", stderr);
    goto faces_number_of_sides_free;
  }
  fseek(in, position, SEEK_SET);

  faces_total_edges = int_array_total_sum(cn[2], faces_number_of_sides);
  cmc_memory_allocate(
    (void **) &faces_to_subfaces, status, sizeof(int) * 2 * faces_total_edges);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("faces_to_subfaces");
    goto faces_number_of_sides_free;
  }

  position = ftell(in);
  mesh_file_scan_tess_get_faces_to_subfaces(faces_to_subfaces,
    in, status, cn[2], faces_total_edges);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan faces_to_subfaces", stderr);
    goto faces_to_subfaces_free;
  }
  fseek(in, position, SEEK_SET);

  if (has_boundary)
  {
    cmc_memory_allocate(
      (void **) &boundary_values_2, status, sizeof(double) * faces_total_edges);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      cmc_error_message_memory_allocate("boundary_values_2");
      goto faces_to_subfaces_free;
    }
    mesh_file_scan_tess_get_boundary_values(boundary_values_2,
      in, status, cn[2], faces_total_edges);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fputs("cannot scan boundary_values_2\n", stderr);
      goto boundary_values_2_free;
    }
    boundary_values[1] = boundary_values_2;
  }

  cmc_memory_allocate((void **) &cf, status, sizeof(jagged4));
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("cf");
    goto boundary_values_2_free;
  }

  cf->a0 = d;
  cmc_memory_allocate((void **) &(cf->a1), status, sizeof(int) * cf->a0);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("cf->a1");
    goto cf_free;
  }
  mesh_cf_a1(cf->a1, d);

  cf_a2_size = int_array_total_sum(d, cf->a1);
  cmc_memory_allocate((void **) &(cf->a2), status, sizeof(int) * cf_a2_size);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("cf->a2");
    goto cf_a1_free;
  }
  mesh_cf_a2(cf->a2, d, cn);

  cf_a3_size = int_array_total_sum(cf_a2_size, cf->a2);
  cmc_memory_allocate((void **) &(cf->a3), status, sizeof(int) * cf_a3_size);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("cf->a3");
    goto cf_a2_free;
  }
  mesh_file_scan_tess_set_cf_a3(cf->a3, cn[1], cn[2], faces_number_of_sides);

  cf_a4_size = int_array_total_sum(cf_a3_size, cf->a3);
  cmc_memory_allocate((void **) &(cf->a4), status, sizeof(int) * cf_a4_size);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("cf->a4");
    goto cf_a3_free;
  }

  mesh_file_scan_tess_set_cf_a4(cf->a4, cn[1], cn[2], faces_total_edges,
    edges_to_nodes, faces_number_of_sides, faces_to_subfaces);

  m_c_size = int_array_total_sum(d + 1, cn);
  cmc_memory_allocate((void **) &(m->c), status, sizeof(int) * m_c_size);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("m->c");
    goto cf_a4_free;
  }
  cmc_memory_free(faces_to_subfaces);
  cmc_memory_free(faces_number_of_sides);
  cmc_memory_free(edges_to_nodes);

  m->dim = d;
  m->dim_embedded = d;
  m->coord = coordinates;
  m->cn = cn;
  mesh_c(m->c, d, cn);
  m->cf = cf;
  m->fc = NULL;
  (*m_and_bd)->_mesh = m;
  (*m_and_bd)->boundary = boundary_values;
  goto end;

  /* cleaning if an error occurs */
  cmc_memory_free(m->c);
cf_a4_free:
  cmc_memory_free(cf->a4);
cf_a3_free:
  cmc_memory_free(cf->a3);
cf_a2_free:
  cmc_memory_free(cf->a2);
cf_a1_free:
  cmc_memory_free(cf->a1);
cf_free:
  cmc_memory_free(cf);
boundary_values_2_free:
  cmc_memory_free(boundary_values_2);
faces_to_subfaces_free:
  cmc_memory_free(faces_to_subfaces);
faces_number_of_sides_free:
  cmc_memory_free(faces_number_of_sides);
boundary_values_1_free:
  cmc_memory_free(boundary_values_1);
boundary_values_free:
  cmc_memory_free(boundary_values);
edges_to_nodes_free:
  cmc_memory_free(edges_to_nodes);
coordinates_free:
  cmc_memory_free(coordinates);
cn_free:
  cmc_memory_free(cn);
m_free:
  cmc_memory_free(m);
m_and_bd_free:
  cmc_memory_free(m_and_bd);
end:
  return;
}
