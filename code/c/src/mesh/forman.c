#include <stdlib.h>

#include "cmc_error_message.h"
#include "color.h"
#include "forman_private.h"
#include "int.h"
#include "mesh_private.h"

mesh * forman(const mesh * m, const char * new_coordinates_format)
{
  int m_forman_c_size, m_forman_coord_size;
  mesh * m_forman;

  m_forman = (mesh *) malloc(sizeof(mesh));
  if (m_forman == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(mesh), "m_forman");
    goto end;
  }

  m_forman->dim_embedded = m->dim_embedded;
  m_forman->dim = m->dim;

  m_forman->cn = (int *) calloc((m->dim + 1), sizeof(int));
  if (m_forman->cn == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(int) * (m->dim + 1), "m_forman->cn");
    goto m_forman_free;
  }
  forman_cn(m_forman->cn, m);

  m_forman_c_size = int_array_total_sum(m->dim + 1, m_forman->cn);
  m_forman->c = (int *) malloc(sizeof(int) * m_forman_c_size);
  if (m_forman->c == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(int) * m_forman_c_size, "m_forman->c");
    goto m_forman_cn_free;
  }
  mesh_c(m_forman->c, m->dim, m_forman->cn);

  m_forman->cf = forman_cf(m, m_forman->cn);
  if (m_forman->cf == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    cmc_error_message_cannot_calculate("m_forman->cf");
    goto m_forman_c_free;
  }

  m_forman->fc = NULL;

  m_forman_coord_size = m->dim_embedded * m_forman->cn[0];
  m_forman->coord = (double *) calloc(m_forman_coord_size, sizeof(double));
  if (m_forman->coord == NULL)
  {
    color_error_position(__FILE__, __LINE__);
    cmc_error_message_malloc(
      sizeof(double) * m_forman_coord_size, "m_forman->coord");
    goto m_forman_cf_free;
  }
  forman_coordinates(m_forman->coord, m, new_coordinates_format);

  return m_forman;

  /* cleaning if an error occurs */
m_forman_cf_free:
  free(m_forman->cf);
m_forman_c_free:
  free(m_forman->c);
m_forman_cn_free:
  free(m_forman->cn);
m_forman_free:
  free(m_forman);
end:
  return NULL;
}
