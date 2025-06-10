#include <math.h>

#include "de_rham.h"
#include "diffusion_steady_state_continuous.h"

/*
[Example of steady-state diffusion in 2D via exterior calculus]

Let
  . A be a positive real number
  . M = "square with nodes {(-A, 0), (0, - A), (A, 0), (0, A)}"
  . kappa_1 = 6
  . f = 0
  . G_D = "sides ((-A, 0), (0, - A)) and ((A, 0), (0, A))"
  . G_N = "sides ((0, - A), (A, 0)) and ((0, A), (-A, 0))"
  . g_D = 100
  . g_N = 0

The potential 0-form u and flow rate 1-form q are solutions to the problem
  . q = - *_1 kappa_1 d_0 u
  . d q = f
  . tr_{G_D, 0} u = g_D
  . tr_{G_N, 1} q = g_N

This problem has exact solution
  . u(x, y) = 50 (1 - (x + y) / A)
  . q(x, y) = (300 / A) (- dx + dy)
*/

#define A 5.

static double kappa_1(const double * x)
{
  return 6.;
}

static double source(const double * x)
{
  return 0;
}

static int boundary_dirichlet(const double * x)
{
  return (fabs(x[0] + x[1] + A) < 0.0001 && -A <= x[0] && x[0] <= 0.)
    || (fabs(x[0] + x[1] - A) < 0.0001 && 0. <= x[0] && x[0] <= A);
}

static double g_dirichlet(const double * x)
{
  if (fabs(x[0] + x[1] + A) < 0.0001)
    return 100.;
  else
    return 0.;
}

static int boundary_neumann(const double * x)
{
  return (fabs(x[1] - x[0] - A) < 0.0001 && -A <= x[0] && x[0] <= 0.)
    || (fabs(x[1] - x[0] + A) < 0.0001 && 0. <= x[0] && x[0] <= A);
}

static double g_neumann(const double * x)
{
  return 0;
}

const struct diffusion_steady_state_continuous
diffusion_steady_state_continuous_2d_d01_p00 =
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
  return 50 * (1 - (x[0] + x[1]) / A);
}

void diffusion_steady_state_continuous_2d_d01_p00_potential(
  double * potential, const struct mesh * m)
{
  de_rham_0(potential, m, u);
}

void diffusion_steady_state_continuous_2d_d01_p00_flow_rate(
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
    value = (300 / A) * ((y1 - y0) - (x1 - x0));
    flow_rate[i] = value * m_bd_1_values[2 * i + 1];
  }
}
