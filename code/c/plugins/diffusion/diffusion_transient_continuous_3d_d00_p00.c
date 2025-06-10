#include "diffusion_transient_continuous.h"

/*
[Example of transient diffusion in 3D via exterior calculus]

Let
  . M = [0, 1]^3
  . pi_0 = 1
  . kappa_1 = 1
  . u_0 = {(0, y, z) |-> 100, (x, y, z) |-> 0 if x > 0}
  . f = 0
  . G_D = {(x, y, z) in G | x in {0, 1}}
  . G_N = {(x, y, z) in G | y in {0, 1} or z in {0, 1}}
  . g_D = {(0, y, z) |-> 100, (1, y, z) |-> 0}
  . g_N = 0

The potential 0-form u and flow rate 1-form q are solutions to the problem
  . q = - *_1 kappa_1 d_0 u
  . D_t Q = - d q + f
  . D_t Q = *_0 (D_t (pi_0 u))
  . tr_{G_D, 0} u = g_D
  . tr_{G_N, 1} q = g_N
  . u(0, x, y, z) = u_0(x, y, z)

The steady-state version of this problem has exact solution
  . u(x, y, z) = 100 (1 - x)
  . q(x, y, z) = 100 dy /\ dz
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
  if (x[0] == 0.)
    return 100.;
  else
    return 0.;
}

static double source(const double * x)
{
  return 0.;
}

static int boundary_dirichlet(const double * x)
{
  return
    (x[0] == 0. || x[0] == 1.) &&
    (0. <= x[1] && x[1] <= 1.) &&
    (0. <= x[2] && x[2] <= 1.);
}

static double g_dirichlet(const double * x)
{
  if (x[0] == 0.)
    return 100.;
  else
    return 0.;
}

static int boundary_neumann(const double * x)
{
  return
    ( ((x[1] == 0. || x[1] == 1.) && (0. <= x[2] && x[2] <= 1.)) ||
      ((x[2] == 0. || x[2] == 1.) && (0. <= x[1] && x[1] <= 1.))
    ) &&
    (0. <= x[0] && x[0] <= 1.);
}

static double g_neumann(const double * x)
{
  return 0.;
}

const struct diffusion_transient_continuous
diffusion_transient_continuous_3d_d00_p00 =
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
