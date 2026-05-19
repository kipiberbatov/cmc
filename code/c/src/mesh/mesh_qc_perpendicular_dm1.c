#include "int.h"
#include "mesh_qc.h"

void mesh_qc_perpendicular_dm1(
  int * nodes, int * nodes_opposite, int * perpendiculars,
  const int * cf_1_0_a2,
  int d_times_power_2_dm1, const int * cf_d_1_k_a1,
  int power_2_dm1, const int * cf_dm1_0_i_a1)
{
  int count, edge_j_0, edge_j_1, index, index_opposite, j, j_local;
  const int * edge_j;

  for (j_local = 0; j_local < d_times_power_2_dm1; ++j_local)
  {
    j = cf_d_1_k_a1[j_local];
    edge_j = cf_1_0_a2 + 2 * j;
    edge_j_0 = edge_j[0];
    edge_j_1 = edge_j[1];
    count = 0;
    if (int_array_member(power_2_dm1, cf_dm1_0_i_a1, edge_j_0))
    {
      ++count;
      index = edge_j_0;
      index_opposite = edge_j_1;
    }
    if (int_array_member(power_2_dm1, cf_dm1_0_i_a1, edge_j_1))
    {
      ++count;
      index = edge_j_1;
      index_opposite = edge_j_0;
    }
    if (count == 1)
    {
      *nodes = index;
      *nodes_opposite = index_opposite;
      *perpendiculars = j;
      ++nodes;
      ++nodes_opposite;
      ++perpendiculars;
    }
  }
}
