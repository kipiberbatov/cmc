#include "de_rham.h"
#include "diffusion_steady_state_continuous.h"

/*
[Example of steady-state diffusion in 3D via exterior calculus]

Let
  . M = [0, 1]^3
  . kappa_1 = 2
  . f = - 12 dx /\ dy /\ dz
  . G be the boundary of M
  . G_D = {(x, y, z) in G | y in {0, 1} or z in {0, 1}}
  . G_N = {(x, y, z) in G | x in {0, 1}}
  . g_D(x, y, z) = x^2 + y^2 + z^2
  . g_N = {(0, y, z) |-> 0, (1, y, z) |-> 4 d y /\ dz}

The potential 0-form u and flow rate 1-form q are solutions to the problem
  . q = - *_1 kappa_1 d_0 u
  . d q = f
  . tr_{G_D, 0} u = g_D
  . tr_{G_N, 2} q = g_N

This problem has exact solution
  . u(x, y, z) = x^2 + y^2 + z^2
  . q(x, y, z) = - 4 (x dy /\ dz + y dz /\ dx + z dx /\ dy)
*/

static double square(double x){return x * x;}

static double kappa_1(const double * x)
{
  return 2.;
}

static double source(const double * x)
{
  return -12.;
}

static int boundary_dirichlet(const double * x)
{
  return
    ( ((x[1] == 0. || x[1] == 1.) && (0. <= x[2] && x[2] <= 1.)) ||
      ((x[2] == 0. || x[2] == 1.) && (0. <= x[1] && x[1] <= 1.))
    ) &&
    (0. <= x[0] && x[0] <= 1.);
}

static double g_dirichlet(const double * x)
{
  return square(x[0]) + square(x[1]) + square(x[2]);
}

static int boundary_neumann(const double * x)
{
  return
    (x[0] == 0. || x[0] == 1.) &&
    (0. <= x[1] && x[1] <= 1.) &&
    (0. <= x[2] && x[2] <= 1.);
}

static double g_neumann(const double * x)
{
  if (x[0] == 0.)
    return 0;
  else
    return 4;
}

const struct diffusion_steady_state_continuous
diffusion_steady_state_continuous_3d_d00_p01 =
{
  kappa_1,
  source,
  boundary_dirichlet,
  g_dirichlet,
  boundary_neumann,
  g_neumann
};

static double u(const double * x)
{
  return square(x[0]) + square(x[1]) + square(x[2]);
}

void diffusion_steady_state_continuous_3d_d00_p01_potential(
  double * potential, const struct mesh * m)
{
  de_rham_0(potential, m, u);
}

static int check_equal_components(
  const double x0[3], const double x1[3],
  const double x2[3], const double x3[3])
{
  if (x0[0] == x1[0] && x1[0] == x2[0] && x2[0] == x3[0])
    return 0;
  if (x0[1] == x1[1] && x1[1] == x2[1] && x2[1] == x3[1])
    return 1;
  if (x0[2] == x1[2] && x1[2] == x2[2] && x2[2] == x3[2])
    return 2;
  return -1;
}

static int
face_perpendicular_axis(const jagged2 * m_cf_2_0, const double * m_coord, int i)
{
  const double * x0, * x1, * x2, * x3;
  jagged1 m_cf_2_0_i;

  jagged2_part1(&m_cf_2_0_i, m_cf_2_0, i);
  x0 = m_coord + 3 * m_cf_2_0_i.a1[0];
  x1 = m_coord + 3 * m_cf_2_0_i.a1[1];
  x2 = m_coord + 3 * m_cf_2_0_i.a1[2];
  x3 = m_coord + 3 * m_cf_2_0_i.a1[3];
  return check_equal_components(x0, x1, x2, x3);
}

static int integer_cube_root(int n)
{
  int i = 1;
  while (1)
  {
    if (i * i * i == n)
      return i;
    ++i;
  }
  return -1;
}

void diffusion_steady_state_continuous_3d_d00_p01_flow_rate(
  double * flow_rate,
  const struct mesh * m,
  const struct matrix_sparse * m_cbd_2)
{
  int i, index, n, m_cn_2, p;
  int * m_cbd_2_cols_total;
  double face_area, value;
  double * m_cbd_2_values, * m_coord;
  jagged1 m_cf_2_0_i;
  jagged2 m_cf_2_0;

  m_cbd_2_values = m_cbd_2->values;
  m_cbd_2_cols_total = m_cbd_2->cols_total;
  n = integer_cube_root(m->cn[3]);
  face_area = 1. / (double) (n * n);
  m_cn_2 = m->cn[2];
  m_coord = m->coord;
  mesh_cf_part2(&m_cf_2_0, m, 2, 0);
  index = 0;
  for (i = 0; i < m_cn_2; ++i)
  {
    p = face_perpendicular_axis(&m_cf_2_0, m_coord, i);
    jagged2_part1(&m_cf_2_0_i, &m_cf_2_0, i);
    value = - 4 * face_area * m_coord[3 * m_cf_2_0_i.a1[0] + p];
    flow_rate[i] = m_cbd_2_values[index] * value;
    index += m_cbd_2_cols_total[i + 1] - m_cbd_2_cols_total[i];
  }
}
