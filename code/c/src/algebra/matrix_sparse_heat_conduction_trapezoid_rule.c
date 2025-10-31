#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "color.h"
#include "int.h"
#include "double.h"
#include "matrix_sparse.h"

/* Finds the multipliers for the implicit Euler method */
static matrix_sparse *
matrix_sparse_heat_conduction_trapezoid_rule_private(
  const matrix_sparse * laplacian_0,
  double tau,
  double sign)
{
  matrix_sparse * id, * l;

  id = matrix_sparse_identity(laplacian_0->cols);
  if (id == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    cmc_error_message_cannot_calculate("id");
    return NULL;
  }

  l = matrix_sparse_linear_combination(laplacian_0, id, sign * tau / 2, 1);
  if (l == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    cmc_error_message_cannot_calculate("l");
  }

  matrix_sparse_free(id);
  return l;
}

static matrix_sparse *
matrix_sparse_heat_conduction_trapezoid_rule_lhs(
  const matrix_sparse * laplacian_0,
  double tau)
{
  return
    matrix_sparse_heat_conduction_trapezoid_rule_private(laplacian_0, tau, -1);
}

static matrix_sparse *
matrix_sparse_heat_conduction_trapezoid_rule_rhs(
  const matrix_sparse * laplacian_0,
  double tau)
{
  return
    matrix_sparse_heat_conduction_trapezoid_rule_private(laplacian_0, tau, 1);
}

static double * matrix_sparse_multiply_with_vector(
  const matrix_sparse * a,
  const double * b)
{
  int m = a->rows, n = a->cols;
  int i, j;
  double * result = (double *) calloc(m, sizeof(double));
  for (i = 0; i < m; ++i)
    for (j = 0; j < n; ++j)
      result[i] += matrix_sparse_part(a, i, j) * b[j];
  return result;
}

/* Solve the time-dependent Laplacian problem with trapezoid method */
double * matrix_sparse_diffusion(
  const matrix_sparse * laplacian_0,
  const double * lhs,
  const double * u_0,
  double tau,
  int N)
{
  int i, j;
  double * u; /* 2d rectangular array */
  double * tmp, * system_rhs;
  matrix_sparse * l, * r;

  l = matrix_sparse_heat_conduction_trapezoid_rule_lhs(laplacian_0, tau);
  if (l == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    cmc_error_message_cannot_calculate("l");
    goto end;
  }

  r = matrix_sparse_heat_conduction_trapezoid_rule_rhs(laplacian_0, tau);
  if (l == NULL || r == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    cmc_error_message_cannot_calculate("r");
    goto l_free;
  }

  u = (double *) malloc(sizeof(double) * l->cols * (N + 1));
  if (errno)
  {
    color_error_position(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * l->cols * (N + 1), "u");
    goto r_free;
  }
  tmp = (double *) malloc(sizeof(double) * l->cols);
  memcpy(tmp, lhs, sizeof(double) * l->cols);
  for (j = 0; j < l->cols; ++j)
    tmp[j] *= tau;
  //memcpy(u, rhs, sizeof(double) * l->cols);

  system_rhs = (double *) malloc(sizeof(double) * l->cols);
  for (i = 0; i < N; ++i)
  {
    // memcpy(
    //   u + l->cols * i,
    //   u_next + l->cols * (i - 1),
    //   sizeof(double) * l->cols);
    // double_array_add_to(u_next + l->cols * i, l->cols, tmp);
    // free(tmp);
    system_rhs = matrix_sparse_multiply_with_vector(r, u + l->cols * i);
    for (j = 0; j < l->cols; ++j)
      system_rhs[j] += tmp[j];

    // matrix_sparse_linear_solve(l, u_next + l->cols * i, "--cholesky");
    memcpy(u + l->cols * (i + 1), u + l->cols * i, sizeof(double) * l->cols);
    matrix_sparse_linear_solve(l, u + l->cols * (i + 1), "--lu");
    if (errno)
    {
      color_error_position(__FILE__, __LINE__);
      fputs("cannot find u[i]\n", stderr);
      goto u_free;
    }
  }

  matrix_sparse_free(r);
  matrix_sparse_free(l);

  return u;

  /* cleaning if an error occurs */
u_free:
  free(u);
r_free:
  matrix_sparse_free(r);
l_free:
  matrix_sparse_free(l);
end:
  return NULL;
}

// /* Solve the time-dependent Laplacian problem with explicit Euler method */
// double * matrix_sparse_diffusion(
//   const matrix_sparse * laplacian_0,
//   const double * lhs,
//   const double * u_current,
//   double tau,
//   int N)
// {
//   int i;
//   double * u; /* 2d rectangular array */
//   double * tmp;
//   matrix_sparse * l, * r;

//   l = matrix_sparse_heat_conduction_trapezoid_rule_lhs(laplacian_0, tau);
//   r = matrix_sparse_heat_conduction_trapezoid_rule_rhs(laplacian_0, tau);
//   if (errno)
//   {
//     fputs("matrix_sparse_diffusion - cannot calculate l\n", stderr);
//     goto end;
//   }

//   u_next = (double *) malloc(sizeof(double) * l->cols * (N + 1));
//   if (errno)
//   {
//     fputs("matrix_sparse_diffusion - cannot allocate memory for u\n",
//           stderr);
//     goto l_free;
//   }

//   memcpy(u_next, u_current, sizeof(double) * l->cols);
//   for (i = 1; i <= N; ++i)
//   {
//     memcpy(
//       u_next + l->cols * i,
//       u_next + l->cols * (i - 1),
//       sizeof(double) * l->cols);

//     for (int j = 0; j < l->cols; ++j)
//     {
//       tmp *= tau;
//     }
//     double_array_add_to(u_next + l->cols * i, l->cols, tmp);
//     free(tmp);
//     tmp = matrix_sparse_multiply_with_vector(r, u_current + l->cols * i);

//     // matrix_sparse_linear_solve(l, u_next + l->cols * i, "--cholesky");
//     matrix_sparse_linear_solve(l, u_next + l->cols * i, "--lu");
//     if (errno)
//     {
//       fputs("matrix_sparse_diffusion - cannot find u[i]\n", stderr);
//       goto u_next_free;
//     }
//   }

//   matrix_sparse_free(r);
//   matrix_sparse_free(l);

//   return u_next;

//   /* cleaning if an error occurs */
// u_next_free:
//   free(u_next);
// l_free:
//   matrix_sparse_free(r);
//   matrix_sparse_free(l);
// end:
//   return NULL;
// }
