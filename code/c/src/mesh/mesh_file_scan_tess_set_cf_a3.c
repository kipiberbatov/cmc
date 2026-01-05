#include "mesh_file_scan_tess_private.h"

void mesh_file_scan_tess_set_cf_a3(
  int * cf_a3,
  int cn_1,
  int cn_2,
  const int * faces_number_of_sides)
{
  int i, index, sides;

  for (i = 0; i < cn_1; ++i)
    cf_a3[i] = 2;
  index = cn_1;
  for (i = 0; i < cn_2; ++i)
  {
    sides = faces_number_of_sides[i];
    cf_a3[index] = sides;
    cf_a3[index + cn_2] = sides;
    ++index;
  }
}
