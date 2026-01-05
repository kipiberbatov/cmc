#include <errno.h>

#include "cmc_error_message.h"
#include "cmc_memory.h"
#include "mesh_and_boundary.h"
#include "mesh_file_scan_tess_private.h"

#define WITHOUT_BOUNDARY 0
mesh * mesh_file_scan_tess(FILE * in)
{
  int status = 0;
  mesh * m = NULL;
  mesh_and_boundary * m_and_bd = NULL;

  mesh_file_scan_tess_with_options(&m_and_bd, in, &status, WITHOUT_BOUNDARY);
  if (status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan m_and_bd\n", stderr);
    goto end;
  }
end:
  errno = status;
  if (!status)
  {
    m = m_and_bd->_mesh;
    cmc_memory_free(m_and_bd);
  }
  return m;
}
