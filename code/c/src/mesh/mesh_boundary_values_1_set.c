#include "mesh_private.h"

void mesh_boundary_values_1_set(double * bd_1_values, int cn_1)
{
  int i;

  for (i = 0; i < cn_1; ++i)
  {
    bd_1_values[2 * i] = -1;
    bd_1_values[2 * i + 1] = 1;
  }
}
