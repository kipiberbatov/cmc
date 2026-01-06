#include <string.h>

#include "mesh_private.h"

void mesh_cf_a4(
  int * cf_a4,
  int cn_1,
  int cn_2,
  int cfn_2_1_total,
  const int * cf_1_0,
  const int * cfn_2_1,
  const int * cf_2_1)
{
  int i, index, index_local, j, sides;

  memcpy(cf_a4, cf_1_0, sizeof(int) * 2 * cn_1);
  index = 2 * cn_1;
  index_local = 0;
  for (i = 0; i < cn_2; ++i)
  {
    sides = cfn_2_1[i];
    for (j = 0; j < sides; ++j)
    {
      cf_a4[index + j] = cf_2_1[index_local + j];
      cf_a4[cfn_2_1_total + index + j]
      = cf_2_1[index_local + sides + j];
    }
    index += sides;
    index_local += 2 * sides;
  }
}
