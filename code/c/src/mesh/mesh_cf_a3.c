#include "mesh_private.h"

void mesh_cf_a3(
  int * cf_a3,
  int cn_1,
  int cn_2,
  const int * cfn_2_1)
{
  int i, index, sides;

  for (i = 0; i < cn_1; ++i)
    cf_a3[i] = 2;
  index = cn_1;
  for (i = 0; i < cn_2; ++i)
  {
    sides = cfn_2_1[i];
    cf_a3[index] = sides;
    cf_a3[index + cn_2] = sides;
    ++index;
  }
}
