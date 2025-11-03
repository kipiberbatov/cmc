#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "matrix_sparse.h"
#include "mesh_qc.h"

static double f(const double * x)
{
  return - 4;
}

static double g_d(const double * x)
{
  return x[0] * x[0] + x[1] * x[1];
}

int main(int argc, char ** argv)
{
  char * m_format, * m_inner_0_format, * m_inner_0_name, * m_laplacian_0_format,
       * m_laplacian_0_name, * m_name, * out_format;
  double * m_inner_0, * x;
  mesh * m;
  jagged1 * m_nodes_bd;
  matrix_sparse * m_laplacian_0;

  if (argc != 8)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("the number of command line arguments must be 8\n", stderr);
    errno = EINVAL;
    goto end;
  }

  m_name = argv[1];
  m_format = argv[2];
  m = mesh_file_scan_by_name(m_name, m_format);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan m\n", stderr);
    goto end;
  }

  m->fc = mesh_fc(m);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m->fc\n", stderr);
    goto m_free;
  }

  m_nodes_bd = mesh_boundary_nodes(m);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m_nodes_bd\n", stderr);
    goto m_free;
  }

  m_laplacian_0_name = argv[3];
  m_laplacian_0_format = argv[4];

  m_laplacian_0 =
    matrix_sparse_file_scan_by_name(m_laplacian_0_name, m_laplacian_0_format);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m_laplacian[0]\n", stderr);
    goto m_nodes_bd_free;
  }

  m_inner_0_name = argv[5];
  m_inner_0_format = argv[6];
  m_inner_0 =
    double_array_file_scan_by_name(m_inner_0_name, m->cn[0], m_inner_0_format);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan m_inner\n", stderr);
    goto m_laplacian_0_free;
  }

  x = matrix_sparse_laplace_equation_solve_non_grid(
    m_laplacian_0, m->dim_embedded, m->coord, m_inner_0, m_nodes_bd, f, g_d);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate x\n", stderr);
    goto m_inner_0_free;
  }

  out_format = argv[7];
  double_array_file_print(stdout, m_laplacian_0->rows, x, out_format);

  free(x);
m_inner_0_free:
  free(m_inner_0);
m_laplacian_0_free:
  matrix_sparse_free(m_laplacian_0);
m_nodes_bd_free:
  jagged1_free(m_nodes_bd);
m_free:
  mesh_free(m);
end:
  return errno;
}
