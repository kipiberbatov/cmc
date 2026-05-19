#include "cmc_diffusion_discrete_primal_weak_a_advective_private.h"
#include "double_array.h"
#include "int.h"
#include "mesh_qc.h"


/*
  Notation for cells (in a quasi-cubical mesh K of dimension d):
    N -> nodes (0-cells)
    E -> edges (1-cells)
    H -> hyperfaces ((d - 1)-cells)
    C -> top-cells (d-cells)

  Indices of the cells in the loop
    j -> 0-cells, N_j in K_0
    k -> (d - 1)-cells, H_k > N_j
    l -> d-cells, C_l > H_k
    m -> 1-cells, (E_m, H_k) are perpendicular with respect to C_l
    i -> 0-cells, N_i = intersection(E_m, H_k)
    n -> 0-cells, N_n = E_m \ N_i

  Formulation
    Let
      K be an oriented quasi-cubical mesh,
      d be the dimension of K,
      tilde{pi}: C^0 K -> C^0 K be the dual capacity,
      v: C^{d - 1} K be the volumetric flow rate.
    Consider the bilinear form,
    representing the advective term in discrete primal weak formulations:
    A_advective: C^0 K * C^0 K -> R,
    A_advective(w, u) := A_advective(u)(w) := (delta_0 w \_/ (pi(u) \_/ v))[K].
    We are calculating its matrix
    a_advective in M_{cn[0] * cn[0]}(R)
    in the standard bases, that is,
    a_advective_{j, i} := (delta_0 N^i \_/ (pi(N^j) \_/ v))[K].

  Derivation
    For simplicity, denote a := a_advective and A := A_advective
    We calculate the coefficients a_{i, j} = a(N^j, N^i) of A, i.e.,
    A = sum_{i, j = 0, ..., cn[0] - 1} a_{i, j} N_i otimes N_j.
    a is a sparse matrix with a sparsity pattern as follows:
    the nonzero entries (i, j) are those
    for which N_i and N_j live in a commonon d-cell C_l.
    To derive the topology chasing for this sparse matrix
    we start with the nodes N_j (since our sparse matrices are column major)
    and proceed by expanding the definition of A.
    Before we do the calculation, we assume that
    pi(N^j) = pi_j N^j and
    v = sum_{k = 0}^{cn[d - 1] - 1} v_k H^k.
    Hence,
    A = sum_{N_j in K_0} sum_{N_i in K_0}
        (delta_0 N^i \_/ (pi(N^j) \_/ v))[K] N_i otimes N_j
      = sum_{N_j in K_0} sum_{N_i in K_0} sum_{H_k in K_{d - 1}}
        sum_{C_l in K_d} (delta_0 N^i \_/ (pi_j N^j \_/ v_k H^K))(C_l)
        N_i otimes N_j
      = sum_{N_j in K_0} pi_j (sum_{H_k in K_{d - 1}} v_k (sum_{C_l in K_d}
        sum_{N_i in K_0} (delta_0 N^i \_/ (N^j \_/ H^K))(C_l) N_i)) otimes N_j
      = 2^{1 - d} sum_{N_j in K_0} pi_j (sum_{H_k >= N_j} v_k (sum_{C_l in K_d}
        sum_{N_i in K_0} (delta_0 N^i \_/ H^k)(C_l) N_i)) otimes N_j
      = 2^{1 - d} sum_{N_j in K_0} pi_j (sum_{H_k >= N_j} v_k (sum_{C_l > H_k}
        sum_{N_i in K_0} (delta_0 N^i \_/ H^k)(C_l) N_i)) otimes N_j
      = 2^{1 - d} sum_{N_j in K_0} pi_j (sum_{H_k >= N_j} v_k (sum_{C_l > H_k}
        sum_{E_m _|_{C_l} H_k} sum_{N_i < E_m}
        epsilon(E_m, N_i) (E^m \_/ H^k)(C_l) N_i)) otimes N_j
      = 2^{1 - 2 d} sum_{N_j in K_0} pi_j (sum_{H_k >= N_j} v_k (sum_{C_l > H_k}
        sum_{E_m _|_{C_l} H_k} sum_{N_i < E_m}
        epsilon(E_m, N_i) epsilon^perpendicuar(C_l, E_m, H_k) N_i)) otimes N_j
      = 2^{1 - 2 d} sum_{N_j in K_0} pi_j (sum_{H_k >= N_j} v_k (sum_{C_l > H_k}
        sum_{E_m _|_{C_l} H_k} sum_{N_i < E_m}
        epsilon(E_m, N_i) epsilon(E_m, E_m /\ H_k) epsilon(C_l, H_k) N_i))
        otimes N_j
      = 2^{1 - 2 d} sum_{N_j in K_0} pi_j (sum_{H_k >= N_j} v_k (sum_{C_l > H_k}
        sum_{E_m _|_{C_l} H_k} sum_{N_i < E_m}
        epsilon(E_m, N_i) epsilon(E_m, intersection(E_m, H_k))
        epsilon(C_l, H_k) N_i))
        otimes N_j
      = 2^{1 - 2 d} sum_{N_j in K_0} pi_j (sum_{H_k >= N_j} v_k (sum_{C_l > H_k}
        sum_{E_m _|_{C_l} H_k} epsilon(C_l, H_k)
        intersection(E_m, H_k) - E_m \ intersection(E_m, H_k))) otimes N_j

  Pseudo-code
    a = 0 // as a sparse matrix
    for (N_j in K_0)
      for (H_k >= N_j)
        for (C_l > H_k)
          for (E_m _|_{C_l} H_k)
            N_i = intersection(E_m, H_k)
            N_n = E_m \ N_i
            a_{i, j} += 2^{1 - 2 d} pi_j v_k epsilon(C_l, H_k) 
            a_{n, j} -= 2^{1 - 2 d} pi_j v_k epsilon(C_l, H_k)
*/

void cmc_diffusion_discrete_primal_weak_a_advective_calculate(
  struct matrix_sparse * a_advective,
  const struct mesh * K,
  const struct matrix_sparse * cbd_dm1,
  const double * dual_capacity,
  const double * volumetric_flow_rate)
{
  int d = K->dim;
  int dm1 = d - 1;
  int power_2_dm1 = 1 << dm1;
  int denominator = 1 << (2 * d - 1);
  int d_times_power_2_dm1 = d * power_2_dm1;

  int cn_0 = K->cn[0];

  int * cbd_dm1_cols_total = cbd_dm1->cols_total;
  int * cbd_dm1_row_indices = cbd_dm1->row_indices;
  double * cbd_dm1_values = cbd_dm1->values;

  int * a_advective_cols_total = a_advective->cols_total;
  int * a_advective_row_indices = a_advective->row_indices;
  double * a_advective_values = a_advective->values;  

  int a_advective_cols_j, fc_0_dm1_j_a0, fc_dm1_d_k_a0;
  int i, i_local, j, k, k_local, l, l_local, m_local, n, n_local;
  int nodes[4], nodes_opposite[4], perpendiculars[4];
  int * a_advective_row_indices_j;
  int * fc_0_dm1_a1, * fc_0_dm1_j_a1, * fc_dm1_d_k_a1;
  int * cf_1_0_a2, * cf_dm1_0_a2, * cf_dm1_0_k_a1, * cf_d_1_a2, * cf_d_1_l_a1;
  double coefficient_k_l, cbd_dm1_values_k_l, volumetric_flow_rate_k;
  double * a_advective_values_j, * cbd_dm1_values_k;
  jagged2 cf_1_0, cf_dm1_0, cf_d_1, fc_0_dm1;

  mesh_cf_part2(&cf_1_0, K, 1, 0);
  cf_1_0_a2 = cf_1_0.a2;

  mesh_cf_part2(&cf_dm1_0, K, dm1, 0);
  cf_dm1_0_a2 = cf_dm1_0.a2;

  mesh_cf_part2(&cf_d_1, K, d, 1);
  cf_d_1_a2 = cf_d_1.a2;
  
  mesh_fc_part2(&fc_0_dm1, K, 0, dm1);
  fc_0_dm1_a1 = fc_0_dm1.a1;

  a_advective_cols_total[0] = 0;
  fc_0_dm1_j_a0 = 0;
  fc_0_dm1_j_a1 = fc_0_dm1.a2;
  for (j = 0; j < cn_0; ++j)
  {
    a_advective_row_indices_j =
      a_advective_row_indices + a_advective_cols_total[j];
    a_advective_values_j = a_advective_values + a_advective_cols_total[j];
    a_advective_cols_j = 0;
    fc_0_dm1_j_a0 = fc_0_dm1_a1[j];
    for (k_local = 0; k_local < fc_0_dm1_j_a0; ++k_local)
    {
      k = fc_0_dm1_j_a1[k_local];
      volumetric_flow_rate_k = volumetric_flow_rate[k];
      cbd_dm1_values_k = cbd_dm1_values + cbd_dm1_cols_total[k];
      cf_dm1_0_k_a1 = cf_dm1_0_a2 + power_2_dm1 * k;
      fc_dm1_d_k_a0 = cbd_dm1_cols_total[k + 1] - cbd_dm1_cols_total[k];
      fc_dm1_d_k_a1 = cbd_dm1_row_indices + cbd_dm1_cols_total[k];
      for (l_local = 0; l_local < fc_dm1_d_k_a0; ++l_local)
      {
        l = fc_dm1_d_k_a1[l_local];
        cbd_dm1_values_k_l = cbd_dm1_values_k[l_local];
        coefficient_k_l = volumetric_flow_rate_k * cbd_dm1_values_k_l;
        cf_d_1_l_a1 = cf_d_1_a2 + d_times_power_2_dm1 * l;
        mesh_qc_perpendicular_dm1(
          nodes, nodes_opposite, perpendiculars,
          cf_1_0_a2,
          d_times_power_2_dm1, cf_d_1_l_a1,
          power_2_dm1, cf_dm1_0_k_a1);
        for (m_local = 0; m_local < power_2_dm1; ++m_local)
        {
          i = nodes[m_local];
          i_local = int_array_member_index(
            a_advective_cols_j, a_advective_row_indices_j, i);
          if (i_local == -1)
          {
            a_advective_row_indices_j[a_advective_cols_j] = i;
            a_advective_values_j[a_advective_cols_j] = coefficient_k_l;
            ++a_advective_cols_j;
          }
          else
            a_advective_values_j[i_local] += coefficient_k_l;

          n = nodes_opposite[m_local];
          n_local = int_array_member_index(
            a_advective_cols_j, a_advective_row_indices_j, n);
          if (n_local == -1)
          {
            a_advective_row_indices_j[a_advective_cols_j] = n;
            a_advective_values_j[a_advective_cols_j] = coefficient_k_l;
            ++a_advective_cols_j;
          }
          else
            a_advective_values_j[n_local] -= coefficient_k_l;
        }
      }
    }
    double_array_multiply_with(
      a_advective_values_j, a_advective_cols_j, dual_capacity[j] / denominator);
    a_advective_cols_total[j + 1] = a_advective_cols_total[j] + a_advective_cols_j;
    fc_0_dm1_j_a1 += fc_0_dm1_j_a0;
  }
}
