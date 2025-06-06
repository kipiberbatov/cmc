#ifndef _matrix_sparse_h
#define _matrix_sparse_h

#include <stdio.h>
#include "jagged.h"

typedef struct matrix_sparse
{
  int rows;
  int cols;
  int * cols_total;
  int * row_indices;
  double * values;
} matrix_sparse;

/* creates an exact copy of a sparse matrix */
matrix_sparse * matrix_sparse_copy(const matrix_sparse * a);

void matrix_sparse_copy_topology(matrix_sparse * b, const matrix_sparse * a);

/* find a[i][j] */
double matrix_sparse_part(const matrix_sparse * a, int i, int j);
double * matrix_sparse_part_pointer(const matrix_sparse * a, int i, int j);

/***************************** matrix_sparse_free *****************************/
/* deallocate heap-allocated sparse matrix a */
void matrix_sparse_free(matrix_sparse * a);

/* deallocate heap-allocated sparse matrix a without topology information */
void matrix_sparse_free_shared(matrix_sparse * a);

/************************** matrix_sparse_file_scan ***************************/
/* Supported formats for "matrix_sparse_file_scan":
 * --raw
 */

/* read a matrix from file "in" given in format "format" */
matrix_sparse * matrix_sparse_file_scan(FILE * in, const char * format);

/* open a file, read the matrix in the specified format and close the file */
matrix_sparse * matrix_sparse_file_scan_by_name(
  const char * name,
  const char * format);


/************************** matrix_sparse_file_print **************************/
/* Supported formats for "matrix_sparse_file_print":
 * --only-values
 * --raw
 * --annotated
 * --matrix-form-raw
 * --matrix-form-curly
 * --mathematica-sparse
 */

/* print in file "out" matrix "a" in format "format" */
void matrix_sparse_file_print(
  FILE * out,
  const matrix_sparse * a,
  const char * format);

/********************* matrix_sparse algebraic operations *********************/
/* multiply matrix a with constant lambda */
void matrix_sparse_scalar_multiply(matrix_sparse * a, double lambda);

/* creates a sparse matrix representing the identity matrix */
matrix_sparse * matrix_sparse_identity(int n);

/* return c = alpha * a + beta * b */
matrix_sparse * matrix_sparse_linear_combination(
  const matrix_sparse * a,
  const matrix_sparse * b,
  double alpha,
  double beta);

/* return c = a + b */
matrix_sparse * matrix_sparse_add(
  const matrix_sparse * a,
  const matrix_sparse * b);

/* return c = a . b */
matrix_sparse * matrix_sparse_product(
  const matrix_sparse * a,
  const matrix_sparse * b);

/* return b = a^T */
matrix_sparse * matrix_sparse_transpose(const matrix_sparse * a);

/* y := a . x + b */
void matrix_sparse_vector_multiply_add(
  double * y,
  const matrix_sparse * a,
  const double * x);

/* Find the a . diagonal(d[0], ..., d[a->cols - 1]) */
void matrix_sparse_multiply_with_diagonal_matrix(
  matrix_sparse * a,
  const double * d);

/* Find the diagonal(d[0], ..., d[a->cols - 1]) . a */
void matrix_sparse_multiply_with_diagonal_matrix_on_the_left(
  matrix_sparse * a,
  const double * d);

void matrix_sparse_add_with_diagonal_matrix(
  matrix_sparse * a,
  const double * d);

/************************* matrix_sparse_linear_solve *************************/
/* Supported methods for "matrix_sparse_linear_solve":
 * --cholesky
 */

/* solve a x = b with a given "method", where x overwrites b;
however, temporary memory is still required */
void matrix_sparse_linear_solve(
  const matrix_sparse * a,
  double * b,
  const char * method);

matrix_sparse * matrix_sparse_cholesky_decomposition(const matrix_sparse * a);

/* find x := l^{-1} x, where l is lower triangular */
void matrix_sparse_lower_triangular_linear_solve(
  double * x, const matrix_sparse * l);

/* find x := l^{-T} x, where l is lower triangular */
void matrix_sparse_lower_triangular_transpose_linear_solve(
  double * x, const matrix_sparse * l);

/**************************** matrix_sparse_remove ****************************/

/* restrict matrix a to specified rows and columns */
matrix_sparse * matrix_sparse_restrict(
  const matrix_sparse * a,
  const jagged1 * rows_complement,
  const jagged1 * cols_complement);

/* restrict the symmetric matrix a to the same rows and columns */
matrix_sparse * matrix_sparse_restrict_symmetric(
  const matrix_sparse * a,
  const jagged1 * rows_complement);

/* remove specified rows and columns from matrix a */
matrix_sparse * matrix_sparse_remove(
  const matrix_sparse * a,
  const jagged1 * rows,
  const jagged1 * cols);

/* remove the same rows and columns from symmetric matrix a */
matrix_sparse * matrix_sparse_remove_symmetric(
  const matrix_sparse * a,
  const jagged1 * rows);

/* solve a_0 x = b, where a_0 = matrix_sparse_remove_symmetric(a, rows) */
double * matrix_sparse_constrained_solve_cholesky(
  const matrix_sparse * a,
  const double * b,
  const jagged1 * rows);

/************** matrix_sparse: preocedures for physical problems **************/
/* return b_1 . a_0 */
matrix_sparse * matrix_sparse_laplacian_0(
  const matrix_sparse * a_0,
  const matrix_sparse * b_1);

/* return a_p_minus_1 . b_p + a_p . b_p_plus_1 */
matrix_sparse * matrix_sparse_laplacian_p(
  const matrix_sparse * a_p_minus_1,
  const matrix_sparse * a_p,
  const matrix_sparse * b_p,
  const matrix_sparse * b_p_plus_1);

/* a_d_minus_1 . b_d */
matrix_sparse * matrix_sparse_laplacian_d(
  const matrix_sparse * a_d_minus_1,
  const matrix_sparse * b_d);

/* return the array if all laplacians */
matrix_sparse ** matrix_sparse_laplacian(
  int d,
  matrix_sparse ** a,
  matrix_sparse ** b);

/* calculate laplacians and print them with freeing result on each step */
void matrix_sparse_laplacian_file_print(
  FILE * out,
  int d,
  matrix_sparse ** a,
  matrix_sparse ** b,
  const char * format);

/* find the symmetric version of laplacian that was computed in orthogonal but
not normalized basis */
void matrix_sparse_laplacian_symmetric(
  matrix_sparse ** delta,
  int d,
  double ** m_inner);

typedef double (*scalar_field)(const double *);

typedef double (*time_dependent_scalar_field)(double, const double *);

typedef int (*boolean_domain)(const double *);

void matrix_sparse_set_identity_rows(
  matrix_sparse * lhs,
  const jagged1 * positions);

/* solve the laplace equation on a grid */
double * matrix_sparse_laplace_equation_solve(
  const matrix_sparse * m_laplacian,
  int m_dim_embedded,
  const double * m_coord,
  const jagged1 * m_nodes_bd,
  scalar_field f,
  scalar_field g_d);

/* solve the Laplace equation on a non-grid by using symmetrization and then
the Cholesky method */
double * matrix_sparse_laplace_equation_solve_non_grid(
  const matrix_sparse * m_laplacian,
  int m_dim_embedded,
  const double * m_coord,
  const double * m_inner,
  const jagged1 * m_nodes_bd,
  scalar_field f,
  scalar_field g_d);

/* supposedly solving the heat equation with Dirichlet boundary conditions */
double * matrix_sparse_heat_conduction_solve_non_grid(
  const matrix_sparse * m_laplacian,
  int m_dim_embedded,
  const double * m_coord,
  const double * m_inner,
  const jagged1 * m_nodes_bd,
  time_dependent_scalar_field f,
  time_dependent_scalar_field g_d,
  scalar_field u_0,
  double tau,
  int N);

matrix_sparse * matrix_sparse_material_product(
  const matrix_sparse * m_cbd_0,
  const double * kappa_1,
  const matrix_sparse * m_cbd_star_1);

void matrix_sparse_neumann_modify(
  matrix_sparse * lhs,
  int i,
  int size_i,
  const int * neighbors,
  const double * coefficients);

/* $b := b a^{-1}$, $a$ points to the diagonal values of a diagonal matrix */
void matrix_sparse_multiply_with_inverse_of_diagonal(
  matrix_sparse * b,
  const double * a);

/* q := q - b u*/
void matrix_sparse_vector_subtract_product(
  double * q,
  const matrix_sparse * b,
  const double * u);

/* solve the mixed problem $a q + b^T u = g, b q = f$ for $q$ and $u$ */
void matrix_sparse_mixed_linear_solve_with_diagonal_top_left_matrix(
  double * q,
  double * u,
  const double * a,
  const matrix_sparse * b,
  const double * g,
  const double * f);

/*
Let
  . $m$ and $n$ be integers, with $m >= n$
  . $a: M_{m * m}(R)$ be a positive diagonal matrix
  . $b: M_{n * m}(R)$ be a sparse matrix of full rank ($n$)
  . $c: M_{n * n}(R)$ be a positive diagonal matrix
  . $g, q: R^m$
  . $f, u: R^n$

We are solving the following linear system for unknowns $q$ and $u$
  | a q + b^t u = g
  | b q - c   u = f
*/
void matrix_sparse_mixed_perturbed_linear_solve_with_diagonal_top_left_matrix(
  double * q,
  double * u,
  const double * a,
  const matrix_sparse * b,
  const double * c,
  const double * g,
  const double * f);

/* restrict $a$ to the columns specify by the array $columns$ */
matrix_sparse * matrix_sparse_columns_restrict(
  const matrix_sparse * a,
  const jagged1 * columns);

/*
solve the mixed problem
$
  (a q)[i] + (b^T u)[i] = g[i], text{for $i$ not in $boundary_neumann$};
  (b q)[k] = f[k],              text{for all $k$};
  q[boundary_neumann->a1[i_local]] = g_neumann[i_local]
$
for $q = flow_rate$ and $u = potential$ */
void matrix_sparse_mixed_constrained_linear_solve_with_diagonal_top_left_matrix(
  double * flow_rate,
  double * dual_potential,
  const double * a,
  const matrix_sparse * b,
  const double * g,
  const double * f,
  const jagged1 * boundary_neumann,
  const double * g_neumann);

/***************************** matrix_sparse_array ****************************/
/* scan an array of matrices of size n */
matrix_sparse ** matrix_sparse_array_file_scan(
  FILE * in,
  int n,
  const char * format);

/* broken, do not use, better to open a file and the scan */
matrix_sparse ** matrix_sparse_array_file_scan_by_name(
  const char * name,
  int n,
  const char * format);

/* print an array of matrices */
void matrix_sparse_array_file_print(
  FILE * out,
  int n,
  matrix_sparse ** a,
  const char * format);

/* deallocate an array of n matrices */
void matrix_sparse_array_free(matrix_sparse ** a, int n);

/* deallocate an array of n matrices sharing a common stencil */
void matrix_sparse_array_free_shared(matrix_sparse ** a, int n);

#endif /* _matrix_sparse_h */
