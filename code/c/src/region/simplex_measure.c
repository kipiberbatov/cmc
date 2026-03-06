#include <math.h>

#include "int.h"
#include "simplex.h"

static double determinant(int n, double a[3][3])
{
  switch (n)
  {
  case 0:
    return 1;
  case 1:
    return a[0][0];
  case 2:
    return a[0][0] * a[1][1] - a[0][1] * a[1][0];
  case 3:
    return a[0][0] * a[1][1] * a[2][2] - a[0][0] * a[1][2] * a[2][1]
         + a[1][0] * a[2][1] * a[0][2] - a[1][0] * a[0][1] * a[2][2]
         + a[2][0] * a[0][1] * a[1][2] - a[2][0] * a[1][1] * a[0][2];
  default:
    return 0.;
  }
}

static double matrix_vol_regular(int s_dim, double s_reference_map[3][3])
{
  return fabs(determinant(s_dim, s_reference_map));
}

static void matrix_transpose_times_itself(
  double res[3][3], int n, int m, double a[3][3])
{
  int i, j, k;
  double a_k_i;
  double * a_k, * res_i;

  for (k = 0; k < m; ++k)
  {
    a_k = a[k];
    for (i = 0; i < n; ++i)
    {
      a_k_i = a_k[i];
      res_i = res[i];
      for (j = 0; j < n; ++j)
        res_i[j] += a_k_i * a_k[j];
    }
  }
}

static double matrix_vol_irregular(
  int s_dim, int s_dim_embedded, double s_reference_map[3][3])
{
  double tmp_matrix[3][3] = {{0.,0.,0.},{0.,0.,0.},{0.,0.,0.}};
  matrix_transpose_times_itself(
    tmp_matrix, s_dim, s_dim_embedded, s_reference_map);
  return sqrt(determinant(s_dim, tmp_matrix));
}

double simplex_measure(const simplex * s)
{
  int node, p, s_dim, s_dim_embedded, tmp;
  double s_measure_times_factorial;
  double * s_coord;
  double s_reference_map[3][3];

  s_dim = s->dim;
  s_dim_embedded = s->dim_embedded;
  s_coord = s->coord;
  for (node = 0; node < s_dim; ++node)
  {
    tmp = s_dim_embedded * (node + 1);
    for (p = 0; p < s_dim_embedded; ++p)
      s_reference_map[p][node] = s_coord[tmp + p] - s_coord[p];
  }
  s_measure_times_factorial = (s_dim == s_dim_embedded) ?
    matrix_vol_regular(s_dim, s_reference_map) :
    matrix_vol_irregular(s_dim, s_dim_embedded, s_reference_map);
  return s_measure_times_factorial / ((double) int_factorial(s_dim));
}
