#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "mesh_disk_polar.h"

mesh * mesh_disk_polar(int na, int nd, double radius, double x0, double y0)
{
  mesh * m;

  m = (mesh *) malloc(sizeof(mesh));
  if (m == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(mesh), "m");
    goto end;
  }

  mesh_disk_polar_only_topology(m, na, nd);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot calculate polar mesh topology for na = %d, nd = %d\n", na, nd);
    goto m_free;
  }

  m->dim_embedded = 2;
  m->coord = (double *) malloc(sizeof(double) * 2 * m->cn[0]);
  if (m->coord == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * 2 * m->cn[0], "m->coord");
    goto m_topology_free;
  }
  mesh_disk_polar_coordinates(m->coord, na, nd, radius, x0, y0);

  return m;

  /* cleaning if an error occurs */
m_topology_free:
  free(m->cf);
  free(m->c);
  free(m->cn);
m_free:
  free(m);
end:
  return NULL;
}
