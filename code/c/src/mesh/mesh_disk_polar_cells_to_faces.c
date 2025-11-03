#include <stdlib.h>

#include "cmc_error_message.h"
#include "int.h"
#include "mesh_disk_polar.h"
#include "mesh_private.h"

/*
(1, 0) -> 2 ($2 * na * nd$ times)
(2, 0) -> 3 ($na$ times), 4 ($na * (nd - 1)$ times)
(2, 1) -> 3 ($na$ times), 4 ($na * (nd - 1)$ times)
*/
static void mesh_disk_polar_cells_to_faces_a3(int * m_cf_a3, int na, int nd)
{
  int index;

  int_array_assign_constant(m_cf_a3, 2 * na * nd, 2);
  index = 2 * na * nd;

  int_array_assign_constant(m_cf_a3 + index, na, 3);
  index += na;

  int_array_assign_constant(m_cf_a3 + index, na * (nd - 1), 4);
  index += na * (nd - 1);

  int_array_assign_constant(m_cf_a3 + index, na, 3);
  index += na;

  int_array_assign_constant(m_cf_a3 + index, na * (nd - 1), 4);
}

/*
(1, 0):
  j = 0 : na - 1
    j -> (0, j + 1)

  j = 0 : na - 2
    na + j -> (j + 1, j + 2)
  2 * na - 1 -> (na, 1)

  i = 1 : nd - 1
    j = 1 : na
      2 * i * na + j  -> (na * (i - 1) + j, na * i + j)

    j = 1 : na - 1
      (2 * i + 1) * na + j -> (na * i + j, na * i + j + 1)
    2 * (i + 1) * na - 1 -> (na * (i + 1), na * i + 1)

(2, 0):
  j = 0 : na - 2
    j -> (0, j + 1, j + 2)
  na - 1 -> (0, na, 1)

  i = 1 : nd - 1
    j = 0 : na - 2
      na * i + j -> (1, na + 1, na + 2, 2) + j + (i - 1) * na
    na * (i + 1) - 1 -> (2 * na, na + 1, 1, na) + (i - 1) * na

(2, 1):
  j = 0 : na - 2
    j -> (j, j + na, j + 1)
  na - 1 -> (na - 1, 2 * na - 1, 0)

  i = 1 : nd - 1
    j = 0 : na - 2
      na * i + j -> (na, 2 * na, 3 * na, 2 * na + 1) + j + 2 * (i - 1) * na
    na * (i + 1) - 1 -> (- 1, na - 1, 2 * na - 1, 0) + 2 * i * na
*/
static void mesh_disk_polar_cells_to_faces_a4(int * m_cf_a4, int na, int nd)
{
  int i, index, j, offset;

  index = 0;

  /* (1, 0) -> inner, radial */
  for (j = 0; j < na; ++j)
  {
    m_cf_a4[index + 0] = 0;
    m_cf_a4[index + 1] = j + 1;
    index += 2;
  }

  /* (1, 0) -> inner, arcs */
  for (j = 0; j < na - 1; ++j)
  {
    m_cf_a4[index + 0] = j + 1;
    m_cf_a4[index + 1] = j + 2;
    index += 2;
  }
  m_cf_a4[index + 0] = na;
  m_cf_a4[index + 1] = 1;
  index += 2;

  /* (1, 0) -> outer */
  for (i = 1; i < nd; ++i)
  {
    offset = na * i;
    /* radial */
    for (j = 1; j <= na; ++j)
    {
      m_cf_a4[index + 0] = offset - na + j;
      m_cf_a4[index + 1] = offset + j;
      index += 2;
    }

    /* arcs */
    for (j = 1; j < na; ++j)
    {
      m_cf_a4[index + 0] = offset + j;
      m_cf_a4[index + 1] = offset + j + 1;
      index += 2;
    }
    m_cf_a4[index + 0] = offset + na;
    m_cf_a4[index + 1] = offset + 1;
    index += 2;
  }

  /* (2, 0) -> inner */
  for (j = 0; j < na - 1; ++j)
  {
    m_cf_a4[index + 0] = 0;
    m_cf_a4[index + 1] = j + 1;
    m_cf_a4[index + 2] = j + 2;
    index += 3;
  }
  m_cf_a4[index + 0] = 0;
  m_cf_a4[index + 1] = na;
  m_cf_a4[index + 2] = 1;
  index += 3;

  /* (2, 0) -> outer */
  for (i = 1; i < nd; ++i)
  {
    offset = (i - 1) * na;
    for (j = 0; j < na - 1; ++j)
    {
      m_cf_a4[index + 0] = 1 + offset + j;
      m_cf_a4[index + 1] = na + 1 + offset + j;
      m_cf_a4[index + 2] = na + 2 + offset + j;
      m_cf_a4[index + 3] = 2 + offset + j;
      index += 4;
    }
    m_cf_a4[index + 0] = na + offset;
    m_cf_a4[index + 1] = 2 * na + offset;
    m_cf_a4[index + 2] = na + 1 + offset;
    m_cf_a4[index + 3] = 1 + offset;
    index += 4;
  }

  /* (2, 1) -> inner */
  for (j = 0; j < na - 1; ++j)
  {
    m_cf_a4[index + 0] = j;
    m_cf_a4[index + 1] = j + na;
    m_cf_a4[index + 2] = j + 1;
    index += 3;
  }
  m_cf_a4[index + 0] = na - 1;
  m_cf_a4[index + 1] = 2 * na - 1;
  m_cf_a4[index + 2] = 0;
  index += 3;

  /* (2, 1) -> outer */
  for (i = 1; i < nd; ++i)
  {
    offset = 2 * (i - 1) * na;
    for (j = 0; j < na - 1; ++j)
    {
      m_cf_a4[index + 0] = na + offset + j;
      m_cf_a4[index + 1] = 2 * na + offset + j;
      m_cf_a4[index + 2] = 3 * na + offset + j;
      m_cf_a4[index + 3] = 2 * na + 1 + offset + j;
      index += 4;
    }
    m_cf_a4[index + 0] = 2 * na - 1 + offset;
    m_cf_a4[index + 1] = 3 * na - 1 + offset;
    m_cf_a4[index + 2] = 4 * na - 1 + offset;
    m_cf_a4[index + 3] = 2 * na + offset;
    index += 4;
  }
}

jagged4 * mesh_disk_polar_cells_to_faces(int na, int nd, const int * m_cn)
{
  int m_cf_a2_size, m_cf_a3_size, m_cf_a4_size;
  jagged4 * m_cf;

  m_cf = (jagged4 *) malloc(sizeof(jagged4));
  if (m_cf == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(jagged4), "m_cf");
    goto end;
  }

  m_cf->a0 = 2;
  m_cf->a1 = (int *) malloc(sizeof(int) * 2);
  if (m_cf->a1 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(int) * 2, "m_cf->a1");
    goto m_cf_free;
  }
  mesh_cf_a1(m_cf->a1, 2);

  m_cf_a2_size = int_array_total_sum(2, m_cf->a1);
  m_cf->a2 = (int *) malloc(sizeof(int) * m_cf_a2_size);
  if (m_cf->a2 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(int) * m_cf_a2_size, "m_cf->a2");
    goto m_cf_a1_free;
  }
  mesh_cf_a2(m_cf->a2, 2, m_cn);

  m_cf_a3_size = int_array_total_sum(m_cf_a2_size, m_cf->a2);
  m_cf->a3 = (int *) malloc(sizeof(int) * m_cf_a3_size);
  if (m_cf->a3 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(int) * m_cf_a3_size, "m_cf->a3");
    goto m_cf_a2_free;
  }
  mesh_disk_polar_cells_to_faces_a3(m_cf->a3, na, nd);

  m_cf_a4_size = int_array_total_sum(m_cf_a3_size, m_cf->a3);
  m_cf->a4 = (int *) malloc(sizeof(int) * m_cf_a4_size);
  if (m_cf->a4 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(int) * m_cf_a4_size, "m_cf->a4");
    goto m_cf_a3_free;
  }
  mesh_disk_polar_cells_to_faces_a4(m_cf->a4, na, nd);

  return m_cf;

  /* cleaning if an error occurs */
m_cf_a3_free:
  free(m_cf->a3);
m_cf_a2_free:
  free(m_cf->a2);
m_cf_a1_free:
  free(m_cf->a1);
m_cf_free:
  free(m_cf);
end:
  return NULL;
}
