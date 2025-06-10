#include "diffusion_transient_continuous.h"

/*
[Example of transient diffusion in 2D via exterior calculus]

Let
  . M = [0, 20] x [0, 15]
  . pi_0 = 4
  . kappa_1 = 6
  . u_0(x, y) = {100 if x = 20, 0 else}
  . f = 0
  . G_D = {0, 20} x [0, 15]
  . G_N = [0, 20] x {0, 15}
  . g_D = {(0, y) |-> 0, (20, y) |-> 100}
  . g_N = 0

The potential 0-form u and flow rate 1-form q are solutions to the problem
  . q = - *_1 kappa_1 d_0 u
  . D_t Q = - d q + f
  . D_t Q = *_0 (D_t (pi_0 u))
  . tr_{G_D, 0} u = g_D
  . tr_{G_N, 1} q = g_N
  . u(0, x, y) = u_0(x, y)

This problem has the following exact steady-state solution
  . u(x, y) = 5 x
  . q(x, y) = - 30 dy
*/

static double pi_0(const double * x)
{
  return 4.;
}

static double kappa_1(const double * x)
{
  return 6.;
}

static double initial(const double * x)
{
  if (x[0] == 20. && (0. <= x[1] && x[1] <= 15.))
    return 100.;
  else
    return 0.;
}

static double source(const double * x)
{
  return 0;
}

static int boundary_dirichlet(const double * x)
{
  return (x[0] == 0 || x[0] == 20.) && (0. <= x[1] && x[1] <= 15.);
}

static double g_dirichlet(const double * x)
{
  if (x[0] == 0. && (0. <= x[1] && x[1] <= 15.))
    return 0.;
  else if (x[0] == 20. && (0. <= x[1] && x[1] <= 15.))
    return 100.;
  /* unreachable */
  return -100;
}

static int boundary_neumann(const double * x)
{
  return ((x[1] == 0. || x[1] == 15.) && (0. <= x[0] && x[0] <= 20.));
}

static double g_neumann(const double * x)
{
  return 0;
}

const struct diffusion_transient_continuous
diffusion_transient_continuous_2d_d02_p01 =
{
  pi_0,
  kappa_1,
  initial,
  source,
  boundary_dirichlet,
  g_dirichlet,
  boundary_neumann,
  g_neumann
};
