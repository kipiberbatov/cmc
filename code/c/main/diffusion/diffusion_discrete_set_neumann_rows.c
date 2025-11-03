#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "diffusion_discrete_set_neumann_rows.h"
#include "mesh.h"

static int x1_axis_constant(const double * x)
{
  return (x[1] == 0. || x[1] == 1) && (0. < x[0] && x[0] < 1.);
}

int main(int argc, char ** argv)
{
  char * m_format, * m_laplacian_0_format, * m_laplacian_0_name, * m_name;
  struct mesh * m;
  struct jagged1 * neumann_nodes;
  struct matrix_sparse * m_laplacian_0;
  double * kappa_1;

#define ARGC 5
  if (argc != ARGC)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_number_of_command_line_arguments_mismatch(ARGC, argc);
    return EINVAL;
  }

  m_format = argv[1];
  m_name = argv[2];
  m_laplacian_0_format = argv[3];
  m_laplacian_0_name = argv[4];

  m = mesh_file_scan_by_name(m_name, m_format);
  if (m == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh m from file %s in format %s\n",
      m_name, m_format);
    goto end;
  }

  m->fc = mesh_fc(m);
  if (m->fc == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m->fc\n", stderr);
    goto m_free;
  }

  m_laplacian_0 = matrix_sparse_file_scan_by_name(
    m_laplacian_0_name, m_laplacian_0_format);
  if (m_laplacian_0 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan m_laplacian[0] from file %s in format %s\n",
      m_laplacian_0_name, m_laplacian_0_format);
    goto m_free;
  }

  neumann_nodes = mesh_boundary_nodes_from_constraint(m, x1_axis_constant);
  if (neumann_nodes == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate neumann_nodes\n", stderr);
    goto m_laplacian_0_free;
  }

  kappa_1 = malloc(sizeof(double) * m_laplacian_0->cols);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m_laplacian_0->cols, "kappa_1");
    goto neumann_node_free;
  }
  double_array_assign_constant(kappa_1, m_laplacian_0->cols, 1);

  diffusion_discrete_set_neumann_rows(m_laplacian_0, m, neumann_nodes, kappa_1);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m_laplacian_0\n", stderr);
    goto kappa_1_free;
  }

  matrix_sparse_file_print(stdout, m_laplacian_0, "--raw");

kappa_1_free:
  free(kappa_1);
neumann_node_free:
  free(neumann_nodes);
m_laplacian_0_free:
  matrix_sparse_free(m_laplacian_0);
m_free:
  mesh_free(m);
end:
  return errno;
}
