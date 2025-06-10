#include "de_rham.h"
#include "diffusion_steady_state_continuous.h"

/*
[Example of steady-state diffusion in 3D via exterior calculus]

Let
  . M = [0, 1]^3
  . kappa_1 = 1
  . f = 0
  . G be the boundary of M
  . G_D = {(x, y, z) in G | x in {0, 1}}
  . G_N = {(x, y, z) in G | y in {0, 1} or z in {0, 1}}
  . g_D = {(0, y, z) |-> 100, (1, y, z) |-> 0}
  . g_N = 0

The potential 0-form u and flow rate 1-form q are solutions to the problem
  . q = - *_1 kappa_1 d_0 u
  . d q = f
  . tr_{G_D, 0} u = g_D
  . tr_{G_N, 2} q = g_N

This problem has exact solution
  . u(x, y, z) = 100 (1 - x)
  . q(x, y, z) = 100 dy /\ dz
*/

static double kappa_1(const double * x)
{
  return 1.;
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

const struct diffusion_steady_state_continuous
diffusion_steady_state_continuous_3d_d00_p00 =
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
  return 100. * (1. - x[0]);
}

void diffusion_steady_state_continuous_3d_d00_p00_potential(
  double * potential, const struct mesh * m)
{
  de_rham_0(potential, m, u);
}
