#include <math.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "mesh.h"

/* finds the full unit angle in d dimensions (d = 0,1,2,3), i.e.,
 * the surface area of the unit (d - 1)-sphere (the boundary of the unit d-ball)
 */
static double angle_unit(int d)
{
  switch (d)
  {
  case 0:
    return 1.;
  case 1:
    return 1.;
  case 2:
    return (2 * M_PI);
  case 3:
    return (4 * M_PI);
  default:
    return 1.;
  }
}

/* finds the angle between two vectors in dimensions 2 or 3 */
static double angle_2d_general(int d, const double a0[3], const double a1[3])
{
  double dot;
  double v0[3], v1[3];

  double_array_normalize(v0, d, a0);
  double_array_normalize(v1, d, a1);
  dot = double_array_dot_product(d, v0, v1);
  return acos(dot);
}

/* finds the planar angle between the first two rows of a 3x3 matrix */
static double angle_2d(const double a[3][3])
{
  double dot;
  double v0[3], v1[3];

  double_array_normalize(v0, 2, a[0]);
  double_array_normalize(v1, 2, a[1]);
  dot = double_array_dot_product(2, v0, v1);
  return acos(dot);
}

#if 0
/* another method for finding solid angles */
static double determinant_3d(const double a[3][3])
{
  return a[0][0] * a[1][1] * a[2][2] - a[0][0] * a[1][2] * a[2][1]
       + a[1][0] * a[2][1] * a[0][2] - a[1][0] * a[0][1] * a[2][2]
       + a[2][0] * a[0][1] * a[1][2] - a[2][0] * a[1][1] * a[0][2];
}

static double angle_3d(const double a[3][3])
{
  double dot01, dot02, dot12, l0, l1, l2, triple;
  double numerator, denominator;

  dot01 = vector_dot(3, a[0], a[1]);
  dot02 = vector_dot(3, a[0], a[2]);
  dot12 = vector_dot(3, a[1], a[2]);
  l0 = vector_length(3, a[0]);
  l1 = vector_length(3, a[1]);
  l2 = vector_length(3, a[2]);
  triple = determinant_3d(a);
  numerator = fabs(triple);
  denominator = l0 * l1 * l2 + dot01 * l2 + dot02 * l1 + dot12 * l0;
  return 2 * atan(numerator / denominator);
}
#endif

/* finds the solid angle between 3 vectors, - the rows of a 3x3 matrix */
static double angle_3d(const double a[3][3])
{
  double fourth_tan_square, theta_s, theta01, theta02, theta12;

  theta01 = angle_2d_general(3, a[0], a[1]);
  theta02 = angle_2d_general(3, a[0], a[2]);
  theta12 = angle_2d_general(3, a[1], a[2]);
  theta_s = (theta01 + theta02 + theta12) / 2;
  fourth_tan_square =
      tan(theta_s / 2)
    * tan((theta_s - theta01) / 2)
    * tan((theta_s - theta02) / 2)
    * tan((theta_s - theta12) / 2);
  return 4 * atan(sqrt(fourth_tan_square));
}

/* constructs the edge vector at a point, needed for calculations of angles */
static void edge_vector(int * ind, double a[3][3], int d, const double * coord,
                        const jagged1 * arr, int i)
{
  if (arr->a1[0] == i)
  {
    double_array_difference(a[*ind], d, coord + d * arr->a1[1], coord + d * i);
    ++*ind;
  }
  else if (arr->a1[1] == i)
  {
    double_array_difference(a[*ind], d, coord + d * arr->a1[0], coord + d * i);
    ++*ind;
  }
}

/* finds the angle at a node with respect to one if its surrounding volumes
 * in dimension 2 or 3
 */
static double mesh_angle_nd(
  int d, const double * m_coord, const jagged2 * m_cf_1_0,
  const jagged1 * m_cf_d_1_k, int i)
{
  int ind, j, j_loc;
  double m_cf_d_1_k_coord[3][3];
  jagged1 m_cf_1_0_j;

  ind = 0;
  for (j_loc = 0; j_loc < m_cf_d_1_k->a0; ++j_loc)
  {
    j = m_cf_d_1_k->a1[j_loc];
    jagged2_part1(&m_cf_1_0_j, m_cf_1_0, j);
    edge_vector(&ind, m_cf_d_1_k_coord, d, m_coord, &m_cf_1_0_j, i);
  }
  return (d == 2) ? angle_2d(m_cf_d_1_k_coord) : angle_3d(m_cf_d_1_k_coord);
}

/* finds the angle at a node with respect to one if its surrounding volumes
 * in any dimension; it is better to use another function for d = 1
 */
static double mesh_angle(
  int d, const double * m_coord, const jagged2 * m_cf_1_0,
  const jagged1 * m_cf_d_1_k, int i)
{
  switch (d)
  {
  case 0:
    return 1.;
  case 1:
    return 0.5;
  case 2:
  case 3:
    return mesh_angle_nd(d, m_coord, m_cf_1_0, m_cf_d_1_k, i);
  default:
    return 1.;
  }
}

/* finds the total mesh curvature at a single node */
static double mesh_node_curvature_i(
  int d, const double * m_coord, const jagged2 * m_cf_1_0,
  const jagged2 * m_cf_d_1, const jagged2 * m_fc_0_d, int i)
{
  int k, k_loc;
  double node_total_angle;
  jagged1 m_cf_d_1_k, m_fc_0_d_i;

  jagged2_part1(&m_fc_0_d_i, m_fc_0_d, i);
  node_total_angle = 0;
  for (k_loc = 0; k_loc < m_fc_0_d_i.a0; ++k_loc)
  {
    k = m_fc_0_d_i.a1[k_loc];
    jagged2_part1(&m_cf_d_1_k, m_cf_d_1, k);
    node_total_angle += mesh_angle(d, m_coord, m_cf_1_0, &m_cf_d_1_k, i);
  }
  return angle_unit(d) / node_total_angle;
}

/* finds the total mesh curvatures at all nodes */
double * mesh_node_curvature(const mesh * m)
{
  int d, i, m_cn_0;
  double * m_node_curvatures;
  jagged2 m_cf_1_0, m_cf_d_1, m_fc_0_d;

  m_cn_0 = m->cn[0];
  d = m->dim;
  mesh_cf_part2(&m_cf_1_0, m, 1, 0);
  mesh_cf_part2(&m_cf_d_1, m, d, 1);
  mesh_fc_part2(&m_fc_0_d, m, 0, d);

  m_node_curvatures = (double *) malloc(sizeof(double) * m_cn_0);
  if (m_node_curvatures == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytes of memory for m_node_curvatures\n",
      sizeof(double) * m_cn_0);
    return NULL;
  }
  for (i = 0; i < m_cn_0; ++i)
    m_node_curvatures[i] =
      mesh_node_curvature_i(d, m->coord, &m_cf_1_0, &m_cf_d_1, &m_fc_0_d, i);

  return m_node_curvatures;
}
