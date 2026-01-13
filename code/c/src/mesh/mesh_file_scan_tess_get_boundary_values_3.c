#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "double.h"
#include "int.h"
#include "mesh_file_scan_tess_private.h"

/* error is impossible there, as data is checked on the previous call */
void mesh_file_scan_tess_get_boundary_values_3(double * boundary_values_3,
  FILE * in, int cn_3)
{
  int cfn_3_2_total_i, i, index, j, orientation_index;

  index = 0;
  for (i = 0; i < cn_3; ++i)
  {
    int_file_scan(in); /* skip c_3_i; */
    cfn_3_2_total_i = int_file_scan(in);
    for (j = 0; j < cfn_3_2_total_i; ++j)
    {
      orientation_index = int_file_scan(in);
      boundary_values_3[index] = (orientation_index > 0 ? 1: -1);
      ++index;
    }
  }
}
