#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "diffusion_transient_discrete_mixed_weak.h"
#include "diffusion_transient_discrete_mixed_weak_solve_trapezoidal_next.h"
#include "diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data.h"
#include "mesh_qc.h"

static void loop(
  double * flow_rate,
  double * dual_potential,
  double * y,
  double * flow_rate_reduced,
  const struct diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data *
    input,
  int number_of_steps)
{
  int i, m_cn_dm1, m_cn_d;

  m_cn_d = input->data->number_of_cells_d;
  m_cn_dm1 = input->data->number_of_cells_dm1;

  for (i = 0; i < number_of_steps; ++i)
  {
    diffusion_transient_discrete_mixed_weak_solve_trapezoidal_next(
      flow_rate + m_cn_dm1 * (i + 1),
      dual_potential + m_cn_d * (i + 1),
      y,
      flow_rate_reduced,
      flow_rate + m_cn_dm1 * i,
      dual_potential + m_cn_d * i,
      input);
  }
}

void diffusion_transient_discrete_mixed_weak_solve_trapezoidal(
  double * flow_rate,
  double * dual_potential,
  const struct mesh * m,
  const struct matrix_sparse * m_cbd_dm1,
  const double * m_inner_dm1,
  const double * m_inner_d,
  const struct diffusion_transient_discrete_mixed_weak * data,
  double time_step,
  int number_of_steps)
{
  int d, m_cn_dm1, m_cn_dm1_bar, m_cn_d;
  double * flow_rate_reduced, * y;
  struct diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data * input;

  d = m->dim;
  m_cn_dm1 = m->cn[d - 1];
  m_cn_dm1_bar = m_cn_dm1 - data->boundary_neumann_dm1->a0;
  m_cn_d = m->cn[d];

  input
  = diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data_initialize(
    m, m_cbd_dm1, m_inner_dm1, m_inner_d, data, time_step);
  if (input == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot initialize constant input for loop\n", stderr);
    return;
  }

  y = (double *) malloc(sizeof(double) * m_cn_d);
  if (y == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m_cn_d, "y");
    goto input_free;
  }

  flow_rate_reduced = (double *) malloc(sizeof(double) * m_cn_dm1_bar);
  if (flow_rate_reduced == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m_cn_dm1_bar,
                              "flow_rate_reduced");
    goto y_free;
  }

  /* initialization */
  memcpy(flow_rate, data->initial_flow_rate, sizeof(double) * m_cn_dm1);
  memcpy(dual_potential, data->initial_dual_potential, sizeof(double) * m_cn_d);

  loop(flow_rate, dual_potential, y, flow_rate_reduced, input, number_of_steps);

  free(flow_rate_reduced);
y_free:
  free(y);
input_free:
  diffusion_transient_discrete_mixed_weak_trapezoidal_loop_data_free(input);
}
