#include <stdlib.h>

#include "cmc_error_message.h"
#include "mesh_qc.h"

static void
mesh_qc_matrix_sparse_from_inner_of_delta_basis_0_cup_kappa_1_delta_basis_0_cols_total(
  int * a_cols_total,
  const mesh_qc * m)
{
  int j, m_cn_0;
  jagged2 m_fc_0_1;

  m_cn_0 = m->cn[0];
  mesh_fc_part2(&m_fc_0_1, m, 0, 1);
  a_cols_total[0] = 0;
  for (j = 0; j < m_cn_0; ++j)
    a_cols_total[j + 1] = a_cols_total[j] + m_fc_0_1.a1[j] + 1;
}

static void
mesh_qc_matrix_sparse_from_inner_of_delta_basis_0_cup_kappa_1_delta_basis_0_row_indices(
  int * a_row_indices,
  const mesh_qc * m)
{
  int index, i, j, k, k_local, m_cn_0;
  int * m_fc_0_1_j;
  jagged1 m_cf_1_0_k;
  jagged2 m_cf_1_0, m_fc_0_1;

  m_cn_0 = m->cn[0];
  mesh_fc_part2(&m_fc_0_1, m, 0, 1);
  mesh_cf_part2(&m_cf_1_0, m, 1, 0);
  m_fc_0_1_j = m_fc_0_1.a2;

  index = 0;
  for (j = 0; j < m_cn_0; ++j)
  {
    a_row_indices[index] = j;
    ++index;
    for (k_local = 0; k_local < m_fc_0_1.a1[j]; ++k_local)
    {
      k = m_fc_0_1_j[k_local];
      jagged2_part1(&m_cf_1_0_k, &m_cf_1_0, k);
      i = jagged1_couple_other_object(&m_cf_1_0_k, j);
      a_row_indices[index] = i;
      ++index;
    }
    m_fc_0_1_j += m_fc_0_1.a1[j];
  }
}

static void
mesh_qc_matrix_sparse_from_inner_of_delta_basis_0_cup_kappa_1_delta_basis_0_values(
  double * a_values,
  const mesh_qc * m,
  const double * m_inner_1,
  const double * kappa_1)
{
  int diagonal_index, index, j, k, k_local, m_cn_0;
  int * m_fc_0_1_j;
  double c_k;
  jagged2 m_fc_0_1;

  m_cn_0 = m->cn[0];
  mesh_fc_part2(&m_fc_0_1, m, 0, 1);
  m_fc_0_1_j = m_fc_0_1.a2;

  index = 0;
  for (j = 0; j < m_cn_0; ++j)
  {
    diagonal_index = index;
    a_values[diagonal_index] = 0;
    ++index;
    for (k_local = 0; k_local < m_fc_0_1.a1[j]; ++k_local)
    {
      k = m_fc_0_1_j[k_local];
      c_k = kappa_1[k] * m_inner_1[k];
      a_values[index] = -c_k;
      a_values[diagonal_index] += c_k;
      ++index;
    }
    m_fc_0_1_j += m_fc_0_1.a1[j];
  }
}

/* calculate sparse matrix a, a_{i, j} := <delta N^j, kappa_1 (delta N^i)> */
matrix_sparse *
mesh_qc_matrix_sparse_from_inner_of_delta_basis_0_cup_kappa_1_delta_basis_0(
  const mesh_qc * m,
  const double * m_inner_1,
  const double * kappa_1)
{
  int nonzero_max;
  matrix_sparse * a;

  a = (matrix_sparse *) malloc(sizeof(matrix_sparse));
  if (a == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for a\n",
      sizeof(matrix_sparse));
    goto end;
  }

  a->rows = m->cn[0];
  a->cols = a->rows;

  a->cols_total = (int *) malloc(sizeof(int) * (a->cols + 1));
  if (a->cols_total == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for a->cols_total\n",
      sizeof(int) * (a->cols + 1));
    goto a_free;
  }
  mesh_qc_matrix_sparse_from_inner_of_delta_basis_0_cup_kappa_1_delta_basis_0_cols_total(
    a->cols_total, m);

  nonzero_max = a->cols_total[a->cols];

  a->row_indices = (int *) malloc(sizeof(int) * nonzero_max);
  if (a->row_indices == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for a->row_indices\n",
      sizeof(int) * nonzero_max);
    goto a_cols_total_free;
  }
  mesh_qc_matrix_sparse_from_inner_of_delta_basis_0_cup_kappa_1_delta_basis_0_row_indices(
    a->row_indices, m);

  a->values = (double *) malloc(sizeof(double) * nonzero_max);
  if (a->values == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for a->values\n",
      sizeof(double) * nonzero_max);
    goto a_row_indices_free;
  }
  mesh_qc_matrix_sparse_from_inner_of_delta_basis_0_cup_kappa_1_delta_basis_0_values(
    a->values, m, m_inner_1, kappa_1);

  return a;

  /* cleaning if an error occurs */
a_row_indices_free:
  free(a->row_indices);
a_cols_total_free:
  free(a->cols_total);
a_free:
  free(a);
end:
  return NULL;
}
