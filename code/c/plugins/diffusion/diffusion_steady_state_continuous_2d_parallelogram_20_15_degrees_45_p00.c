#include <math.h>

#include "de_rham.h"
#include "diffusion_steady_state_continuous.h"

/*
[Example of steady-state diffusion in 2D via exterior calculus]

Let
  . a = sqrt(15) / 2
  . M = Polygon((0, 0), (20, 0), (20 + a, a), (a, a))
    M is a parallelogram with sides (20, 15), and angle 45 degrees between them
  . kappa_1 = 1
  . f = 0
  . G_D = Line((0, 0), (a, a)) U Line((20, 0) (20 + a, a)) => x - y in {0, 20}
  . G_N = Line((0, 0), (20, 0)) U Line((a, a) (20 + a, a)) => y in {0, 20}
  . g_D = {Line((0, 0), (a, a)) |-> 20, Line((20, 0) (20 + a, a)) |-> 0}
  . g_N = - dx

The potential 0-form u and flow rate 1-form q are solutions to the problem
  . q = - *_1 kappa_1 d_0 u
  . d q = f
  . tr_{G_D, 0} u = g_D
  . tr_{G_N, 1} q = g_N

This problem has exact solution
  . u(x, y) = 20 - (x - y)
  . q(x, y) = dx + dy
*/

#define EPSILON 0.0001

static double kappa_1(const double * x)
{
  return 1.;
}

static double source(const double * x)
{
  return 0.;
}

static int on_left_boundary(const double * x)
{
  double a = 15. / sqrt(2.), x0 = x[0], x1 = x[1];
  return fabs(x0 - x1) < EPSILON && x0 > -EPSILON && x0 < a + EPSILON;
}

static int on_right_boundary(const double * x)
{
  double a = 15. / sqrt(2.), x0 = x[0], x1 = x[1];
  return fabs(x0 - x1 - 20.) < EPSILON && x0 > 20. - EPSILON
         && x0 < a + 20. + EPSILON;
}

static int boundary_dirichlet(const double * x)
{
  return on_left_boundary(x) || on_right_boundary(x);
}

static double g_dirichlet(const double * x)
{
  if (on_left_boundary(x))
    return 20.;
  else /* on_right_boundary(x) */
    return 0.;
}

static int on_bottom_boundary(const double * x)
{
  return fabs(x[1]) < EPSILON;
}

static int on_top_boundary(const double * x)
{
  double a = 15. / sqrt(2.);
  return fabs(x[1] - a) < EPSILON;
}

static int boundary_neumann(const double * x)
{
  return on_bottom_boundary(x) || on_top_boundary(x);
}

static double g_neumann(const double * x)
{
  if (on_bottom_boundary(x))
    return 1.;
  else /* on_top_boundary(x) */
    return -1.;
}

const struct diffusion_steady_state_continuous
diffusion_steady_state_continuous_2d_parallelogram_20_15_degrees_45_p00 =
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
  return 20. - (x[0] - x[1]);
}

void diffusion_steady_state_continuous_2d_parallelogram_20_15_degrees_45_p00_potential(
  double * potential, const struct mesh * m)
{
  de_rham_0(potential, m, u);
}

void diffusion_steady_state_continuous_2d_parallelogram_20_15_degrees_45_p00_flow_rate(
  double * flow_rate,
  const struct mesh * m,
  const struct matrix_sparse * m_bd_1)
{
  int i, j0, j1, m_cn_1;
  int * m_cf_1_0;
  double value, x0, x1, y0, y1;
  double * m_bd_1_values, * m_coord;

  m_cf_1_0 = m->cf->a4;
  m_cn_1 = m->cn[1];
  m_coord = m->coord;
  m_bd_1_values = m_bd_1->values;

  for (i = 0; i < m_cn_1; ++i)
  {
    j0 = m_cf_1_0[2 * i];
    j1 = m_cf_1_0[2 * i + 1];
    x0 = m_coord[2 * j0];
    y0 = m_coord[2 * j0 + 1];
    x1 = m_coord[2 * j1];
    y1 = m_coord[2 * j1 + 1];
    value = (x1 - x0) + (y1 - y0);
    flow_rate[i] = value * m_bd_1_values[2 * i + 1];
  }
}
