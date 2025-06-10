#include "diffusion_steady_state_continuous.h"

/*
[Example of steady-state diffusion in 2D via exterior calculus]

Let
  . M = {(x, y) in R^2 | x^2 + y^2 <= 1}
  . kappa_1 = 1
  . f = - 4 dx /\ dy
  . G be the boundary of M, i.e., G = {(x, y) in R^2 | x^2 + y^2 = 1}
  . G_D = {(x, y) in G | x >= 0}
  . G_N = {(x, y) in G | x <= 0}
  . g_D = 1
  . g_N = 2 t dt (with respect to the (x, y) = (cos(t), sin(t)) coordinates)

The potential 0-form u and flow rate 1-form q are solutions to the problem
  . q = - *_1 kappa_1 d_0 u
  . d q = f
  . tr_{G_D, 0} u = g_D
  . tr_{G_N, 1} q = g_N

This problem has exact solution
  . u(x, y) = x^2 + y^2
  . q(x, y) = 2 y dx - 2 x dy
*/

#define EPSILON 0.00001

static int on_unit_circle(const double * x)
{
  double error = x[0] * x[0] + x[1] * x[1] - 1;
  if (error < EPSILON && -error < EPSILON)
    return 1;
  return 0;
}

static double kappa_1(const double * x)
{
  return 1.;
}

static double source(const double * x)
{
  return -4.;
}

static int boundary_dirichlet(const double * x)
{
  return (on_unit_circle(x) && x[0] > -EPSILON );
}

static double g_dirichlet(const double * x)
{
  return 1.;
}

static int boundary_neumann(const double * x)
{
  return (on_unit_circle(x) && x[0] < EPSILON);
}

static double g_neumann(const double * x)
{
  return -2.;
}

const struct diffusion_steady_state_continuous
diffusion_steady_state_continuous_2d_d03_p01 =
{
  kappa_1,
  source,
  boundary_dirichlet,
  g_dirichlet,
  boundary_neumann,
  g_neumann
};
