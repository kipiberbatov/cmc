#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "int.h"
#include "mesh.h"

static void mesh_fc_a1(int * m_fc_a1, int m_dim)
{
  int q;

  for (q = 0; q <= m_dim; ++q)
    m_fc_a1[q] = m_dim - q;
}

static void mesh_fc_a2(int * m_fc_a2, int m_dim, const int * m_cn)
{
  int ind, m_cn_q, p, q;

  ind = 0;
  for (q = 0; q < m_dim; ++q)
  {
    m_cn_q = m_cn[q];
    for (p = q + 1; p <= m_dim; ++p)
    {
      m_fc_a2[ind] = m_cn_q;
      ++ind;
    }
  }
}

/* m_fc_a3 has zeroes assigned initially */
static void mesh_fc_a3(int * m_fc_a3, const mesh * m)
{
  int i, ind, j, j_loc, m_cn_q, m_dim, p, q;
  int * m_cn;
  jagged1 m_cf_p_q_i;
  jagged2 m_cf_p_q;

  m_dim = m->dim;
  m_cn = m->cn;
  ind = 0;
  for (q = 0; q < m_dim; ++q)
  {
    m_cn_q = m_cn[q];
    for (p = q + 1; p <= m_dim; ++p)
    {
      mesh_cf_part2(&m_cf_p_q, m, p, q);
      for (i = 0; i < m_cn[p]; ++i)
      {
        jagged2_part1(&m_cf_p_q_i, &m_cf_p_q, i);
        for (j_loc = 0; j_loc < m_cf_p_q_i.a0; ++j_loc)
        {
          j = (m_cf_p_q_i.a1)[j_loc];
          ++(m_fc_a3[ind + j]);
        }
      }
      ind += m_cn_q;
    }
  }
}

static void mesh_fc_a4(int * m_fc_a4, const mesh * m, int * m_fc_a3)
{
  int i, ind, ind_loc, j, j_loc, m_cn_q, m_dim, p, q, tmp, tmp_list_sum;
  int * ind_current, * m_cn;
  jagged1 m_cf_p_q_i;
  jagged2 m_cf_p_q;

  m_dim = m->dim;
  m_cn = m->cn;
  ind_loc = 0;
  ind = 0;
  for (q = 0; q < m_dim; ++q)
  {
    m_cn_q = m_cn[q];
    for (p = q + 1; p <= m_dim; ++p)
    {
      ind_current = (int *) calloc(m_cn_q, sizeof(int));
      if (ind_current == NULL)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fprintf(stderr,
          "cannot allocate %zu bytes of memory for ind_current\n",
          sizeof(int) * m_cn_q);
        return;
      }
      mesh_cf_part2(&m_cf_p_q, m, p, q);
      for (i = 0; i < m_cn[p]; ++i)
      {
        jagged2_part1(&m_cf_p_q_i, &m_cf_p_q, i);
        for (j_loc = 0; j_loc < m_cf_p_q_i.a0; ++j_loc)
        {
          j = (m_cf_p_q_i.a1)[j_loc];
          tmp_list_sum = int_array_total_sum(j, m_fc_a3 + ind_loc);
          tmp = ind + tmp_list_sum + ind_current[j];
          m_fc_a4[tmp] = i;
          ++ind_current[j];
        }
      }
      free(ind_current);
      ind += int_array_total_sum(m_cn[q], m_fc_a3 + ind_loc);
      ind_loc += m_cn_q;
    }
  }
}

/* the next function constructs fc if only cf is given */
jagged4 * mesh_fc(const mesh * m)
{
  int m_fc_a2_size, m_fc_a3_size, m_fc_a4_size;
  jagged4 * m_fc;

  m_fc = (jagged4 *) malloc(sizeof(jagged4));
  if (m_fc == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for m_fc\n",
      sizeof(jagged4));
    goto end;
  }

  m_fc->a0 = m->dim;
  m_fc->a1 = (int *) malloc(sizeof(int) * m->dim);
  if (m_fc->a1 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for m_fc->a1\n",
      sizeof(int) * m->dim);
    goto m_fc_free;
  }
  mesh_fc_a1(m_fc->a1, m->dim);

  m_fc_a2_size = int_array_total_sum(m->dim, m_fc->a1);
  m_fc->a2 = (int *) malloc(sizeof(int) * m_fc_a2_size);
  if (m_fc->a2 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for m_fc->a2\n",
      sizeof(int) *  m_fc_a2_size);
    goto m_fc_a1_free;
  }
  mesh_fc_a2(m_fc->a2, m->dim, m->cn);

  m_fc_a3_size = int_array_total_sum(m_fc_a2_size, m_fc->a2);
  m_fc->a3 = (int *) calloc(m_fc_a3_size, sizeof(int));
  if (m_fc->a3 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for m_fc->a3\n",
      sizeof(int) *  m_fc_a3_size);
    goto m_fc_a2_free;
  }
  mesh_fc_a3(m_fc->a3, m);

  m_fc_a4_size = int_array_total_sum(m_fc_a3_size, m_fc->a3);
  m_fc->a4 = (int *) malloc(sizeof(int) * m_fc_a4_size);
  if (m_fc->a4 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for m_fc->a4\n",
      sizeof(int) *  m_fc_a4_size);
    goto m_fc_a3_free;
  }
  mesh_fc_a4(m_fc->a4, m, m_fc->a3);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate for m->fc->a4\n", stderr);
    goto m_fc_a4_free;
  }

  return m_fc;

  /* cleaning if an error occurs */
m_fc_a4_free:
  free(m_fc->a4);
m_fc_a3_free:
  free(m_fc->a3);
m_fc_a2_free:
  free(m_fc->a2);
m_fc_a1_free:
  free(m_fc->a2);
m_fc_free:
  free(m_fc);
end:
  return NULL;
}
