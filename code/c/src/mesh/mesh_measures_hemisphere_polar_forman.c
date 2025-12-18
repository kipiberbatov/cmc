#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "mesh.h"
#include "mesh_measures.h"

static void forman_lengths_of_edges_to_nodes(
  double * vol_1, int * index, int na, int nd,
  double r_times_theta, double r_times_phi, double theta)
{
  int _index, i;
  double parallel_arc_length;

  _index = *index;
  for (i = 1; i <= nd / 2; ++i)
  {
    /* meridians */
    double_array_assign_constant(vol_1 + _index, na, r_times_theta);
    _index += na;

    /* parallels */
    parallel_arc_length = r_times_phi * sin(theta * 2 * i);
    double_array_assign_constant(vol_1 + _index, na, parallel_arc_length);
    _index += na;
  }
  *index = _index;
}

static void forman_lengths_of_faces_to_edges_in_inner_circle(
  double * vol_1, int * index, int na,
  double r_times_theta, double r_times_phi, double theta)
{
  int _index, j;
  double parallel_arc_length;

  parallel_arc_length = r_times_phi * sin(theta);
  _index = *index;
  for (j = 0; j < na / 2; ++j)
  {
    vol_1[_index + 0] = parallel_arc_length; /* parallel */
    vol_1[_index + 1] = r_times_theta;       /* meridian */
    vol_1[_index + 2] = parallel_arc_length; /* parallel */
    _index += 3;
  }
  *index = _index;
}

static void forman_lengths_of_faces_to_edges_in_outer_circles(
  double * vol_1, int * index, int na, int nd,
  double r_times_theta, double r_times_phi, double theta)
{
  int _index, i, j;
  double parallel_arc_length;

  _index = *index;
  for (i = 1; i < nd / 2; ++i)
  {
    parallel_arc_length = r_times_phi * sin(theta * (2 * i + 1));
    for (j = 0; j < na / 2; ++j)
    {
      vol_1[_index + 0] = r_times_theta;       /* meridian */
      vol_1[_index + 1] = parallel_arc_length; /* parallel */
      vol_1[_index + 2] = r_times_theta;       /* meridian */
      vol_1[_index + 3] = parallel_arc_length; /* parallel */
      _index += 4;
    }
  }
  *index = _index;
}

static void forman_lengths_of_faces_to_edges(
  double * vol_1, int * index, int na, int nd,
  double r_times_theta, double r_times_phi, double theta)
{
  forman_lengths_of_faces_to_edges_in_inner_circle(
    vol_1, index, na, r_times_theta, r_times_phi, theta);
  forman_lengths_of_faces_to_edges_in_outer_circles(
    vol_1, index, na, nd, r_times_theta, r_times_phi, theta);
}

static void forman_lengths(
  double * vol_1, int na, int nd,
  double r_times_theta, double r_times_phi, double theta)
{
  int index = 0;
  forman_lengths_of_edges_to_nodes(
    vol_1, &index, na, nd, r_times_theta, r_times_phi, theta);
  forman_lengths_of_faces_to_edges(
    vol_1, &index, na, nd, r_times_theta, r_times_phi, theta);
}

static void forman_areas_of_faces_to_nodes_in_inner_circle(
  double * vol_2, int * index, int na, double r_squred_times_phi, double theta)
{
  int _index, j;
  double s_i0, s_i1;

  _index = *index;
  s_i0 = 2 * r_squred_times_phi * (1 - cos(theta));
  s_i1 = r_squred_times_phi * (cos(theta) - cos(2 * theta));
  for (j = 0; j < na / 2; ++j)
  {
    vol_2[_index + 0] = s_i0;  /* [0, theta]       */
    vol_2[_index + 1] = s_i1;  /* [theta, 2 theta] */
    vol_2[_index + 2] = s_i1;  /* [theta, 2 theta] */
    _index += 3;
  }
  *index = _index;
}

static void forman_areas_of_faces_to_nodes_in_outer_circles(
  double * vol_2, int * index, int na, int nd,
  double r_squred_times_phi, double theta)
{
  int _index, i, j;
  double d_i0, d_i1, s_i0, s_i1;

  _index = *index;
  for (i = 1; i < nd / 2; ++i)
  {
    d_i0 = cos((2 * i + 0) * theta) - cos((2 * i + 1) * theta);
    d_i1 = cos((2 * i + 1) * theta) - cos((2 * i + 2) * theta);
    s_i0 = r_squred_times_phi * d_i0;
    s_i1 = r_squred_times_phi * d_i1;
    for (j = 0; j < na / 2; ++j)
    {
      vol_2[_index + 0] = s_i0; /* [(2 i + 0) theta, (2 i + 1) theta] */
      vol_2[_index + 1] = s_i1; /* [(2 i + 1) theta, (2 i + 2) theta] */
      vol_2[_index + 2] = s_i1; /* [(2 i + 1) theta, (2 i + 2) theta] */
      vol_2[_index + 3] = s_i0; /* [(2 i + 0) theta, (2 i + 1) theta] */
      _index += 4;
    }
  }
  *index = _index;
}

static void forman_areas_of_faces_to_nodes(
  double * vol_2, int * index, int na, int nd,
  double r_squred_times_phi, double theta)
{
  forman_areas_of_faces_to_nodes_in_inner_circle(
    vol_2, index, na, r_squred_times_phi, theta);
  forman_areas_of_faces_to_nodes_in_outer_circles(
    vol_2, index, na, nd, r_squred_times_phi, theta);
}

static void forman_areas(
  double * vol_2, int na, int nd,
  double r_squred_times_phi, double theta)
{
  int index = 0;
  forman_areas_of_faces_to_nodes(
    vol_2, &index, na, nd, r_squred_times_phi, theta);
}

/* m is the Forman mesh of a polar mesh of a hemisphere */
void mesh_measures_hemisphere_polar_forman(
  double *** m_measures, int * status, const struct mesh * m)
{
  int end_index, na, nd, p;
  int * m_cn;
  double phi, r, rx, ry, theta;
  double ** vol;

  *m_measures = (double **) malloc(sizeof(double *) * 3);
  if (*m_measures == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double *) * 3, "*m_measures");
    *status = 1;
    return;
  }

  m_cn = m->cn;
  vol = *m_measures;
  for (p = 0; p <= 2; ++p)
  {
    vol[p] = (double *) malloc(sizeof(double) * m_cn[p]);
    if (vol[p] == NULL)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr,
        "cannot allocate %s%zu%s bytes of memory for %s%s[%d]%s\n",
         color_variable, sizeof(double) * m_cn[p], color_none,
         color_variable, "vol", p, color_none);
      *status = 1;
      return;
    }
  }

  na = 2 * (2 * m_cn[0] - m_cn[1] - 2);
  nd = (m_cn[0] - 1) / na;
  theta = (M_PI / 2) / nd;
  phi = M_PI * 2 / na;
  end_index = na * nd / 4;
  rx = m->coord[3 * end_index + 0] - m->coord[0];
  ry = m->coord[3 * end_index + 1] - m->coord[1];
  r = sqrt(rx * rx + ry * ry);

  double_array_assign_constant(vol[0], m_cn[0], 1.);
  forman_lengths(vol[1], na, nd, r * theta, r * phi, theta);
  forman_areas(vol[2], na, nd, r * r * phi, theta);
}
