#include <errno.h>

#include "cmc_error_message.h"
#include "int.h"
#include "mesh_file_scan_tess_private.h"

int mesh_file_scan_tess_get_number_of_maximal_cells(FILE * in, int * status)
{
  int cn_d;

  cn_d = int_file_scan(in);
  *status = errno;
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("Cannot scan maximal dimension\n", stderr);
    return -1;
  }
  if (cn_d <= 0)
  {
    *status = EINVAL;
    fprintf(stderr,
      "Number of maximal cells is %d which is not positive", cn_d);
    return -1;
  }
  return cn_d;
}
