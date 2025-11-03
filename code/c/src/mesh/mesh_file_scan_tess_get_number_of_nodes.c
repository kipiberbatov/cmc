#include <errno.h>

#include "cmc_error_message.h"
#include "int.h"
#include "mesh_file_scan_tess_private.h"

int mesh_file_scan_tess_get_number_of_nodes(FILE * in, int * error)
{
  int cn_0;

  cn_0 = int_file_scan(in);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan number of nodes\n", stderr);
    *error = errno;
    return -1;
  }
  if (cn_0 <= 0)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "number of vertices is %d which is not positive", cn_0);
    *error = 1;
    return -1;
  }
  return cn_0;
}
