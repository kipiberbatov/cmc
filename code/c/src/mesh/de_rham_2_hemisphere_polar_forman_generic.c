#include <math.h>

#include "de_rham.h"
#include "cmc_rectangle.h"

static void de_rham_2_of_faces_to_nodes_in_inner_circle(
  double * x, int * index,
  int na, double r_squared, double theta_1, double phi_1,
  double (*f)(const double *),
  double (*average_value)(const void *, double (*)(const double *)))
{
  int _index, j;
  double factor, phi_j0, phi_j1, phi_j2, theta_2, value;
  struct cmc_rectangle rectangle;

  factor = r_squared * theta_1 * phi_1;
  theta_2 = 2 * theta_1;

  _index = *index;
  for (j = 0; j < na / 2; ++j)
  {
    phi_j0 = (2 * j + 0) * phi_1;
    phi_j1 = (2 * j + 1) * phi_1;
    phi_j2 = (2 * j + 2) * phi_1;

    /* [0, theta_1] x [phi_{2 j}, phi_{2 j + 2}] */
    rectangle.x0 = 0;
    rectangle.x1 = theta_1;
    rectangle.y0 = phi_j0;
    rectangle.y1 = phi_j2;
    value = average_value((const void *) &rectangle, f);
    x[_index + 0] = 2 * factor * value;

    /* [theta_1, theta_2] x [phi_{2 j}, phi_{2 j + 1}] */
    rectangle.x0 = theta_1;
    rectangle.x1 = theta_2;
    rectangle.y1 = phi_j1;
    value = average_value((const void *) &rectangle, f);
    x[_index + 1] = factor * value;

    /* [theta_1, theta_2] x [phi_{2 j + 1}, phi_{2 j + 2}] */
    rectangle.y0 = phi_j1;
    rectangle.y1 = phi_j2;
    value = average_value((const void *) &rectangle, f);
    x[_index + 2] = factor * value;

    _index += 3;
  }
  *index = _index;
}

static void de_rham_2_of_faces_to_nodes_in_outer_circles(
  double * x, int * index,
  int na, int nd, double r_squared, double theta_1, double phi_1,
  double (*f)(const double *),
  double (*average_value)(const void *, double (*)(const double *)))
{
  int _index, i, j;
  double factor, phi_j0, phi_j1, phi_j2, theta_i0, theta_i1, theta_i2, value;
  struct cmc_rectangle rectangle;

  factor = r_squared * theta_1 * phi_1;

  _index = *index;
  for (i = 1; i < nd / 2; ++i)
  {
    theta_i0 = (2 * i + 0) * theta_1;
    theta_i1 = (2 * i + 1) * theta_1;
    theta_i2 = (2 * i + 2) * theta_1;
    for (j = 0; j < na / 2; ++j)
    {
      phi_j0 = (2 * j + 0) * phi_1;
      phi_j1 = (2 * j + 1) * phi_1;
      phi_j2 = (2 * j + 2) * phi_1;

      /* [theta_{2 i}, theta_{2 i + 1}] x [phi_{2 j}, phi_{2j + 1}] */
      rectangle.x0 = theta_i0;
      rectangle.x1 = theta_i1;
      rectangle.y0 = phi_j0;
      rectangle.y1 = phi_j1;
      value = average_value((const void *) &rectangle, f);
      x[_index + 0] = factor * value;

      /* [theta_{2 i + 1}, theta_{2 i + 2}] x [phi_{2 j}, phi_{2j + 1}] */
      rectangle.x0 = theta_i1;
      rectangle.x1 = theta_i2;
      value = average_value((const void *) &rectangle, f);
      x[_index + 1] = factor * value;

      /* [theta_{2 i + 1}, theta_{2 i + 2}] x [phi_{2 j + 1}, phi_{2j + 2}] */
      rectangle.y0 = phi_j1;
      rectangle.y1 = phi_j2;
      value = average_value((const void *) &rectangle, f);
      x[_index + 2] = factor * value;

      /* [theta_{2 i}, theta_{2 i + 1}] x [phi_{2 j + 1}, phi_{2j + 2}] */
      rectangle.x0 = theta_i0;
      rectangle.x1 = theta_i1;
      value = average_value((const void *) &rectangle, f);
      x[_index + 3] = factor * value;

      _index += 4;
    }
  }
  *index = _index;
}

/*
. x are the computed coefficients of the 2-cochain
. m is the Forman mesh of a polar mesh of a hemisphere
. f is the coefficient before d theta /\ d phi (in spherical coordinates)
. average_value gives the average value of a function in a numerical integration
  rule over a rectangle
*/
void de_rham_2_hemisphere_polar_forman_generic(
  double * x,
  const mesh * m,
  double (*f)(const double *),
  double (*average_value)(const void *, double (*)(const double *)))
{
  int end_index, index, na, nd;
  int * m_cn;
  double phi_1, r, rx, ry, r_squared, theta_1;

  m_cn = m->cn;

  na = 2 * (2 * m_cn[0] - m_cn[1] - 2);
  nd = (m_cn[0] - 1) / na;
  theta_1 = (M_PI / 2) / nd;
  phi_1 = M_PI * 2 / na;
  end_index = na * nd / 4;
  rx = m->coord[3 * end_index + 0] - m->coord[0];
  ry = m->coord[3 * end_index + 1] - m->coord[1];
  r = sqrt(rx * rx + ry * ry);
  r_squared = r * r;

  index = 0;
  de_rham_2_of_faces_to_nodes_in_inner_circle(
    x, &index, na, r_squared, theta_1, phi_1, f, average_value);
  de_rham_2_of_faces_to_nodes_in_outer_circles(
    x, &index, na, nd, r_squared, theta_1, phi_1, f, average_value);
}
