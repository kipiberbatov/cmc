#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "double_array2.h"
#include "mesh_qc.h"
#include "vector_sparse.h"

double * mesh_qc_inner_p(const mesh_qc * m, const double * m_vol_d,
                         int p, vector_sparse ** m_metric_p)
{
  int i, m_cn_p;
  double * m_inner_p;

  m_cn_p = m->cn[p];

  m_inner_p = (double *) malloc(sizeof(double) * m_cn_p);
  if (m_inner_p == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m_cn_p, "m_inner_p");
    return NULL;
  }

  for (i = 0; i < m_cn_p; ++i)
    m_inner_p[i] = mesh_qc_integrate(m, m_vol_d, m_metric_p[i]);

  return m_inner_p;
}

double ** mesh_qc_inner(
  const mesh_qc * m, const double * m_vol_d, vector_sparse *** m_metric)
{
  int m_dim, p;
  double ** m_inner;

  m_dim = m->dim;

  m_inner = (double **) malloc(sizeof(double *) * (m_dim + 1));
  if (m_inner == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * (m_dim + 1), "m_inner");
    return NULL;
  }

  for (p = 0; p <= m_dim; ++p)
  {
    m_inner[p] = mesh_qc_inner_p(m, m_vol_d, p, m_metric[p]);
    if (m_inner[p] == NULL)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot calculate m_inner[%s%d%s]\n",
        color_variable, p, color_none);
      double_array2_free(m_inner, p);
      return NULL;
    }
  }

  return m_inner;
}
