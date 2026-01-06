#ifndef _mesh_private_h
#define _mesh_private_h

#include "mesh.h"

/*********************************** mesh_c ***********************************/
void mesh_c(int * m_c, int m_dim, const int * m_cn);

/********************************** mesh_cf ***********************************/
void mesh_cf_a1(int * m_cf_a1, int m_dim);
void mesh_cf_a2(int * m_cf_a2, int m_dim, const int * m_cn);
void mesh_cf_a3(int * cf_a3, int cn_1, int cn_2, const int * cfn_2_1);

void mesh_cf_a4(
  int * cf_a4,
  int cn_1,
  int cn_2,
  int cfn_2_1_total,
  const int * cf_1_0,
  const int * cfn_2_1,
  const int * cf_2_1);

jagged4 * mesh_cf_file_scan(FILE * in, int m_dim, const int * m_cn);

/************************* mesh_boundary_values_1_set *************************/
void mesh_boundary_values_1_set(double * bd_1_values, int cn_1);

/********************************* mesh_cell **********************************/
void mesh_cell_coord(
  double * s_coord, const jagged1 * m_cf_p_0_i,
  int m_dim_embedded, const double * m_coord);

/******************************* mesh_file_scan *******************************/
mesh * mesh_file_scan_raw(FILE * in);
mesh * mesh_file_scan_tess(FILE * in);

/****************************** mesh_file_print *******************************/
void mesh_file_print_raw(FILE * out, const mesh * a);

#endif /* _mesh_private_h */
