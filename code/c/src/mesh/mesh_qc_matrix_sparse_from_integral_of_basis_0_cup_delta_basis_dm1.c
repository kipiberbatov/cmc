#include <stdlib.h>

#include "mesh_qc.h"

/*
********************************* declaration **********************************
Let
  . d be a natural number,
  . M be an oriented quasi-cubical mesh of dimension d
    with fundamental class [M].
In the mixed formulation for diffusion we have the operator
B: C^{d - 1} M * C^0 M -> R,
B(r, w) := $(w \_/ delta_{d - 1} q)[M].
We are calculating its matrix
b in M_{cn[0] * cn_[d - 1]}(R)
in the standard bases, that is,
b_{i, j} := (N^j \_/ delta_{d - 1} c^{d - 1, i})[M].
          = sum_{c_{d, k} > c_{d - 1, i}}
              epsilon(c_{d, k}, c_{d - 1, i}) * (N^j \_/ c^{d, k})[M]
          = sum_{c_{d, k} > c_{d - 1, i} and c_{d, k} > N_j}
              epsilon(c_{d, k}, c_{d - 1, i}) / 2^d.

Note!!!
What follows is a wrong implementation.
Fortunately, it is not used anywhere.

********************************** definition **********************************
take a node N_j
  0 F_i is not a boundary of the 3-coboundary of N_j -> b_{i, j} = 0
  1 F_i is a boundary of the 3-coboundary of N_j
      0 N_j is not on the boundary of F_i: let V_k be the common volume
        -> b_{i, j} = 1 / 2^d epsilon(V_k, F_i)
      1 N_j is on the boundary of F_i
          0 F_i is interior -> b_{i, j} = 0
          1 F_i is boundary with coboundary V_k
            -> b_{i, j} = 1 / 2^d epsilon(V_k, F_i)
            which is always 1 / 2^d when d > 1 and orientation is positive

algorithm
  . take a cell N_j
  . count the number of cells F_i satisfying 1.0 or 1.1.1
    let F_i be on the boundary of the 3 coboundary of N_j. count it if
      . F_i is not on the coboundary of N_i
      . F_i is on the coboundary of N_j and F_i is a boundary cell
  . take the indices of those cells
  . calculate the values
    (more precisely, the signs epsilon(V_k, F_i) before 1 / 2^d)

alternative algorithm
  . take a cell c_{d - 1, i}
  . there are 2^d 0-cells that have nonzero contribution
    let F_i be on the boundary of the 3 coboundary of N_j. count it if
      . F_i is not on the coboundary of N_i
      . F_i is on the coboundary of N_j and F_i is a boundary cell
  . take the indices of those cells
  . calculate the values
    (more precisely, the signs epsilon(V_k, F_i) before 1 / 2^d)
*/

static void
mesh_qc_matrix_sparse_from_integral_of_basis_0_cup_delta_basis_dm1_cols_total(
  int * b_cols_total,
  const mesh_qc * m)
{
  int d, i, m_cn_dm1, pow_2_d;

  d = m->dim;
  pow_2_d = 1 << d;
  m_cn_dm1 = m->cn[d - 1];
  b_cols_total[0] = 0;
  for (i = 0; i < m_cn_dm1; ++i)
    b_cols_total[i + 1] = b_cols_total[i] + pow_2_d;
}

static void
mesh_qc_matrix_sparse_from_integral_of_basis_0_cup_delta_basis_dm1_row_indices(
  int * b_row_indices,
  const mesh_qc * m)
{
  int d, i, index, j, j_local, k, k_local, m_cn_dm1, pow_2_d;
  jagged1 m_cf_d_0_k, m_cf_dm1_0_i, m_fc_dm1_d_i;
  jagged2 m_cf_d_0, m_cf_dm1_0, m_fc_dm1_d;

  d = m->dim;
  pow_2_d = 1 << d;
  m_cn_dm1 = m->cn[d - 1];
  mesh_cf_part2(&m_cf_d_0, m, d, 0);
  mesh_cf_part2(&m_cf_dm1_0, m, d - 1, 0);
  mesh_fc_part2(&m_fc_dm1_d, m, d - 1, d);

  index = 0;
  for (i = 0; i < m_cn_dm1; ++i)
  {
    jagged2_part1(&m_fc_dm1_d_i, &m_fc_dm1_d, i);
    if (m_fc_dm1_d_i.a0 == 1) /* boundary hyperface */
    {
      k = m_fc_dm1_d_i.a1[0];
      jagged2_part1(&m_cf_d_0_k, &m_cf_d_0, k);
      for (j_local = 0; j_local < pow_2_d; ++j_local)
      {
        j = m_cf_d_0_k.a1[j_local];
        b_row_indices[index] = j;
        ++index;
      }
    }
    else /* interior hyperface */
    {
      jagged2_part1(&m_cf_dm1_0_i, &m_cf_dm1_0, i);
      for (k_local = 0; k_local < 2; ++k_local)
      {
        k = m_fc_dm1_d_i.a1[k_local];
        jagged2_part1(&m_cf_d_0_k, &m_cf_d_0, k);
        for (j_local = 0; j_local < pow_2_d; ++j_local)
        {
          j = m_cf_d_0_k.a1[j_local];
          if (!jagged1_member(&m_cf_dm1_0_i, j))
          {
            b_row_indices[index] = j;
            ++index;
          }
        }
      }
    }
  }
}

static void
mesh_qc_matrix_sparse_from_integral_of_basis_0_cup_delta_basis_dm1_values(
  double * b_values,
  const mesh_qc * m,
  const matrix_sparse * m_cbd_dm1)
{
  int d, i, index, j_local, k_local, m_cbd_dm1_columns_i, m_cn_dm1, pow_2_d,
      pow_2_dm1;
  int * m_cbd_dm1_cols_total;//, * m_cbd_dm1_row_indices;
  double sign_k_i, value_k_i;
  double * m_cbd_dm1_values, * m_cbd_dm1_values_i;
  jagged1 m_fc_dm1_d_i;
  jagged2 m_fc_dm1_d;

  d = m->dim;
  pow_2_dm1 = 1 << (d - 1);
  pow_2_d = 1 << d;
  m_cn_dm1 = m->cn[d - 1];
  mesh_fc_part2(&m_fc_dm1_d, m, d - 1, d);
  m_cbd_dm1_cols_total = m_cbd_dm1->cols_total;
  m_cbd_dm1_values = m_cbd_dm1->values;

  index = 0;
  for (i = 0; i < m_cn_dm1; ++i)
  {
    jagged2_part1(&m_fc_dm1_d_i, &m_fc_dm1_d, i);
    m_cbd_dm1_columns_i = m_cbd_dm1_cols_total[i];
    m_cbd_dm1_values_i = m_cbd_dm1_values + m_cbd_dm1_columns_i;
    if (m_fc_dm1_d_i.a0 == 1) /* boundary hyperface */
    {
      value_k_i = 1. / (double) pow_2_d;
      for (j_local = 0; j_local < pow_2_d; ++j_local)
        b_values[index + j_local] = value_k_i;
      index += pow_2_d;
    }
    else /* interior hyperface */
    {
      for (k_local = 0; k_local < 2; ++k_local)
      {
        sign_k_i = m_cbd_dm1_values_i[k_local];
        value_k_i = sign_k_i / (double) pow_2_d;
        for (j_local = 0; j_local < pow_2_dm1; ++j_local)
          b_values[index + j_local] = value_k_i;
        index += pow_2_dm1;
      }
    }
  }
}

matrix_sparse *
mesh_qc_matrix_sparse_from_integral_of_basis_0_cup_delta_basis_dm1(
  const mesh_qc * m,
  const matrix_sparse * m_cbd_dm1)
{
  int d, nonzero_max;
  int * m_cn;
  matrix_sparse * b;

  d = m->dim;
  m_cn = m->cn;

  b = (matrix_sparse *) malloc(sizeof(matrix_sparse));
  if (b == NULL)
  {
    fprintf(stderr,
      "%s:%d: cannot allocate memory for sparse mtrix b\n", __FILE__, __LINE__);
    goto end;
  }

  b->rows = m_cn[0];
  b->cols = m_cn[d - 1];

  b->cols_total = (int *) malloc(sizeof(int) * (b->cols + 1));
  if (b->cols_total == NULL)
  {
    fprintf(stderr,
      "%s:%d: cannot allocate memory for b->cols_total\n", __FILE__, __LINE__);
    goto b_free;
  }
  mesh_qc_matrix_sparse_from_integral_of_basis_0_cup_delta_basis_dm1_cols_total(
    b->cols_total, m);

  nonzero_max = b->cols_total[b->cols];

  b->row_indices = (int *) malloc(sizeof(int) * nonzero_max);
  if (b->row_indices == NULL)
  {
    fprintf(stderr,
      "%s:%d: cannot allocate memory for b->row_indices\n", __FILE__, __LINE__);
    goto b_cols_total_free;
  }
  mesh_qc_matrix_sparse_from_integral_of_basis_0_cup_delta_basis_dm1_row_indices(
    b->row_indices, m);

  b->values = (double *) malloc(sizeof(double) * nonzero_max);
  if (b->values == NULL)
  {
    fprintf(stderr,
      "%s:%d: cannot allocate memory for b->values\n", __FILE__, __LINE__);
    goto b_row_indices_free;
  }
  mesh_qc_matrix_sparse_from_integral_of_basis_0_cup_delta_basis_dm1_values(
    b->values, m, m_cbd_dm1);

  return b;

  /* cleaning if an error occurs */
b_row_indices_free:
  free(b->row_indices);
b_cols_total_free:
  free(b->cols_total);
b_free:
  free(b);
end:
  return NULL;
}
