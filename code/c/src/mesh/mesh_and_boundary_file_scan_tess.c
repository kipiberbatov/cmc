#include <errno.h>

#include "cmc_error_message.h"
#include "mesh_and_boundary.h"
#include "mesh_file_scan_tess_private.h"

#define WITH_BOUNDARY 1
mesh_and_boundary * mesh_and_boundary_file_scan_tess(FILE * in)
{
  int status = 0;
  mesh_and_boundary * m_and_bd = NULL;

  mesh_file_scan_tess_with_options(&m_and_bd, in, &status, WITH_BOUNDARY);
  if (status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan m_and_bd\n", stderr);
    goto end;
  }
end:
  errno = status;
  return m_and_bd;
}
