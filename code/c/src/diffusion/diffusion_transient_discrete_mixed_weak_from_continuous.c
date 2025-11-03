#include <errno.h>
#include <stdlib.h>

#include "boundary_scalar_field_discretize.h"
#include "boundary_pseudoscalar_field_discretize.h"
#include "cmc_error_message.h"
#include "de_rham.h"
#include "diffusion_steady_state_discrete_flow_rate_from_potential.h"
#include "diffusion_transient_continuous.h"
#include "diffusion_transient_discrete_mixed_weak.h"
#include "double_array.h"
#include "mesh_qc.h"
#include "unsigned_approximation.h"

static void set_initial_flow_rate(
  double * initial_flow_rate,
  const struct mesh * m,
  const struct matrix_sparse * m_bd_1,
  const struct matrix_sparse * m_hodge_1,
  const struct diffusion_transient_continuous * data_continuous)
{
  double * discrete_potential, * dual_conductivity;

  errno = 0;

  dual_conductivity = (double *) malloc(sizeof(double) * m->cn[1]);
  if (dual_conductivity == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m->cn[1], "dual_conductivity");
    return;
  }
  unsigned_approximation_of_scalar_field_on_nonzero_cells(
    dual_conductivity, m, data_continuous->kappa_1, 1);

  errno = 0;

  discrete_potential = (double *) malloc(sizeof(double) * m->cn[0]);
  if (discrete_potential == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m->cn[0], "discrete_potential");
    goto dual_conductivity_free;
  }
  de_rham_0(discrete_potential, m, data_continuous->initial);

  errno = 0;

  diffusion_steady_state_discrete_flow_rate_from_potential(initial_flow_rate,
    m, m_bd_1, dual_conductivity, discrete_potential, m_hodge_1);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot calculate initial flow_rate\n");
    goto discrete_potential_free;
  }

  errno = 0;

discrete_potential_free:
  free(discrete_potential);
dual_conductivity_free:
  free(dual_conductivity);
}

static void discrete_dual_potential_from_continuous_potential(
  double * discrete_dual_potential,
  const struct mesh * m,
  const double * m_vol_d,
  double (*continuous_potential)(const double *))
{
  double * discrete_potential;

  errno = 0;

  discrete_potential = (double *) malloc(sizeof(double) * m->cn[0]);
  if (discrete_potential == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m->cn[0], "discrete_potential");
    return;
  }

  de_rham_0(discrete_potential, m, continuous_potential);
  mesh_qc_hodge_star_0(discrete_dual_potential, m, m_vol_d, discrete_potential);
  free(discrete_potential);

  errno = 0;
}

struct diffusion_transient_discrete_mixed_weak *
diffusion_transient_discrete_mixed_weak_from_continuous(
  const struct mesh * m,
  const double * m_vol_dm1,
  const double * m_vol_d,
  const struct matrix_sparse * m_bd_1,
  const struct matrix_sparse * m_hodge_1,
  const struct diffusion_transient_continuous * data_continuous)
{
  int d;
  struct diffusion_transient_discrete_mixed_weak * data_discrete;

  d = m->dim;

  *(void **) (&data_discrete) = malloc(sizeof(*data_discrete));
  if (data_discrete == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(*data_discrete), "data_discrete");
    goto end;
  }

  data_discrete->number_of_cells_dm1 = m->cn[d - 1];
  data_discrete->number_of_cells_d = m->cn[d];

  data_discrete->pi_d = (double *) malloc(sizeof(double) * m->cn[d]);
  if (data_discrete->pi_d == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m->cn[d], "data_discrete->pi_d");
    goto data_discrete_free;
  }
  unsigned_approximation_of_scalar_field_on_nonzero_cells(
    data_discrete->pi_d, m, data_continuous->pi_0, d);

  data_discrete->kappa_dm1 = (double *) malloc(sizeof(double) * m->cn[d - 1]);
  if (data_discrete->kappa_dm1 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m->cn[d - 1],
      "data_discrete->kappa_dm1");
    goto data_discrete_pi_d_free;
  }
  unsigned_approximation_of_scalar_field_on_hyperfaces(
    data_discrete->kappa_dm1, m, data_continuous->kappa_1);

  data_discrete->initial_dual_potential = (double *) malloc(
    sizeof(double) * m->cn[d]);
  if (data_discrete->initial_dual_potential == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m->cn[d],
      "data_discrete->initial_dual_potential");
    goto data_discrete_kappa_dm1_free;
  }
  discrete_dual_potential_from_continuous_potential(
    data_discrete->initial_dual_potential,
    m, m_vol_d, data_continuous->initial);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate data_discrete->initial_dual_potential\n", stderr);
    goto data_discrete_initial_dual_potential_free;
  }

  data_discrete->initial_flow_rate
  = (double *) calloc(m->cn[d - 1], sizeof(double));
  if (data_discrete->initial_flow_rate == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m->cn[d - 1],
      "data_discrete->initial_flow_rate");
    goto data_discrete_initial_dual_potential_free;
  }
  set_initial_flow_rate(data_discrete->initial_flow_rate,
    m, m_bd_1, m_hodge_1, data_continuous);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate data_discrete->initial_dual_potential\n", stderr);
    goto data_discrete_initial_flow_rate_free;
  }

  data_discrete->source = (double *) malloc(sizeof(double) * m->cn[d]);
  if (data_discrete->source == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m->cn[d],
      "data_discrete->source");
    goto data_discrete_initial_flow_rate_free;
  }
  de_rham_nonzero(
    data_discrete->source, m, m->dim, m_vol_d, data_continuous->source);

  data_discrete->boundary_dirichlet_dm1
  = mesh_boundary_hyperfaces_from_constraint(
    m, data_continuous->boundary_dirichlet);
  if (data_discrete->boundary_dirichlet_dm1 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot calculate data_discrete->boundary_dirichlet_dm1\n");
    goto data_discrete_source_free;
  }

  data_discrete->boundary_dirichlet_0 = mesh_boundary_nodes_from_constraint(
    m, data_continuous->boundary_dirichlet);
  if (data_discrete->boundary_dirichlet_0 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot calculate data_discrete->boundary_dirichlet_0\n");
    goto data_discrete_boundary_dirichlet_dm1_free;
  }

  data_discrete->g_dirichlet_0 = (double *) malloc(
    sizeof(double) * (data_discrete->boundary_dirichlet_0->a0));
  if (data_discrete->g_dirichlet_0 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(
      sizeof(double) * data_discrete->boundary_dirichlet_0->a0,
      "data_discrete->g_dirichlet_0");
    goto data_discrete_boundary_dirichlet_0_free;
  }
  boundary_scalar_field_discretize(
    data_discrete->g_dirichlet_0,
    m->dim_embedded,
    m->coord,
    data_discrete->boundary_dirichlet_0,
    data_continuous->g_dirichlet);

  data_discrete->boundary_neumann_dm1
  = mesh_boundary_hyperfaces_from_constraint(
    m, data_continuous->boundary_neumann);
  if (data_discrete->boundary_neumann_dm1 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot calculate data_discrete->boundary_neumann_dm1\n");
    goto data_discrete_g_dirichlet_0_free;
  }

  data_discrete->g_neumann_dm1 = (double *) malloc(
    sizeof(double) * (data_discrete->boundary_neumann_dm1->a0));
  if (data_discrete->g_neumann_dm1 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(
      sizeof(double) * data_discrete->boundary_neumann_dm1->a0,
      "data_discrete->g_neumann_dm1");
    goto data_discrete_boundary_neumann_dm1_free;
  }
  boundary_pseudoscalar_field_discretize(
    data_discrete->g_neumann_dm1,
    m,
    m_vol_dm1,
    data_discrete->boundary_neumann_dm1,
    data_continuous->g_neumann);

  double_array_assemble_from_sparse_array(data_discrete->initial_flow_rate,
    data_discrete->boundary_neumann_dm1, data_discrete->g_neumann_dm1);

  return data_discrete;

  /* cleaning if an error occurs */
  free(data_discrete->g_neumann_dm1);
data_discrete_boundary_neumann_dm1_free:
  jagged1_free(data_discrete->boundary_neumann_dm1);
data_discrete_g_dirichlet_0_free:
  free(data_discrete->g_dirichlet_0);
data_discrete_boundary_dirichlet_0_free:
  jagged1_free(data_discrete->boundary_dirichlet_0);
data_discrete_boundary_dirichlet_dm1_free:
  jagged1_free(data_discrete->boundary_dirichlet_dm1);
data_discrete_source_free:
  free(data_discrete->source);
data_discrete_initial_flow_rate_free:
  free(data_discrete->initial_flow_rate);
data_discrete_initial_dual_potential_free:
  free(data_discrete->initial_dual_potential);
data_discrete_kappa_dm1_free:
  free(data_discrete->kappa_dm1);
data_discrete_pi_d_free:
  free(data_discrete->pi_d);
data_discrete_free:
  free(data_discrete);
end:
  return NULL;
}
