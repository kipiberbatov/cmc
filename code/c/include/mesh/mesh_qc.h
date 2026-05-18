#ifndef _mesh_qc_h
#define _mesh_qc_h

#include "mesh.h"
#include "quasi_cube.h"

typedef mesh mesh_qc;

/******************************** mesh_qc_vol *********************************/
double * mesh_qc_vol_p(const mesh_qc * m, int p);
double ** mesh_qc_vol(const mesh_qc * m);

/******************************* mesh_qc_metric *******************************/
vector_sparse ** mesh_qc_metric_p(
  const mesh_qc * m, int p, const double * m_vol_p);

vector_sparse *** mesh_qc_metric(const mesh_qc * m, double ** m_vol);

vector_sparse **
mesh_qc_metric_p_file_scan(FILE * in, const mesh_qc * m, int p);

vector_sparse *** mesh_qc_metric_file_scan(FILE * in, const mesh_qc * m);

/************************** mesh_qc_metric_corrected **************************/
vector_sparse ** mesh_qc_metric_corrected_p(
  const mesh_qc * m, int p, const double * m_vol_p,
  const double * node_curvatures);

vector_sparse *** mesh_qc_metric_corrected(
  const mesh_qc * m, double ** m_vol, const double * node_curvatures);

/***************************** mesh_qc_integrate ******************************/
double mesh_qc_integrate(const mesh_qc * m, const double * m_vol_d,
                         const vector_sparse * a);

/******************************* mesh_qc_inner ********************************/
double * mesh_qc_inner_p(const mesh_qc * m, const double * m_vol_d,
                         int p, vector_sparse ** m_metric_p);

double ** mesh_qc_inner(const mesh_qc * m, const double * m_vol_d,
                        vector_sparse *** m_metric);

double * mesh_qc_inner_direct_p(
  const mesh_qc * m,
  int p,
  const double * m_vol_p,
  const double * m_vol_q
);

double ** mesh_qc_inner_direct(const mesh_qc * m);
/************************** mesh_qc_coboundary_star ***************************/
/* q = p - 1 */
matrix_sparse * mesh_qc_coboundary_star_p(
  const mesh_qc * m, int p, const matrix_sparse * m_bd_p,
  const double * m_inner_p, const double * m_inner_q);

matrix_sparse ** mesh_qc_coboundary_star(
  const mesh_qc * m, matrix_sparse ** m_bd, double ** m_inner);

/******************************* mesh_qc_hodge ********************************/
matrix_sparse * mesh_qc_hodge_p(
  const mesh_qc * m, matrix_sparse ** m_bd, int p,
  const double * m_inner_q, const double * m_coeff_q);

matrix_sparse ** mesh_qc_hodge(const mesh_qc * m, matrix_sparse ** m_bd,
                               double ** m_inner, double ** m_coeff);

void mesh_qc_hodge_star_0(
  double * cochain_d,
  const mesh_qc * m,
  const double * m_vol_d,
  const double * cochain_0);

void mesh_qc_hodge_star_d(
  double * cochain_0,
  const mesh * m,
  const double * m_vol_d,
  const double * cochain_d);

/******************************************************************************/
/*                                 miscelaneous                               */
/******************************************************************************/

/************************ mesh_qc_hodge_codifferential ************************/
matrix_sparse * mesh_qc_hodge_codifferential_p(
  int m_dim, int p, const matrix_sparse * m_cbd_m_dim_minus_p,
  matrix_sparse ** m_hodge);

matrix_sparse ** mesh_qc_hodge_codifferential(
  int m_dim, matrix_sparse ** m_cbd, matrix_sparse ** m_hodge);

/***************************** mesh_qc_elasticity *****************************/
matrix_sparse * mesh_qc_elasticity_coboundary_star_1(
  const mesh_qc * m, const matrix_sparse * m_bd_1, const double * m_inner_1,
  const double * m_inner_0, double lambda, double mu);

matrix_sparse * mesh_qc_elasticity_coboundary_star_2(
  const mesh_qc * m, const matrix_sparse * m_bd_2,
  const double * m_inner_2, const double * m_inner_1, double mu);

/*************************** mesh_qc_boundary_layer ***************************/
jagged1 * mesh_qc_boundary_layer_0_hyperfaces(const mesh * m);

jagged1 * mesh_qc_boundary_layer_0_cells(
  const mesh * m, const jagged1 * m_bd_layer_0_hyperfaces);

jagged1 * mesh_qc_boundary_layer_0_1_nodes(
  const mesh * m, const jagged1 * m_bd_layer_0_cells);

/************ vectors and matrices for discrete weak formulations *************/

void mesh_qc_vector_from_integral_of_basis_0_cup_d_cochain(
  double * f,
  const mesh_qc * m,
  const double * source);

void mesh_qc_vector_from_boundary_integral_of_basis_0_cup_dm1_cochain(
  double * g,
  const mesh_qc * m,
  const jagged1 * boundary_neumann_dm1,
  const double * g_neumann);

void mesh_qc_vector_from_boundary_integral_of_basis_dm1_cup_0_cochain(
  double * g,
  const mesh_qc * m,
  const matrix_sparse * m_bd_d,
  const jagged1 * boundary_dirichlet_dm1,
  const double * g_dirichlet);

void mesh_qc_vector_from_inner_of_basis_d_cochain_and_d_cochain(
  double * f,
  const mesh_qc * m,
  const double * m_inner_d,
  const double * source);

void
mesh_qc_matrix_diagonal_from_inner_of_basis_dm1_and_inverse_kappa_dm1_basis_dm1(
  double * a,
  const mesh_qc * m,
  const double * m_inner_dm1,
  const double * kappa_dm1);

void mesh_qc_matrix_diagonal_from_inner_of_basis_0_and_pi_0_basis_0(
  double * a,
  const mesh_qc * m,
  const double * m_inner_0,
  const double * pi_0);

matrix_sparse *
mesh_qc_matrix_sparse_from_inner_of_delta_basis_0_and_kappa_1_delta_basis_0(
  const mesh_qc * m,
  const double * m_inner_1,
  const double * kappa_1);

matrix_sparse *
mesh_qc_matrix_sparse_from_integral_of_basis_0_cup_delta_basis_dm1(
  const mesh_qc * m,
  const matrix_sparse * m_cbd_dm1);

matrix_sparse *
mesh_qc_matrix_sparse_from_inner_of_basis_d_and_delta_basis_dm1(
  const matrix_sparse * m_bd_d,
  const double * m_inner_d);

#endif /* _mesh_qc_h */
