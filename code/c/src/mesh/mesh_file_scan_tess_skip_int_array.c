#include <errno.h>

#include "cmc_error_message.h"
#include "int.h"
#include "mesh_file_scan_tess_private.h"

void mesh_file_scan_tess_skip_int_array(FILE * in, int * status, int n)
{
  int j;

  for (j = 0; j < n; ++j)
  {
    int_file_scan(in);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot scan value with index %d\n", j);
      *status = errno;
      return;
    }
  }
}
