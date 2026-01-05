#include "mesh_file_scan_tess_private.h"

void mesh_file_scan_tess_set_boundary_values_1(double * bd_1_values, int cn_1)
{
  int i;

  for (i = 0; i < cn_1; ++i)
  {
    bd_1_values[2 * i] = -1;
    bd_1_values[2 * i + 1] = 1;
  }
}
