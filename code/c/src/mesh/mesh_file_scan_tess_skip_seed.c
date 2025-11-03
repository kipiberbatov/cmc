#include <errno.h>

#include "cmc_error_message.h"
#include "double.h"
#include "int.h"
#include "mesh_file_scan_tess_private.h"

void mesh_file_scan_tess_skip_seed(FILE * in, int * error, int cn_d,
  const int * c)
{
  int c_i, i, j;

  for (i = 0; i < cn_d; ++i)
  {
    c_i = int_file_scan(in) - 1;
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot scan %d-th cell id dimension\n", i);
      *error = errno;
      return;
    }
    if (c_i != c[i])
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "id of cell[%d] does differs from data from seed",c_i);
      *error = 1;
      return;
    }
    for (j = 0; j < 4; ++j)
    {
      double_file_scan(in);
      if (errno)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fprintf(stderr, "missing value (%d, %d)\n", i, j);
        *error = errno;
        return;
      }
    }
  }
}
