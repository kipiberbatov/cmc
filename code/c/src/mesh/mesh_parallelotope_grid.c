#include <stdlib.h>

#include "cmc_error_message.h"
#include "mesh_brick.h"
#include "mesh_parallelotope_grid.h"

mesh * mesh_parallelotope_grid(
  int d,
  int n,
  const double * origin,
  const double * directions,
  const int * partitions)
{
  mesh * m;

  m = mesh_brick_topology(d, partitions);
  if (m == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m\n", stderr);
    goto end;
  }

  m->dim_embedded = n;
  m->coord = (double *) malloc(sizeof(double) * n * m->cn[0]);
  if (m->coord == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * n * m->cn[0], "m->coord");
    goto m_free;
  }
  mesh_parallelotope_grid_coordinates(
    m->coord, d, n, origin, directions, partitions);

  return m;

  /* cleaning if an error occurs */
m_free:
  free(m);
end:
  return NULL;
}
