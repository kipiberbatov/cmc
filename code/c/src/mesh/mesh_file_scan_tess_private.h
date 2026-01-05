#ifndef _mesh_file_scan_tess_private_h
#define _mesh_file_scan_tess_private_h

#include <stdio.h>

void mesh_file_scan_tess_check_preamble(FILE * in, int * status);

int mesh_file_scan_tess_get_dimension(FILE * in, int * status);

void mesh_file_scan_tess_check_text_for_cell(FILE * in, int * status);

int mesh_file_scan_tess_get_number_of_maximal_cells(FILE * in, int * status);

int mesh_file_scan_tess_get_number_of_nodes(FILE * in, int * status);

void mesh_file_scan_tess_get_coordinates(double * coordinates, FILE * in,
  int * status, int d, int cn_0);

void mesh_file_scan_tess_check_text_for_edge(FILE * in, int * status);

int mesh_file_scan_tess_get_number_of_edges(FILE * in, int * status);

void mesh_file_scan_tess_get_edges_to_nodes(int * edges_to_nodes, FILE * in,
  int * status, int cn_1);

void mesh_file_scan_tess_set_boundary_values_1(double * bd_1_values, int cn_1);

void mesh_file_scan_tess_check_text_for_face(FILE * in, int * status);

int mesh_file_scan_tess_get_number_of_faces(FILE * in, int * status);

void mesh_file_scan_tess_get_faces_number_of_sides(
  int * faces_number_of_sides, FILE * in, int * status, int cn_2);

void mesh_file_scan_tess_get_faces_to_subfaces(int * faces_to_subfaces,
  FILE * in, int * status, int cn_2, int faces_total_edges);

void mesh_file_scan_tess_get_boundary_values(double * bd_values_2,
  FILE * in, int * status, int cn_2, int faces_total_edges);

void mesh_file_scan_tess_set_cf_a3(
  int * cf_a3,
  int cn_1,
  int cn_2,
  const int * faces_number_of_sides);

void mesh_file_scan_tess_set_cf_a4(
  int * cf_a4,
  int cn_1,
  int cn_2,
  int faces_total_edges,
  const int * edges_to_nodes,
  const int * faces_number_of_sides,
  const int * faces_to_subfaces);

struct mesh_and_boundary;

void mesh_file_scan_tess_with_options(
  struct mesh_and_boundary ** m_and_bd,
  FILE * in,
  int * status,
  int has_boundary);

#endif /* _mesh_file_scan_tess_private_h */
