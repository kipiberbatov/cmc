#include <errno.h>

#include "cmc_error_message.h"
#include "mesh_qc.h"

void mesh_qc_boundary_layer_0_1_nodes_file_print_raw(FILE * out, const mesh * m)
{
  jagged1 * m_bd_layer_0_hyperfaces;
  jagged1 * m_bd_layer_0_cells;
  jagged1 * m_bd_layer_0_1_nodes;

  m_bd_layer_0_hyperfaces = mesh_qc_boundary_layer_0_hyperfaces(m);
  if (m_bd_layer_0_hyperfaces == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m_bd_layer_0_hyperfaces\n", stderr);
    return;
  }

  m_bd_layer_0_cells = mesh_qc_boundary_layer_0_cells(
    m, m_bd_layer_0_hyperfaces);
  if (m_bd_layer_0_cells == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m_bd_layer_0_cells\n", stderr);
    goto m_bd_layer_0_hyperfaces_free;
  }

  m_bd_layer_0_1_nodes = mesh_qc_boundary_layer_0_1_nodes(
    m, m_bd_layer_0_cells);
  if (m_bd_layer_0_1_nodes == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m_bd_layer_0_1_nodes\n", stderr);
    goto m_bd_layer_0_cells_free;
  }

  jagged1_file_print(out, m_bd_layer_0_1_nodes, "--raw");

  jagged1_free(m_bd_layer_0_1_nodes);
m_bd_layer_0_cells_free:
  jagged1_free(m_bd_layer_0_cells);
m_bd_layer_0_hyperfaces_free:
  jagged1_free(m_bd_layer_0_hyperfaces);
}

int main(void)
{
  mesh * m;
  FILE * in, * out;

  out = stdout;
  in = stdin;

  m = mesh_file_scan(in, "--raw");
  if (m == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan mesh m in format --raw\n", stderr);
    goto end;
  }

  m->fc = mesh_fc(m);
  if (m->fc == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m->fc\n", stderr);
    goto m_free;
  }

  mesh_qc_boundary_layer_0_1_nodes_file_print_raw(out, m);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate and print boundary layer 0 -> 1\n", stderr);
    goto m_free;
  }

m_free:
  mesh_free(m);
end:
  return errno;
}
