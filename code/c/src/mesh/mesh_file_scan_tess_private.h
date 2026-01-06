#ifndef _mesh_file_scan_tess_private_h
#define _mesh_file_scan_tess_private_h

#include <stdio.h>

void mesh_file_scan_tess_check_preamble(FILE * in, int * status);

int mesh_file_scan_tess_get_dimension(FILE * in, int * status);

void mesh_file_scan_tess_check_text_for_cell(FILE * in, int * status);

int mesh_file_scan_tess_get_number_of_maximal_cells(FILE * in, int * status);

int mesh_file_scan_tess_get_cells_number_0(FILE * in, int * status);

void mesh_file_scan_tess_get_coordinates(double * coordinates, FILE * in,
  int * status, int d, int cn_0);

void mesh_file_scan_tess_check_text_for_edge(FILE * in, int * status);

int mesh_file_scan_tess_get_cells_number_1(FILE * in, int * status);

void mesh_file_scan_tess_get_cells_to_faces_1_0(
  int * cf_1_0, FILE * in, int * status, int cn_1);

void mesh_file_scan_tess_check_text_for_face(FILE * in, int * status);

int mesh_file_scan_tess_get_cells_number_2(FILE * in, int * status);

void mesh_file_scan_tess_get_cells_to_faces_number_2_1(
  int * cfn_2_1, FILE * in, int * status, int cn_2);

void mesh_file_scan_tess_get_cells_to_faces_2_subfaces_mixed(
  int * cf_2_subfaces_mixed, FILE * in, int * status,
  int cn_2, int cfn_2_1_total);

void mesh_file_scan_tess_get_boundary_values_2(double * bd_values_2,
  FILE * in, int * status, int cn_2, int cfn_2_1_total);

struct mesh_and_boundary;

void mesh_file_scan_tess_with_options(
  struct mesh_and_boundary ** m_and_bd,
  FILE * in,
  int * status,
  int has_boundary);

#endif /* _mesh_file_scan_tess_private_h */
