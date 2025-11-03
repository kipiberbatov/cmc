#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "forman_private.h"
#include "int.h"
#include "mesh_private.h"

jagged4 * forman_cf(const mesh * m, const int * m_forman_cn)
{
  int d, m_forman_cf_a2_size, m_forman_cf_a3_size, m_forman_cf_a4_size;
  jagged4 * m_forman_cf;

  d = m->dim;

  m_forman_cf = (jagged4 *) malloc(sizeof(jagged4));
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(jagged4), "m_forman_cf");
    goto end;
  }

  m_forman_cf->a0 = d;
  m_forman_cf->a1 = (int *) malloc(sizeof(int) * d);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(int) * d, "m_forman_cf->a1");
    goto m_forman_cf_free;
  }
  mesh_cf_a1(m_forman_cf->a1, d);

  m_forman_cf_a2_size = int_array_total_sum(d, m_forman_cf->a1);
  m_forman_cf->a2 = (int *) malloc(sizeof(int) * m_forman_cf_a2_size);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(int) * m_forman_cf_a2_size,
                              "m_forman_cf->a2");
    goto m_forman_cf_a1_free;
  }
  mesh_cf_a2(m_forman_cf->a2, d, m_forman_cn);

  m_forman_cf_a3_size = int_array_total_sum(m_forman_cf_a2_size,
                                            m_forman_cf->a2);
  m_forman_cf->a3 = (int *) malloc(sizeof(int) * m_forman_cf_a3_size);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(int) * m_forman_cf_a3_size,
                              "m_forman_cf->a3");
    goto m_forman_cf_a2_free;
  }
  forman_cf_a3(m_forman_cf->a3, m, m_forman_cn);

  m_forman_cf_a4_size =  int_array_total_sum(m_forman_cf_a3_size,
                                             m_forman_cf->a3);
  m_forman_cf->a4 = (int *) malloc(sizeof(int) * m_forman_cf_a4_size);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(int) * m_forman_cf_a4_size,
                              "m_forman_cf->a4");
    goto m_forman_cf_a3_free;
  }
  forman_cf_a4(m_forman_cf->a4, m);

  return m_forman_cf;

  /* cleaning if an error occurs */
m_forman_cf_a3_free:
  free(m_forman_cf->a3);
m_forman_cf_a2_free:
  free(m_forman_cf->a2);
m_forman_cf_a1_free:
  free(m_forman_cf->a1);
m_forman_cf_free:
  free(m_forman_cf);
end:
  return NULL;
}
