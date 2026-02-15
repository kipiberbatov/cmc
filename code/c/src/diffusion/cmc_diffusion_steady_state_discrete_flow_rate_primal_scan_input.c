#include <errno.h>

#include "cmc_diffusion_steady_state_discrete_flow_rate_primal__struct.h"
#include "cmc_diffusion_steady_state_discrete_flow_rate_primal_arguments__struct.h"
#include "cmc_diffusion_steady_state_discrete_flow_rate_primal_scan_input.h"
#include "cmc_error_message.h"
#include "cmc_file_open.h"
#include "cmc_file_close.h"
#include "cmc_memory.h"
#include "double_array.h"
#include "mesh.h"

void cmc_diffusion_steady_state_discrete_flow_rate_primal_scan_input(
  struct cmc_diffusion_steady_state_discrete_flow_rate_primal * input,
  int * status,
  const struct cmc_diffusion_steady_state_discrete_flow_rate_primal_arguments *
    arguments)
{
  int * m_cn;
  FILE * m_file;

  cmc_file_open(&m_file, status, arguments->m_name, "r");
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_string("cannot open mesh file\n");
    goto end;
  }

  input->m = mesh_file_scan(m_file, arguments->m_format);
  if (input->m == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh m from file %s in format %s\n",
      arguments->m_name, arguments->m_format);
    cmc_file_close(m_file, status);
    *status = errno;
    goto end;
  }

  m_cn = input->m->cn;

  input->m_bd_1 = mesh_file_scan_boundary_p(m_file, input->m, 1);
  if (input->m_bd_1 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan m_bd_1 from file %s\n", arguments->m_name);
    fclose(m_file);
    *status = errno;
    goto m_free;
  }
  fclose(m_file);

  input->m_hodge = matrix_sparse_array_file_scan_by_name(
    arguments->m_hodge_name, 2, arguments->m_hodge_format);
  if (input->m_hodge == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan m_hodge form file %s in format %s\n",
      arguments->m_hodge_name, arguments->m_hodge_format);
    *status = errno;
    goto m_bd_1_free;
  }

  input->dual_conductivity = double_array_file_scan_by_name(
    arguments->dual_conductivity_name,
    m_cn[1],
    arguments->dual_conductivity_format);
  if (input->dual_conductivity == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan dual_conductivity form file %s%s%s in format %s%s%s\n",
      color_variable, arguments->dual_conductivity_name, color_none,
      color_variable, arguments->dual_conductivity_format, color_none);
    *status = errno;
    goto m_hodge_free;
  }

  input->potential = double_array_file_scan_by_name(
    arguments->potential_name, m_cn[0], arguments->potential_format);
  if (input->potential == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan potential form file %s in format %s\n",
      arguments->potential_name, arguments->potential_format);
    *status = errno;
    goto dual_conductivity_free;
  }

  return;

  /* cleaning if an error occurs */
dual_conductivity_free:
  cmc_memory_free(input->dual_conductivity);
m_hodge_free:
  matrix_sparse_array_free(input->m_hodge, 2);
m_bd_1_free:
  matrix_sparse_free(input->m_bd_1);
m_free:
  mesh_free(input->m);
end:
  return;
}
