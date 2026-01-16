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
  . G_D be the boundary of M, i.e.,
    G_D = {(cos(phi), sin(phi), 0) | 0 <= phi <= 2 pi}
  . G_N = {}
  . ~g_D(theta, phi)|_{theta = pi / 2} = cos(2 phi), i.e.,
    g_D(x, y, z)|_{z = 0} = x^2 - y^2

The potential 0-form u and flow 1-form q are solutions to the problem
  . q = - *_1 kappa_1 d_0 u
  . d q = f
  . tr_{G_D, 0} u = g_D

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
  return on_unit_circle(x);
}

static double g_dirichlet(const double * x)
{
  return double_square(x[0]) - double_square(x[1]);
}

static int boundary_neumann(const double * x)
{
  return 0;
}

const struct diffusion_steady_state_continuous
diffusion_steady_state_continuous_2d_d04_p00 =
{
  kappa_1,
  source,
  boundary_dirichlet,
  g_dirichlet,
  boundary_neumann,
  NULL
};

static double u(const double * x)
{
  return double_square(x[0]) - double_square(x[1]);
}

void
diffusion_steady_state_continuous_2d_d04_p00_exact_potential_hemisphere_polar(
  double * potential, const struct mesh * m)
{
  de_rham_0(potential, m, u);
}

/*
A regular grid for hemisphere has theta and phi on regular intervals
We are expressing meridians and parallels in spherical coordinates
The flow rate through edge E is represented by int_E q
Let K := KAPPA

On a meridian M = [theta_a, theta_b] * {phi_0}, theta_b - theta_a = theta_1,
  int_M q = - int_{theta_a}^{theta_b} K (2 sin(theta) sin(2 phi_0) d theta
          = - 2 K sin(2 phi_0) (cos(theta_a) - cos(theta_b))
          = - 4 K sin(theta_1 / 2) sin((theta_a + theta_b) / 2) sin(2 phi_0)

On a parallel P = {theta_0} * [phi_a, phi_b], phi_b - phi_a = phi_1,
  int_P q = -int_{phi_a}^{phi_b} K (sin(theta_0) sin(2 theta_0) cos(2 phi) d phi
          = - (K / 2) sin(theta_0) sin(2 theta_0) (sin(2 phi_b) - sin(2 phi_a))
          = - K sin(phi_1) sin(theta_0) sin(2 theta_0) cos(phi_a + phi_b)

*/
void
diffusion_steady_state_continuous_2d_d04_p00_exact_flow_rate_hemisphere_polar(
  double * flow_rate,
  const struct mesh * m,
  const struct matrix_sparse * m_bd_1)
{
  int i, index, j, na, nd;
  int * topology;
  double c_m, c_p, d0, d1, m0, m1, p0, p1, s0, s1;
  double phi, theta;
  double * signs;

  signs = m_bd_1->values;

  topology = m->cf->a4;
  i = 0;
  while (topology[i] == 0)
    i += 4;
  na = i / 2;
  nd = (m->cn[2] + na / 2) / na;

  theta = (M_PI / 2.) / (double) nd;
  phi   = (2. * M_PI) / (double) na;
  c_m = 4. * KAPPA * sin(theta / 2.);
  c_p = KAPPA * sin(phi);

  index = 0;

  /* edges to nodes -> all parallels are "even" */
  for (i = 0; i < nd / 2; ++i)
  {
    /* meridians */
    m0 = c_m * sin((4 * i + 1) * theta / 2.);
    m1 = c_m * sin((4 * i + 3) * theta / 2.);
    for (j = 0; j < na / 2; ++j)
    {
      s0 = sin(4 * j * phi);
      flow_rate[index + 0] = + signs[2 * index + 0] * m0 * s0;
      flow_rate[index + 1] = - signs[2 * index + 2] * m1 * s0;
      index += 2;
    }

    /* parallels */
    p0 = c_p * sin(2 * (i + 1) * theta) * sin(4 * (i + 1) * theta);
    for (j = 0; j < na / 2; ++j)
    {
      d0 = cos((4 * j + 1) * phi);
      d1 = cos((4 * j + 3) * phi);
      flow_rate[index + 0] = + signs[2 * index + 0] * p0 * d0;
      flow_rate[index + 1] = - signs[2 * index + 2] * p0 * d1;
      index += 2;
    }
  }

  /* faces to edges -> all parallels are "odd" */

  /* inner faces to edges */
  m1 = c_m * sin(3. * theta / 2.);
  p1 = c_p * sin(theta) * sin(2 * theta);
  for (j = 0; j < na / 2; ++j)
  {
    d0 = cos((4 * j + 1) * phi);
    d1 = cos((4 * j + 3) * phi);
    s1 = sin(2 * (2 * j + 1) * phi);
    flow_rate[index + 0] = + signs[2 * index + 0] * p1 * d0; /* parallel */
    flow_rate[index + 1] = - signs[2 * index + 2] * m1 * s1; /* meridian */
    flow_rate[index + 2] = - signs[2 * index + 4] * p1 * d1; /* parallel */
    index += 3;
  }

  /* outer faces to edges */
  for (i = 1; i < nd / 2; ++i)
  {
    m0 = c_m * sin((4 * i + 1) * theta / 2.);
    m1 = c_m * sin((4 * i + 3) * theta / 2.);
    p1 = c_p * sin((2 * i + 1) * theta) * sin(2 * (2 * i + 1) * theta);
    for (j = 0; j < na / 2; ++j)
    {
      d0 = cos((4 * j + 1) * phi);
      d1 = cos((4 * j + 3) * phi);
      s1 = sin(2 * (2 * j + 1) * phi);
      flow_rate[index + 0] = + signs[2 * index + 0] * m0 * s1; /* meridian */
      flow_rate[index + 1] = + signs[2 * index + 2] * p1 * d0; /* parallel */
      flow_rate[index + 2] = - signs[2 * index + 4] * m1 * s1; /* meridian */
      flow_rate[index + 3] = - signs[2 * index + 6] * p1 * d1; /* parallel */
      index += 4;
    }
  }
}
