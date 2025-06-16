#include "diffusion_steady_state_continuous.h"
#include "diffusion_steady_state_discrete.h"
#include "diffusion_steady_state_discrete_from_continuous.h"
#include "diffusion_steady_state_discrete_pre_processing.h"
#include "cmc_error_message.h"
#include "cmc_memory.h"
#include "mesh.h"

void diffusion_steady_state_discrete_from_continuous(
  struct diffusion_steady_state_discrete ** result,
  int * status,
  const struct mesh * m,
  const struct jagged1 * m_boundary_dm1,
  const double * m_vol_dm1,
  const double * m_vol_d,
  const struct diffusion_steady_state_continuous * data_continuous,
  const struct diffusion_steady_state_discrete_pre_processing * functions)
{
  int d, m_cn_1, m_cn_dm1, m_cn_d;
  int * m_cn;
  double * conductivity, * dual_conductivity, * g_dirichlet, * g_neumann,
         * production_rate;
  struct jagged1 * boundary_dirichlet_0, * boundary_dirichlet_dm1,
                 * boundary_neumann_dm1;
  struct diffusion_steady_state_discrete * data_discrete;

  d = m->dim;
  m_cn = m->cn;
  m_cn_1 = m_cn[1];
  m_cn_dm1 = m_cn[d - 1];
  m_cn_d = m_cn[d];

  /* result */
  cmc_memory_allocate((void **) result, status, sizeof(**result));
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("result");
    goto end;
  }

  /* conductivity */
  cmc_memory_allocate(
    (void **) &conductivity, status, sizeof(double) * m_cn_dm1);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("conductivity");
    goto result_free;
  }
  functions->get_conductivity(conductivity, m, data_continuous->kappa_1);

  /* dual_conductivity */
  cmc_memory_allocate(
    (void **) &dual_conductivity, status, sizeof(double) * m_cn_1);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("conductivity");
    goto conductivity_free;
  }
  functions->get_dual_conductivity(
    dual_conductivity, m, data_continuous->kappa_1);

  /* production_rate */
  cmc_memory_allocate(
    (void **) &production_rate, status, sizeof(double) * m_cn_d);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("production_rate");
    goto dual_conductivity_free;
  }
  functions->get_production_rate(
    production_rate, m, m_vol_d, data_continuous->source);

  /* boundary_dirichlet_dm1 */
  functions->get_boundary_dirichlet_dm1(
    &boundary_dirichlet_dm1,
    status,
    m,
    m_boundary_dm1,
    data_continuous->boundary_dirichlet);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_cannot_calculate("boundary_dirichlet_dm1");
    goto production_rate_free;
  }

  /* boundary_dirichlet_0 */
  mesh_boundary_hyperface_get_lower_faces(
    &boundary_dirichlet_0, status, m, boundary_dirichlet_dm1, 0);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_cannot_calculate("boundary_dirichlet_0");
    goto boundary_dirichlet_dm1_free;
  }

  /* g_dirichlet */
  cmc_memory_allocate(
    (void **) &g_dirichlet,
    status,
    sizeof(double) * boundary_dirichlet_0->a0);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_cannot_calculate("boundary_dirichlet_0");
    goto boundary_dirichlet_0_free;
  }
  functions->get_g_dirichlet(
    g_dirichlet, m, boundary_dirichlet_0, data_continuous->g_dirichlet);

  boundary_neumann_dm1 = jagged1_difference(m_boundary_dm1,
                                            boundary_dirichlet_dm1);
  if (boundary_neumann_dm1 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_cannot_calculate("boundary_neumann_dm1");
    *status = 1;
    goto g_dirichlet_free;
  }

  /* g_neumann_dm1 */
  cmc_memory_allocate(
    (void **) &g_neumann, status, sizeof(double) * boundary_neumann_dm1->a0);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("data_discrete->g_neumann");
    goto boundary_neumann_dm1_free;
  }
  functions->get_g_neumann(
    g_neumann,
    m,
    m_vol_dm1,
    boundary_neumann_dm1,
    data_continuous->g_neumann);

  data_discrete = *result;
  data_discrete->number_of_cells_1 = m_cn_1;
  data_discrete->number_of_cells_dm1 = m_cn_dm1;
  data_discrete->number_of_cells_d = m_cn_d;
  data_discrete->conductivity = conductivity;
  data_discrete->dual_conductivity = dual_conductivity;
  data_discrete->production_rate = production_rate;
  data_discrete->boundary_dirichlet_dm1 = boundary_dirichlet_dm1;
  data_discrete->boundary_dirichlet_0 = boundary_dirichlet_0;
  data_discrete->g_dirichlet = g_dirichlet;
  data_discrete->boundary_neumann_dm1 = boundary_neumann_dm1;
  data_discrete->g_neumann = g_neumann;
  return;

  /* cleaning if an error occurs */
  cmc_memory_free(g_neumann);
boundary_neumann_dm1_free:
  jagged1_free(boundary_neumann_dm1);
g_dirichlet_free:
  cmc_memory_free(g_dirichlet);
boundary_dirichlet_0_free:
  jagged1_free(boundary_dirichlet_0);
boundary_dirichlet_dm1_free:
  jagged1_free(boundary_dirichlet_dm1);
production_rate_free:
  cmc_memory_free(production_rate);
dual_conductivity_free:
  cmc_memory_free(dual_conductivity);
conductivity_free:
  cmc_memory_free(conductivity);
result_free:
  cmc_memory_free(*result);
end:
  return;
}
