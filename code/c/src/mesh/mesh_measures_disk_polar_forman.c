#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "mesh.h"
#include "mesh_measures.h"

static void forman_lengths_of_edges_to_nodes(
  double * vol_1, int * index, int na, int nd, double r0, double a0)
{
  int _index, i;
  double a;

  _index = *index;
  for (i = 1; i <= nd / 2; ++i)
  {
    /* rays */
    double_array_assign_constant(vol_1 + _index, na, r0);
    _index += na;

    /* arcs */
    a = a0 * 2 * i;
    double_array_assign_constant(vol_1 + _index, na, a);
    _index += na;
  }
  *index = _index;
}

static void forman_lengths_of_faces_to_edges_in_inner_circle(
  double * vol_1, int * index, int na, double r0, double a0)
{
  int _index, j;

  _index = *index;
  for (j = 0; j < na / 2; ++j)
  {
    vol_1[_index + 0] = a0; /* arc */
    vol_1[_index + 1] = r0; /* ray */
    vol_1[_index + 2] = a0; /* arc */
    _index += 3;
  }
  *index = _index;
}

static void forman_lengths_of_faces_to_edges_in_outer_circles(
  double * vol_1, int * index, int na, int nd, double r0, double a0)
{
  int _index, i, j;
  double a;

  _index = *index;
  for (i = 1; i < nd / 2; ++i)
  {
    a = a0 * (2 * i + 1);
    for (j = 0; j < na / 2; ++j)
    {
      vol_1[_index + 0] = r0; /* ray */
      vol_1[_index + 1] = a;  /* arc */
      vol_1[_index + 2] = r0; /* ray */
      vol_1[_index + 3] = a;  /* arc */
      _index += 4;
    }
  }
  *index = _index;
}

static void forman_lengths_of_faces_to_edges(
  double * vol_1, int * index, int na, int nd, double r0, double a0)
{
  forman_lengths_of_faces_to_edges_in_inner_circle(vol_1, index, na, r0, a0);
  forman_lengths_of_faces_to_edges_in_outer_circles(
    vol_1, index, na, nd, r0, a0);
}

static void forman_lengths(double * vol_1, int na, int nd, double r0, double a0)
{
  int index = 0;
  forman_lengths_of_edges_to_nodes(vol_1, &index, na, nd, r0, a0);
  forman_lengths_of_faces_to_edges(vol_1, &index, na, nd, r0, a0);
}

static void forman_areas_of_faces_to_nodes_in_inner_circle(
  double * vol_2, int * index, int na, double s_0)
{
  int _index, j;
  double s_i0, s_i1;

  s_i0 = 2 * s_0;
  s_i1 = 3 * s_0;
  _index = *index;
  for (j = 0; j < na / 2; ++j)
  {
    vol_2[_index + 0] = s_i0;  /* (0, r0) */
    vol_2[_index + 1] = s_i1;  /* (r0, r1) */
    vol_2[_index + 2] = s_i1;  /* (r0, r1) */
    _index += 3;
  }
  *index = _index;
}

static void forman_areas_of_faces_to_nodes_in_outer_circles(
  double * vol_2, int * index, int na, int nd, double s_0)
{
  int _index, i, j;
  double s_i0, s_i1;

  _index = *index;
  for (i = 1; i < nd / 2; ++i)
  {
    s_i0 = (4 * i + 1) * s_0;
    s_i1 = (4 * i + 3) * s_0;
    for (j = 0; j < na / 2; ++j)
    {
      vol_2[_index + 0] = s_i0; /* (r[2 i + 0], r[2 i + 1]) */
      vol_2[_index + 1] = s_i1; /* (r[2 i + 1], r[2 i + 2]) */
      vol_2[_index + 2] = s_i1; /* (r[2 i + 0], r[2 i + 1]) */
      vol_2[_index + 3] = s_i0; /* (r[2 i + 1], r[2 i + 2]) */
      _index += 4;
    }
  }
  *index = _index;
}

static void forman_areas_of_faces_to_nodes(
  double * vol_2, int * index, int na, int nd, double s_0)
{
  forman_areas_of_faces_to_nodes_in_inner_circle(vol_2, index, na, s_0);
  forman_areas_of_faces_to_nodes_in_outer_circles(vol_2, index, na, nd, s_0);
}

static void forman_areas(double * vol_2, int na, int nd, double s_0)
{
  int index = 0;
  forman_areas_of_faces_to_nodes(vol_2, &index, na, nd, s_0);
}

/* m is the Forman mesh of a polar mesh */
void mesh_measures_disk_polar_forman(
  double *** m_measures, int * status, const struct mesh * m)
{
  int end_index, na, nd, p;
  int * m_cn;
  double a0, r, r0, rx, ry, s_0, theta;
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
  end_index = na * nd / 4;
  rx = m->coord[2 * end_index];
  ry = m->coord[2 * end_index + 1];
  r = sqrt(rx * rx + ry * ry);
  r0 = r / nd;
  theta = M_PI * 2 / na;
  a0 = r0 * theta;
  s_0 = r0 * r0 * theta / 2;

  double_array_assign_constant(vol[0], m_cn[0], 1.);
  forman_lengths(vol[1], na, nd, r0, a0);
  forman_areas(vol[2], na, nd, s_0);
}
