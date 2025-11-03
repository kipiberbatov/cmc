#include <math.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "mesh.h"
#include "mesh_measures.h"

static void de_rham_2_of_faces_to_nodes_in_inner_circle(
  double * x, int * index,
  int na, double r_squared, double theta_1, double phi_1,
  double (*f)(const double *))
{
  int _index, j;
  double factor, theta_half, theta_one_and_half;
  double point[2];

  factor = r_squared * theta_1 * phi_1;
  theta_half = 0.5 * theta_1;
  theta_one_and_half = 1.5 * theta_1;
  
  _index = *index;
  for (j = 0; j < na / 2; ++j)
  {
    /* [0, theta_1] x [phi_{2 j}, phi_{2 j + 2}] */
    point[0] = theta_half;
    point[1] = (2 * j + 1) * phi_1;
    x[_index + 0] = 2 * factor * f(point);  
    
    /* [theta_1, theta_2] x [phi_{2 j}, phi_{2 j + 1}] */
    point[0] = theta_one_and_half;
    point[1] = (2 * j + 0.5) * phi_1;
    x[_index + 1] = factor * f(point);
    
    /* [theta_1, theta_2] x [phi_{2 j + 1}, phi_{2 j + 2}] */
    point[1] = (2 * j + 1.5) * phi_1;
    x[_index + 2] = factor * f(point);

    _index += 3;
  }
  *index = _index;
}

static void de_rham_2_of_faces_to_nodes_in_outer_circles(
  double * x, int * index,
  int na, int nd, double r_squared, double theta_1, double phi_1,
  double (*f)(const double *))
{
  int _index, i, j;
  double factor, theta_i0, theta_i1;
  double point[2];

  factor = r_squared * theta_1 * phi_1;

  _index = *index;
  for (i = 1; i < nd / 2; ++i)
  {
    theta_i0 = (2 * i + 0.5) * theta_1;
    theta_i1 = (2 * i + 1.5) * theta_1;
    for (j = 0; j < na / 2; ++j)
    {
      /* [theta_{2 i}, theta_{2 i + 1}] x [phi_{2 j}, phi_{2j + 1}] */
      point[0] = theta_i0;
      point[1] = (2 * j + 0.5) * phi_1;
      x[_index + 0] = factor * f(point);

      /* [theta_{2 i + 1}, theta_{2 i + 2}] x [phi_{2 j}, phi_{2j + 1}] */
      point[0] = theta_i1;
      x[_index + 1] = factor * f(point);

      /* [theta_{2 i + 1}, theta_{2 i + 2}] x [phi_{2 j + 1}, phi_{2j + 2}] */
      point[1] = (2 * j + 1.5) * phi_1;
      x[_index + 2] = factor * f(point);

      /* [theta_{2 i}, theta_{2 i + 1}] x [phi_{2 j + 1}, phi_{2j + 2}] */
      point[0] = theta_i0;
      x[_index + 3] = factor * f(point);
      
      _index += 4;
    }
  }
  *index = _index;
}

/* m is the Forman mesh of a polar mesh of a hemisphere */
void de_rham_2_hemisphere_polar_forman(
  double * x,
  const mesh * m,
  const double * m_vol_d,
  double (*f)(const double *))
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
    x, &index, na, r_squared, theta_1, phi_1, f);
  de_rham_2_of_faces_to_nodes_in_outer_circles(
    x, &index, na, nd, r_squared, theta_1, phi_1, f);
}
