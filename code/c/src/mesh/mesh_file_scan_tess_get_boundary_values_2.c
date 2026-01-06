#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "double.h"
#include "int.h"
#include "mesh_file_scan_tess_private.h"

/* error is impossible there, as data is checked on the previous call */
void mesh_file_scan_tess_get_boundary_values_2(double * boundary_values_2,
  FILE * in, int * status, int cn_2, int cfn_2_1_total)
{
  int cfn_2_1_total_i, i, index, j, orientation_index;

  index = 0;
  for (i = 0; i < cn_2; ++i)
  {
    int_file_scan(in); /* c_i; */
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot scan integer for i = %d\n", i);
      *status = errno;
      return;
    }

    /* skip */
    cfn_2_1_total_i = int_file_scan(in);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot scan cfn_2_1_total[%d]\n", i);
      *status = errno;
      return;
    }
    if (cfn_2_1_total_i <= 2)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr,
        "cfn_2_1_total[%d] should be at least 3; instead it is %d\n",
        i, cfn_2_1_total_i);
      *status = 1;
      return;
    }
    for (j = 0; j < cfn_2_1_total_i; ++j)
    {
      int_file_scan(in);
      if (errno)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fprintf(stderr, "unable to skip garbage value[%d]\n", j);
        *status = errno;
        return;
      }
    }

    cfn_2_1_total_i = int_file_scan(in);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot scan cfn_2_1_total[%d]\n", i);
      *status = errno;
      return;
    }
    if (cfn_2_1_total_i <= 2)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr,
        "cfn_2_1_total[%d] should be at least 3; instead it is %d\n",
        i, cfn_2_1_total_i);
      *status = 1;
      return;
    }
    for (j = 0; j < cfn_2_1_total_i; ++j)
    {
      /* tess meshes come with clock-wise orientation */
      orientation_index = int_file_scan(in);
      if (errno)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fprintf(stderr, "cannot scan orientation index (%d\n, %d)", i, j);
        *status = errno;
        return;
      }
      boundary_values_2[index] = (orientation_index > 0 ? -1: 1);
      ++index;
    }

    /* skip */
    for (j = 0; j < 9; ++j)
    {
      double_file_scan(in);
      if (errno)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fprintf(stderr, "unable to skip garbage value[%d]\n", j);
        *status = errno;
        return;
      }
    }
  }
}
