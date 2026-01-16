#include "cmc_error_message.h"
#include "cmc_memory.h"
#include "mesh.h"

static int mesh_boundary_dm1_a0(const struct jagged2 * m_fc_dm1_d)
{
  int i, m_boundary_dm1_a0, m_cn_dm1;
  int * m_fc_dm1_d_a1;

  m_cn_dm1 = m_fc_dm1_d->a0;
  m_fc_dm1_d_a1 = m_fc_dm1_d->a1;

  m_boundary_dm1_a0 = 0;
  for (i = 0; i < m_cn_dm1; ++i)
    if (m_fc_dm1_d_a1[i] == 1)
      ++m_boundary_dm1_a0;
  return m_boundary_dm1_a0;
}

static void
mesh_boundary_dm1_a1(int * m_boundary_dm1_a1, const struct jagged2 * m_fc_dm1_d)
{
  int i, index, m_cn_dm1;
  int * m_fc_dm1_d_a1;

  m_cn_dm1 = m_fc_dm1_d->a0;
  m_fc_dm1_d_a1 = m_fc_dm1_d->a1;

  index = 0;
  for (i = 0; i < m_cn_dm1; ++i)
  {
    if (m_fc_dm1_d_a1[i] == 1)
    {
      m_boundary_dm1_a1[index] = i;
      ++index;
    }
  }
}

void mesh_boundary_dm1(
  struct jagged1 ** m_boundary_dm1, int * status, const struct mesh * m)
{
  int d, m_boundary_dm1_a0;
  int * m_boundary_dm1_a1;
  struct jagged2 m_fc_dm1_d;

  d = m->dim;
  mesh_fc_part2(&m_fc_dm1_d, m, d - 1, d);

  cmc_memory_allocate(
    (void **) m_boundary_dm1, status, sizeof(struct jagged1));
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("m_boundary_dm1");
    return;
  }

  m_boundary_dm1_a0 = mesh_boundary_dm1_a0(&m_fc_dm1_d);
  cmc_memory_allocate(
    (void **) &m_boundary_dm1_a1, status, sizeof(int) * m_boundary_dm1_a0);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("m_boundary_dm1_a1");
    cmc_memory_free(*m_boundary_dm1);
    return;
  }
  mesh_boundary_dm1_a1(m_boundary_dm1_a1, &m_fc_dm1_d);

  (*m_boundary_dm1)->a0 = m_boundary_dm1_a0;
  (*m_boundary_dm1)->a1 = m_boundary_dm1_a1;
}
