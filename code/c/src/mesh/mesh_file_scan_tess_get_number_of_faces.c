#include <errno.h>

#include "cmc_error_message.h"
#include "int.h"
#include "mesh_file_scan_tess_private.h"

int mesh_file_scan_tess_get_number_of_faces(FILE * in, int * status)
{
  int cn_2;

  cn_2 = int_file_scan(in);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan number of faces\n", stderr);
    *status = errno;
    return -1;
  }
  if (cn_2 <= 0)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "number of faces is %d which is not positive", cn_2);
    *status = 1;
    return -1;
  }
  return cn_2;
}
