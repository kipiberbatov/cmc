#include <stdlib.h>

#include "cmc_error_message.h"
#include "int.h"
#include "mesh_brick_private.h"
#include "mesh_private.h"

mesh * mesh_brick_topology(int d, const int * partitions)
{
  int m_c_size;
  mesh * m;

  m = (mesh *) malloc(sizeof(mesh));
  if (m == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(mesh), "m");
    goto end;
  }

  m->dim = d;

  m->cn = (int *) calloc((m->dim + 1), sizeof(int));
  if (m->cn == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(mesh), "m");
    goto m_free;
  }
  mesh_brick_cn(m->cn, m->dim, partitions);

  m_c_size = int_array_total_sum(m->dim + 1, m->cn);
  m->c = (int *) malloc(sizeof(int) * m_c_size);
  if (m->c == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(int) * m_c_size, "m->c");
    goto m_cn_free;
  }
  mesh_c(m->c, m->dim, m->cn);

  m->cf = mesh_brick_cf(m->dim, m->cn, partitions);
  if (m->cf == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m->cf\n", stderr);
    goto m_c_free;
  }

  m->fc = NULL;

  return m;

  /* cleaning if an error occurs */
m_c_free:
  free(m->c);
m_cn_free:
  free(m->cn);
m_free:
  free(m);
end:
  return NULL;
}
