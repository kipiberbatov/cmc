#include "de_rham.h"
#include "diffusion_transient_continuous.h"

/*
[Example of transient diffusion in 2D via exterior calculus]

Let
  . M = [0, 1]^2
  . pi_0 = 1
  . kappa_1 = 1
  . u_0(x, y) = 0
  . f = - 2 dx /\ dy
  . G_D = {0, 1} x [0, 1]
  . G_N = [0, 1] x {0, 1}
  . g_D = 0
  . g_N = 0

The potential 0-form u and flow rate 1-form q are solutions to the problem
  . q = - *_1 kappa_1 d_0 u
  . D_t Q = - d q + f
  . D_t Q = *_0 (D_t (pi_0 u))
  . tr_{G_D, 0} u = g_D
  . tr_{G_N, 1} q = g_N
  . u(0, x, y) = u_0(x, y)

This problem has the following exact steady-state solution
  . u(x, y) = x (x - 1)
  . q(x, y) = - (2 x - 1) dy
*/

static double pi_0(const double * x)
{
  return 1.;
}

static double kappa_1(const double * x)
{
  return 1.;
}

static double initial(const double * x)
{
  return 0.;
}

static double source(const double * x)
{
  return -2.;
}

static int boundary_dirichlet(const double * x)
{
  return ((x[0] == 0 || x[0] == 1) && 0 <= x[1] && x[1] <= 1);
}

static double g_dirichlet(const double * x)
{
  return 0.;
}

static int boundary_neumann(const double * x)
{
  return ((x[1] == 0 || x[1] == 1) && 0 <= x[0] && x[0] <= 1);
}

static double g_neumann(const double * x)
{
  return 0.;
}

const struct diffusion_transient_continuous
diffusion_transient_continuous_2d_d00_p03 =
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
