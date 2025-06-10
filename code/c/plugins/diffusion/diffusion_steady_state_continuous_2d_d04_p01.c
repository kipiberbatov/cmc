#include <math.h>

#include "de_rham.h"
#include "diffusion_steady_state_continuous.h"

/*
[Example of steady-state diffusion in 2D via exterior calculus]

Let
  . M = {(x, y, z) in R^3 | x^2 + y^2 + z^2 = 1, z >= 0}, i.e.,
    M = {(sin(theta) cos(phi), sin(theta) sin(phi), cos(theta))
         | 0 <= theta <= pi / 2, 0 <= phi <= 2 pi}
  . kappa_1 = KAPPA
  . ~f(theta, phi) = 6 KAPPA cos(2 phi) sin^3(theta) d theta /\ d phi, i.e.,
    f(x, y, z) = 6 KAPPA (x^2 - y^2) vol
  . G be the boundary of M, i.e.,
    G = {(cos(phi), sin(phi), 0) | 0 <= phi <= 2 pi}
  . G_D = {(x, y, z) in G_D | y <= 0}
  . G_N = {(x, y, z) in G_D | y >= 0}
  . ~g_D(theta, phi)|_{theta = pi / 2} = cos(2 phi), i.e.,
    g_D(x, y, z)|_{z = 0} = x^2 - y^2
  . ~g_N(theta, phi) = 0, i.e.,
    g_N(x, y, z) = 0

The potential 0-form u and flow rate 1-form q are solutions to the problem
  . q = - *_1 kappa_1 d_0 u
  . d q = f
  . tr_{G_D, 0} u = g_D
  . tr_{G_N, 1} q = g_N

This problem has exact solution
  . ~u(theta, phi) = sin^2(theta) cos(2 phi), i.e.,
    u(x, y, z) = x^2 - y^2
  . ~q(theta, phi) = - KAPPA (2 sin(theta) sin(2 phi) d theta
                              + sin(theta) sin(2 theta) cos(2 phi) d phi)
*/

#define EPSILON 0.00001
#define KAPPA 2.

static double double_square(double z) {return z * z;}

static int on_unit_circle(const double * x)
{
  double error = double_square(x[0]) + double_square(x[1]) - 1;
  if (error < EPSILON && -error < EPSILON)
    return 1;
  return 0;
}

static double kappa_1(const double * x)
{
  return KAPPA;
}

static double double_cube(double x){return x * x * x;}

/* with coefficient before d theta /\ d phi in spherical coordinates */
static double source(const double * x)
{
  double theta = x[0];
  double phi = x[1];
  return 6 * KAPPA * cos(2 * phi) * double_cube(sin(theta));
}

static int boundary_dirichlet(const double * x)
{
  return on_unit_circle(x) && x[1] < EPSILON;
}

static double g_dirichlet(const double * x)
{
  return double_square(x[0]) - double_square(x[1]);
}

static int boundary_neumann(const double * x)
{
  return on_unit_circle(x) && x[1] > -EPSILON;
}

static double g_neumann(const double * x)
{
  return 0;
}

const struct diffusion_steady_state_continuous
diffusion_steady_state_continuous_2d_d04_p01 =
{
  kappa_1,
  source,
  boundary_dirichlet,
  g_dirichlet,
  boundary_neumann,
  g_neumann
};
