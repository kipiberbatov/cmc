#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "double.h"
#include "int.h"
#include "mesh_file_scan_tess_private.h"

void mesh_file_scan_tess_get_cells_to_faces_3_2(
  int * cf_3_2, FILE * in, int * status, int cn_3, const int * cfn_3_2)
{
  int cfn_3_2_i, i, index, j, tmp;

  index = 0;
  for (i = 0; i < cn_3; ++i)
  {
    int_file_scan(in); /* c_i; */
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot scan integer for i = %d\n", i);
      *status = errno;
      return;
    }

    cfn_3_2_i = int_file_scan(in);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot scan cfn_3_2[%d]\n", i);
      *status = errno;
      return;
    }
    if (cfn_3_2_i != cfn_3_2[i])
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr,
        "cfn_3_2[%d] = %d but it should be equal to %d\n",
        i, cfn_3_2_i, cfn_3_2[i]);
      *status = 1;
      return;
    }
    for (j = 0; j < cfn_3_2_i; ++j)
    {
      tmp = int_file_scan(in);
      if (errno)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fprintf(stderr, "cannot scan cf_3_2[%d][%d]\n", i, j);
        *status = errno;
        return;
      }
      cf_3_2[index] = abs(tmp) - 1;
      ++index;
    }
  }
}
