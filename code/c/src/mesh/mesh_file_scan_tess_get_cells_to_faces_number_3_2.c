#include <errno.h>

#include "cmc_error_message.h"
#include "double.h"
#include "int.h"
#include "mesh_file_scan_tess_private.h"

void mesh_file_scan_tess_get_cells_to_faces_number_3_2(
  int * cfn_3_2, FILE * in, int * status, int cn_3)
{
  int c_i, i;

  for (i = 0; i < cn_3; ++i)
  {
    c_i = int_file_scan(in);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot scan %d-th 3-cell id\n", i);
      *status = errno;
      return;
    }
    if (c_i != (i + 1))
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "invalid edge index: %d != %d\n", c_i, i + 1);
      *status = 1;
      return;
    }

    cfn_3_2[i] = int_file_scan(in);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot scan %d-th 3-cell number of sides\n", i);
      *status = errno;
      return;
    }
    if (cfn_3_2[i] < 4)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr,
        " i = %d, number of sides must be at least 4; instead it is %d\n",
        i, cfn_3_2[i]);
      *status = 1;
      return;
    }

    mesh_file_scan_tess_skip_int_array(in, status, cfn_3_2[i]);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot skip cf_3_2_%d\n", i);
      return;
    }
  }
}
