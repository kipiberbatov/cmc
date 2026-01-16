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
  . ~f(theta, phi) = - KAPPA cos(theta) d theta /\ d phi
  . G_D be the boundary of M, i.e.,
    G_D = {(cos(phi), sin(phi), 0) | 0 <= phi <= 2 pi}
  . G_N = {}
  . ~g_D(theta, phi)|_{theta = pi / 2} = pi / 2

The potential 0-form u and flow 1-form q are solutions to the problem
  . q = - *_1 kappa_1 d_0 u
  . d q = f
  . tr_{G_D, 0} u = g_D

This problem has exact solution
  . ~u(theta, phi) = theta
  . ~q(theta, phi) = - KAPPA sin(theta) d phi
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

/* with coefficient before d theta /\ d phi in spherical coordinates */
static double source(const double * spherical_point)
{
  double theta = spherical_point[0];
  return - KAPPA * cos(theta);
}

static int boundary_dirichlet(const double * x)
{
  return on_unit_circle(x);
}

static double g_dirichlet(const double * spherical_point)
{
  return M_PI / 2.;
}

static int boundary_neumann(const double * x)
{
  return 0;
}

const struct diffusion_steady_state_continuous
diffusion_steady_state_continuous_2d_d04_p02 =
{
  kappa_1,
  source,
  boundary_dirichlet,
  g_dirichlet,
  boundary_neumann,
  NULL
};

/* sin(theta) = sqrt(x^2 + y^2) */
static double u(const double * x)
{
  double sin_theta = sqrt(double_square(x[0]) + double_square(x[1]));
  return asin(sin_theta - EPSILON / 30); /* accommodate values close to 1 */
}

void
diffusion_steady_state_continuous_2d_d04_p02_exact_potential_hemisphere_polar(
  double * potential, const struct mesh * m)
{
  de_rham_0(potential, m, u);
}

/*
A regular grid for hemisphere has theta and phi on regular intervals
We are expressing meridians and parallels in spherical coordinates
The flow rate through edge E is represented by int_E q
Let K := KAPPA

Through a meridian m_{i, j} = [theta_i, theta_{i + 1}] * {phi_j},
  int_{m_{i, j}} q = 0

Through a parallel p_{i, j} = {theta_i} * [phi_j, phi_{j + 1}],
  int_{p_{i, j}} q = - int_{phi_j}^{phi_{j + 1}} K sin(theta_i) d phi
                   = - K sin(theta_i) phi_1
*/
void
diffusion_steady_state_continuous_2d_d04_p02_exact_flow_rate_hemisphere_polar(
  double * flow_rate,
  const struct mesh * m,
  const struct matrix_sparse * m_bd_1)
{
  int i, index, j, na, nd;
  int * topology;
  double p_i, phi_1, theta_1;
  double * signs;

  signs = m_bd_1->values;

  topology = m->cf->a4;
  i = 0;
  while (topology[i] == 0)
    i += 4;
  na = i / 2;
  nd = (m->cn[2] + na / 2) / na;

  theta_1 = (M_PI / 2.) / (double) nd;
  phi_1   = (2. * M_PI) / (double) na;

  index = 0;

  /* edges to nodes -> all parallels are "even" */
  for (i = 1; i <= nd / 2; ++i)
  {
    /* meridians */
    for (j = 0; j < na / 2; ++j)
    {
      flow_rate[index + 0] = 0;
      flow_rate[index + 1] = 0;
      index += 2;
    }

    /* parallels */
    p_i = KAPPA * sin(2 * i * theta_1) * phi_1;
    for (j = 0; j < na / 2; ++j)
    {
      flow_rate[index + 0] = + signs[2 * index + 0] * p_i;
      flow_rate[index + 1] = - signs[2 * index + 2] * p_i;
      index += 2;
    }
  }

  /* faces to edges -> all parallels are "odd" */

  /* inner faces to edges */
  p_i = KAPPA * sin(theta_1) * phi_1;
  for (j = 0; j < na / 2; ++j)
  {
    flow_rate[index + 0] = + signs[2 * index + 0] * p_i; /* parallel */
    flow_rate[index + 1] = 0;                            /* meridian */
    flow_rate[index + 2] = - signs[2 * index + 4] * p_i; /* parallel */
    index += 3;
  }

  /* outer faces to edges */
  for (i = 1; i < nd / 2; ++i)
  {
    p_i = KAPPA * sin((2 * i + 1) * theta_1) * phi_1;
    for (j = 0; j < na / 2; ++j)
    {
      flow_rate[index + 0] = 0;                            /* meridian */
      flow_rate[index + 1] = + signs[2 * index + 2] * p_i; /* parallel */
      flow_rate[index + 2] = 0;                            /* meridian */
      flow_rate[index + 3] = - signs[2 * index + 6] * p_i; /* parallel */
      index += 4;
    }
  }
}
