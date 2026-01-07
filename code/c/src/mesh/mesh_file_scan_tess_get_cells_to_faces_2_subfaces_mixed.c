#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "double.h"
#include "int.h"
#include "mesh_file_scan_tess_private.h"

/* error is impossible there, as data is checked on the previous call */
void mesh_file_scan_tess_get_cells_to_faces_2_subfaces_mixed(
  int * cf_2_subfaces_mixed, FILE * in, int * status,
  int cn_2, int cfn_2_1_total)
{
  int cfn_2_1_total_i, i, index, j;

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
      cf_2_subfaces_mixed[index] = int_file_scan(in) - 1;
      if (errno)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fprintf(stderr, "cannot scan cf_2_subfaces[%d]\n", index);
        *status = errno;
        return;
      }
      ++index;
    }

    cfn_2_1_total_i = int_file_scan(in);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot scan cfn_2_1_total[%d]\n", i);
      *status = errno;
      return;
    }
    for (j = 0; j < cfn_2_1_total_i; ++j)
    {
      cf_2_subfaces_mixed[index] = abs(int_file_scan(in)) - 1;
      if (errno)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fprintf(stderr, "cannot scan cf_2_subfaces[%d]\n", index);
        *status = errno;
        return;
      }
      ++index;
    }

    mesh_file_scan_tess_skip_garbage_face_values(in, status, i);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot skip garbage values for cell %d\n", i);
      return;
    }
  }
}
