#include <errno.h>

#include "cmc_error_message.h"
#include "double.h"
#include "mesh_file_scan_tess_private.h"

void mesh_file_scan_tess_skip_garbage_face_values(FILE * in, int * status,
  int i)
{
  int j;

  for (j = 0; j < 9; ++j)
  {
    double_file_scan(in);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "missing value, (i, j) = (%d, %d)\n", i, j);
      *status = errno;
      return;
    }
  }
}
