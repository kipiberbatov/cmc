#include "mesh_private.h"

void mesh_cf_a4_2_set(
  int * cf_a4_2,
  int cn_2,
  int cfn_2_1_total,
  const int * cfn_2_1,
  const int * cf_2_subfaces_mixed)
{
  int i, index, index_local, j, sides;

  index = 0;
  index_local = 0;
  for (i = 0; i < cn_2; ++i)
  {
    sides = cfn_2_1[i];
    for (j = 0; j < sides; ++j)
    {
      cf_a4_2[index + j] = cf_2_subfaces_mixed[index_local + j];
      cf_a4_2[cfn_2_1_total + index + j]
      = cf_2_subfaces_mixed[index_local + sides + j];
    }
    index += sides;
    index_local += 2 * sides;
  }
}
