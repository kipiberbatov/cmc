#include <string.h>

#include "cmc_error_message.h"
#include "mesh_file_scan_tess_private.h"
#include "string_private.h"

int mesh_file_scan_tess_get_dimension(FILE * in, int * error)
{
  int d;
  char buffer[3];

  string_file_scan(in, buffer, 2);
  if (!strcmp(buffer, "1"))
    d = 1;
  else if (!strcmp(buffer, "2"))
    d = 2;
  else if (!strcmp(buffer, "3"))
    d = 3;
  else
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan dimension: it should be 1, 2, or 3\n", stderr);
    *error = 1;
    return -1;
  }
  return d;
}
