#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "diffusion_transient_discrete_mixed_weak.h"
#include "double_array.h"
#include "int.h"
#include "jagged.h"

struct diffusion_transient_discrete_mixed_weak *
diffusion_transient_discrete_mixed_weak_file_scan_raw(FILE * in)
{
  struct diffusion_transient_discrete_mixed_weak * data;

  *(void **) (&data) = malloc(sizeof(*data));
  if (data == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(*data), "data");
    goto end;
  }

  data->number_of_cells_dm1 = int_file_scan(in);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan data->number_of_cells_dm1\n", stderr);
    goto data_free;
  }

  data->number_of_cells_d = int_file_scan(in);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan data->number_of_cells_d\n", stderr);
    goto data_free;
  }

  data->pi_d = double_array_file_scan(in, data->number_of_cells_d, "--raw");
  if (data->pi_d == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan data->pi_d\n", stderr);
    goto data_free;
  }

  data->kappa_dm1 = double_array_file_scan(in,
    data->number_of_cells_dm1, "--raw");
  if (data->kappa_dm1 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan data->kappa_dm1\n", stderr);
    goto data_pi_d_free;
  }

  data->initial_dual_potential = double_array_file_scan(in,
    data->number_of_cells_d, "--raw");
  if (data->initial_dual_potential == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan data->initial_dual_potential\n", stderr);
    goto data_kappa_dm1_free;
  }

  data->initial_flow_rate = double_array_file_scan(in,
    data->number_of_cells_dm1, "--raw");
  if (data->initial_flow_rate == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan data->initial_flow_rate\n", stderr);
    goto data_initial_dual_potential_free;
  }

  data->source = double_array_file_scan(in, data->number_of_cells_d, "--raw");
  if (data->source == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan data->source\n", stderr);
    goto data_initial_flow_rate_free;
  }

  data->boundary_dirichlet_dm1 = jagged1_file_scan(in, "--raw");
  if (data->boundary_dirichlet_dm1 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan data->boundary_dirichlet_dm1\n", stderr);
    goto data_source_free;
  }

  data->boundary_dirichlet_0 = jagged1_file_scan(in, "--raw");
  if (data->boundary_dirichlet_0 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan data->boundary_dirichlet_0\n", stderr);
    goto data_boundary_dirichlet_dm1_free;
  }

  data->g_dirichlet_0 = double_array_file_scan(in,
    data->boundary_dirichlet_0->a0, "--raw");
  if (data->g_dirichlet_0 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan data->g_dirichlet_0\n", stderr);
    goto data_boundary_dirichlet_0_free;
  }

  data->boundary_neumann_dm1 = jagged1_file_scan(in, "--raw");
  if (data->boundary_neumann_dm1 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan data->boundary_neumann_dm1\n", stderr);
    goto data_g_dirichlet_0_free;
  }

  data->g_neumann_dm1 = double_array_file_scan(in,
    data->boundary_neumann_dm1->a0, "--raw");
  if (data->g_neumann_dm1 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan data->g_neumann_dm1\n", stderr);
    goto data_boundary_neumann_dm1_free;
  }

  return data;

  /* cleaning if an error occurs */
data_boundary_neumann_dm1_free:
  jagged1_free(data->boundary_neumann_dm1);
data_g_dirichlet_0_free:
  free(data->g_dirichlet_0);
data_boundary_dirichlet_0_free:
  jagged1_free(data->boundary_dirichlet_0);
data_boundary_dirichlet_dm1_free:
  jagged1_free(data->boundary_dirichlet_dm1);
data_source_free:
  free(data->source);
data_initial_flow_rate_free:
  free(data->initial_flow_rate);
data_initial_dual_potential_free:
  free(data->initial_dual_potential);
data_kappa_dm1_free:
  free(data->kappa_dm1);
data_pi_d_free:
  free(data->pi_d);
data_free:
  free(data);
end:
  return NULL;
}
