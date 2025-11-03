#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "mesh.h"

matrix_sparse * mesh_qc_hodge_codifferential_p(
  int d, int p, const matrix_sparse * m_cbd_d_minus_p, matrix_sparse ** m_hodge)
{
  matrix_sparse * tmp, * m_hodge_codifferential_p;

  tmp = matrix_sparse_product(m_cbd_d_minus_p, m_hodge[p]);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot calculate delta_%d *_%d\n", d - p, p);
    matrix_sparse_free(tmp);
    return NULL;
  }

  m_hodge_codifferential_p = matrix_sparse_product(m_hodge[d - p + 1], tmp);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot calculate *_%d tmp\n", d - p + 1);
    matrix_sparse_free(m_hodge_codifferential_p);
    matrix_sparse_free(tmp);
    return NULL;
  }
  matrix_sparse_free(tmp);
  return m_hodge_codifferential_p;
}

matrix_sparse ** mesh_qc_hodge_codifferential(
  int d, const matrix_sparse * const * m_cbd, matrix_sparse ** m_hodge)
{
  int p;
  matrix_sparse ** m_hodge_codifferential;

  m_hodge_codifferential = (matrix_sparse **) malloc(
    sizeof(matrix_sparse *) * d);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(matrix_sparse *) * d,
                              "m_hodge_codifferential");
    return NULL;
  }
  for (p = 1; p <= d; ++p)
  {
    m_hodge_codifferential[p - 1] =
      mesh_qc_hodge_codifferential_p(d, p, m_cbd[d - p], m_hodge);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr,
        "cannot calculate *_%d delta_%d *_%d\n",
        d - p + 1, d - p, p);
      matrix_sparse_array_free(m_hodge_codifferential, d);
      return NULL;
    }
  }
  return m_hodge_codifferential;
}
