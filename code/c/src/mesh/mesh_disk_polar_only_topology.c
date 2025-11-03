#include <stdlib.h>

#include "cmc_error_message.h"
#include "int.h"
#include "mesh_disk_polar.h"
#include "mesh_private.h"

static void mesh_disk_polar_cells_number(int * m_cn, int na, int nd)
{
  int product = na * nd;
  m_cn[0] = product + 1;
  m_cn[1] = 2 * product;
  m_cn[2] = product;
}

void mesh_disk_polar_only_topology(mesh * m, int na, int nd)
{
  int m_c_size;

  m->dim = 2;

  m->cn = (int *) malloc(sizeof(int) * 3);
  if (m->cn == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(int) * 3, "m->cn");
    goto end;
  }
  mesh_disk_polar_cells_number(m->cn, na, nd);

  m_c_size = int_array_total_sum(3, m->cn);
  m->c = (int *) malloc(sizeof(int) * m_c_size);
  if (m->c == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(int) * m_c_size, "m->c");
    goto m_cn_free;
  }
  mesh_c(m->c, 2, m->cn);

  m->cf = mesh_disk_polar_cells_to_faces(na, nd, m->cn);
  if (m->cf == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m->cf\n", stderr);
    goto m_c_free;
  }

  m->fc = NULL;
  return;

  /* cleaning if an error occurs */
m_c_free:
  free(m->c);
m_cn_free:
  free(m->cn);
end:
  return;
}
