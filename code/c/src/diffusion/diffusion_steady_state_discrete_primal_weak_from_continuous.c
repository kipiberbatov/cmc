#include <errno.h>
#include <stdlib.h>

#include "boundary_scalar_field_discretize.h"
#include "boundary_pseudoscalar_field_discretize.h"
#include "de_rham.h"
#include "diffusion_steady_state_continuous.h"
#include "diffusion_steady_state_discrete_primal_weak.h"
#include "unsigned_approximation.h"

struct diffusion_steady_state_discrete_primal_weak *
diffusion_steady_state_discrete_primal_weak_from_continuous(
  const struct mesh * m,
  const double * m_vol_dm1,
  const double * m_vol_d,
  const struct diffusion_steady_state_continuous * data_continuous)
{
  int d;
  struct diffusion_steady_state_discrete_primal_weak * data_discrete;

  d = m->dim;

  *(void **) (&data_discrete) = malloc(sizeof(*data_discrete));
  if (errno)
    goto end;

  data_discrete->number_of_cells_1 = m->cn[1];
  data_discrete->number_of_cells_d = m->cn[d];

  data_discrete->kappa_1 = (double *) malloc(sizeof(double) * m->cn[1]);
  if (errno)
    goto data_discrete_free;
  unsigned_approximation_of_scalar_field_on_1_cells(
    data_discrete->kappa_1, m, data_continuous->kappa_1);

  data_discrete->source = (double *) malloc(sizeof(double) * m->cn[d]);
  if (errno)
    goto data_discrete_kappa_1_free;
  de_rham_nonzero(
    data_discrete->source, m, d, m_vol_d, data_continuous->source);

  data_discrete->boundary_dirichlet
  = mesh_boundary_nodes_from_constraint(m, data_continuous->boundary_dirichlet);
  if (errno)
    goto data_discrete_source_free;

  data_discrete->g_dirichlet
  = (double *) malloc(sizeof(double) * (data_discrete->boundary_dirichlet->a0));
  if (errno)
    goto data_discrete_boundary_dirichlet_free;
  boundary_scalar_field_discretize(
    data_discrete->g_dirichlet,
    m->dim_embedded,
    m->coord,
    data_discrete->boundary_dirichlet,
    data_continuous->g_dirichlet);

  data_discrete->boundary_neumann = mesh_boundary_hyperfaces_from_constraint(
    m, data_continuous->boundary_neumann);
  if (errno)
    goto data_discrete_g_dirichlet_free;

  data_discrete->g_neumann
  = (double *) malloc(sizeof(double) * (data_discrete->boundary_neumann->a0));
  if (errno)
    goto data_discrete_boundary_neumann_free;
  boundary_pseudoscalar_field_discretize(
    data_discrete->g_neumann,
    m,
    m_vol_dm1,
    data_discrete->boundary_neumann,
    data_continuous->g_neumann);

  return data_discrete;

  /* cleaning if an error occurs */
  free(data_discrete->g_neumann);
data_discrete_boundary_neumann_free:
  jagged1_free(data_discrete->boundary_neumann);
data_discrete_g_dirichlet_free:
  free(data_discrete->g_dirichlet);
data_discrete_boundary_dirichlet_free:
  jagged1_free(data_discrete->boundary_dirichlet);
data_discrete_source_free:
  free(data_discrete->source);
data_discrete_kappa_1_free:
  free(data_discrete->kappa_1);
data_discrete_free:
  free(data_discrete);
end:
  return NULL;
}
