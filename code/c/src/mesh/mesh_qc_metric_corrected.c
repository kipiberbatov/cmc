#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "double.h"
#include "int.h"
#include "mesh_qc.h"

static vector_sparse * mesh_qc_metric_corrected_p_i(
  int m_cn_0, const jagged1 * m_c_p_i_nodes, int p, int i, double m_vol_p_i,
  const double * node_curvatures, const jagged2 * m_volumes)
{
  int j, j_loc;
  double denominator_p_i, node_curvature;
  vector_sparse * m_metric_p_i;
  jagged1 m_volumes_j;

  m_metric_p_i = (vector_sparse *) malloc(sizeof(vector_sparse));
  if (m_metric_p_i == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(vector_sparse), "m_metric_p_i");
    goto end;
  }

  m_metric_p_i->length = m_cn_0;
  m_metric_p_i->nonzero_max = m_c_p_i_nodes->a0;

  m_metric_p_i->positions =
    (int *) malloc(sizeof(int) * m_metric_p_i->nonzero_max);
  if (m_metric_p_i->positions == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(
      sizeof(int) * m_metric_p_i->nonzero_max, "m_metric_p_i->positions");
    goto m_metric_p_i_free;
  }
  memcpy(m_metric_p_i->positions, m_c_p_i_nodes->a1,
         sizeof(int) * m_metric_p_i->nonzero_max);

  m_metric_p_i->values =
    (double *) malloc(sizeof(double) * m_metric_p_i->nonzero_max);
  if (m_metric_p_i->values == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(
      sizeof(double) * m_metric_p_i->nonzero_max, "m_metric_p_i->values");
    goto m_metric_p_i_positions_free;
  }
  denominator_p_i = ((double) m_c_p_i_nodes->a0) * (m_vol_p_i * m_vol_p_i);
  for(j_loc = 0; j_loc < m_metric_p_i->nonzero_max; ++j_loc)
  {
    j = m_metric_p_i->positions[j_loc];
    jagged2_part1(&m_volumes_j, m_volumes, j);
    node_curvature = node_curvatures[j];
    m_metric_p_i->values[j_loc] = node_curvature / denominator_p_i;
  }

  vector_sparse_rearrange(m_metric_p_i);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "unable to rearrange m_metric_p_i\n");
    goto m_metric_p_i_values_free;
  }

  return m_metric_p_i;

  /* cleaning if an error occurs */
m_metric_p_i_values_free:
  free(m_metric_p_i->values);
m_metric_p_i_positions_free:
  free(m_metric_p_i->positions);
m_metric_p_i_free:
  free(m_metric_p_i);
end:
  return NULL;
}

vector_sparse ** mesh_qc_metric_corrected_p(
  const mesh_qc * m, int p, const double * m_vol_p,
  const double * node_curvatures)
{
  int i, m_cn_p;
  int * m_cn;
  jagged1 m_c_p_i_nodes;
  jagged2 m_volumes;
  vector_sparse ** m_metric_p;

  m_cn = m->cn;
  m_cn_p = m_cn[p];

  m_metric_p = (vector_sparse **) malloc(m_cn_p * sizeof(vector_sparse *));
  if (m_metric_p == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(m_cn_p * sizeof(vector_sparse *), "m_metric_p");
    return NULL;
  }

  mesh_fc_part2(&m_volumes, m, 0, m->dim);
  for (i = 0; i < m_cn_p; ++i)
  {
    mesh_cf_part3(&m_c_p_i_nodes, m, p, 0, i);
    m_metric_p[i] =
      mesh_qc_metric_corrected_p_i(m_cn[0], &m_c_p_i_nodes, p, i,
                                   m_vol_p[i], node_curvatures, &m_volumes);
    if (m_metric_p[i] == NULL)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr,
        "cannot calculate m_metric_p[%s%d%s]\n", color_variable, i, color_none);
      vector_sparse_array_free(m_metric_p, i);
      return NULL;
    }
  }

  return m_metric_p;
}

vector_sparse *** mesh_qc_metric_corrected(
  const mesh_qc * m, double ** m_vol, const double * node_curvatures)
{
  int m_dim, p;
  vector_sparse *** m_metric;

  m_dim = m->dim;

  m_metric = (vector_sparse ***) malloc(sizeof(vector_sparse **) * (m_dim + 1));
  if (m_metric == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(
      sizeof(vector_sparse **) * (m_dim + 1), "m_metric");
    return NULL;
  }

  for (p = 0; p <= m_dim; ++p)
  {
    m_metric[p] = mesh_qc_metric_corrected_p(m, p, m_vol[p], node_curvatures);
    if (m_metric[p] == NULL)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr,
        "cannot calculate m_metric[%s%d%s]\n", color_variable, p, color_none);
      vector_sparse_array2_free(m_metric, p, m->cn);
      return NULL;
    }
  }

  return m_metric;
}
