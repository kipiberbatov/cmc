#include <errno.h>
#include <string.h>

#include "cmc_error_message.h"
#include "mesh_and_boundary.h"

mesh_and_boundary * mesh_and_boundary_file_scan(FILE * in, const char * format)
{
  mesh_and_boundary * m;

  if (!strcmp(format, "tess"))
    m = mesh_and_boundary_file_scan_tess(in);
  else
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "format %s%s%s is not supported\n",
      color_variable, format, color_none);
    errno = EINVAL;
    return NULL;
  }
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan input in format %s%s%s\n",
      color_variable, format, color_none);
    return NULL;
  }
  return m;
}
