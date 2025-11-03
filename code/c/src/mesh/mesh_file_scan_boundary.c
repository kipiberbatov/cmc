#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "mesh.h"

static void mesh_boundary_p_cols_total(
  int * m_bd_p_cols_total, int m_bd_p_cols, const int * m_cfn_p_q_a1)
{
  int i;

  m_bd_p_cols_total[0] = 0;
  for (i = 0; i < m_bd_p_cols; ++i)
    m_bd_p_cols_total[i + 1] = m_bd_p_cols_total[i] + m_cfn_p_q_a1[i];
}

matrix_sparse * mesh_file_scan_boundary_p(FILE * in, const mesh * m, int p)
{
  int m_bd_p_nonzero_max;
  jagged1 m_cfn_p_q; /* q = p - 1 */
  jagged2 m_cf_p_q; /* q = p - 1 */
  matrix_sparse * m_bd_p;

  mesh_cfn_part2(&m_cfn_p_q, m, p, p - 1);
  mesh_cf_part2(&m_cf_p_q, m, p, p - 1);

  m_bd_p = (matrix_sparse *) malloc(sizeof(matrix_sparse));
  if (m_bd_p == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytes of memory for m->bd[%d]\n",
      sizeof(matrix_sparse), p);
    goto end;
  }

  m_bd_p->rows = m->cn[p - 1];
  m_bd_p->cols = m->cn[p];

  m_bd_p->cols_total = (int *) malloc(sizeof(int) * (m_bd_p->cols + 1));
  if (m_bd_p->cols_total == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytes of memory for m->bd[%d]->cols_total\n",
      sizeof(int) * (m_bd_p->cols + 1), p);
    goto m_bd_p_free;
  }
  mesh_boundary_p_cols_total(m_bd_p->cols_total, m_bd_p->cols, m_cfn_p_q.a1);

  m_bd_p_nonzero_max = m_bd_p->cols_total[m_bd_p->cols];

  m_bd_p->row_indices = (int *) malloc(sizeof(int) * m_bd_p_nonzero_max);
  if (m_bd_p->row_indices == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytes of memory for m->bd[%d]->row_indices\n",
      sizeof(int) * m_bd_p_nonzero_max, p);
    goto m_bd_p_cols_total_free;
  }
  memcpy(m_bd_p->row_indices, m_cf_p_q.a2, sizeof(int) * m_bd_p_nonzero_max);

  m_bd_p->values = double_array_file_scan(in, m_bd_p_nonzero_max, "--raw");
  if (m_bd_p->values == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan m->bd[%d]->values in format --raw\n", p);
    goto m_bd_p_row_indices_free;
  }

  return m_bd_p;

  /* cleaning if an error occurs */
m_bd_p_row_indices_free:
  free(m_bd_p->row_indices);
m_bd_p_cols_total_free:
  free(m_bd_p->cols_total);
m_bd_p_free:
  free(m_bd_p);
end:
  return NULL;
}

matrix_sparse ** mesh_file_scan_boundary(FILE * in, const mesh * m)
{
  int m_dim, p;
  matrix_sparse ** m_bd;

  m_dim = m->dim;

  m_bd = (matrix_sparse **) malloc(sizeof(matrix_sparse *) * m_dim);
  if (m_bd == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytes of memory for m_bd\n",
      sizeof(matrix_sparse *) * m_dim);
    return NULL;
  }

  for (p = 1; p <= m_dim; ++p)
  {
    m_bd[p - 1] = mesh_file_scan_boundary_p(in, m, p);
    if (m_bd[p - 1] == NULL)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot scan m_bd[%d]\n", p - 1);
      matrix_sparse_array_free(m_bd, p - 1);
      return NULL;
    }
  }

  return m_bd;
}
