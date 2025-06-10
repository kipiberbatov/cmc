#include <stddef.h>

#include "diffusion_transient_continuous.h"

/*
[Example of transient diffusion in 2D via exterior calculus]

Let
  . M = {(x, y) in R^2 | x^2 + y^2 <= 1}
  . pi_0 = 4
  . kappa_1 = 1
  . u_0(x, y) = 2 - (x^2 + y^2)
  . f = - 4 dx /\ dy
  . G_D be the boundary of M, i.e., G_D = {(x, y) in R^2 | x^2 + y^2 = 1}
  . G_N = {}
  . g_D = 1

The potential 0-form u and flow rate 1-form q are solutions to the problem
  . q = - *_1 kappa_1 d_0 u
  . D_t Q = - d q + f
  . D_t Q = *_0 (D_t (pi_0 u))
  . tr_{G_D, 0} u = g_D
  . tr_{G_N, 1} q = g_N
  . u(0, x, y) = u_0(x, y)

This problem has exact solution in steady-state
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

static double pi_0(const double * x)
{
  return 4.;
}

static double kappa_1(const double * x)
{
  return 1.;
}

static double initial(const double * x)
{
  return 2 - (x[0] * x[0] + x[1] * x[1]);
}

static double source(const double * x)
{
  return -4.;
}

static int boundary_dirichlet(const double * x)
{
  return (on_unit_circle(x));
}

static double g_dirichlet(const double * x)
{
  return 1.;
}

static int boundary_neumann(const double * x)
{
  return 0;
}

const struct diffusion_transient_continuous
diffusion_transient_continuous_2d_d03_p00 =
{
  pi_0,
  kappa_1,
  initial,
  source,
  boundary_dirichlet,
  g_dirichlet,
  boundary_neumann,
  NULL
};
