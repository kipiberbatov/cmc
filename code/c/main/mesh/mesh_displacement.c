#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "mesh_qc.h"

static void mesh_displacement_file_print_raw(
  FILE * out, const mesh * m, const matrix_sparse * m_bd_0, const double * u)
{
  int i, m_dim_embedded;
  double * m_displacement_i;
  double ** m_displacement;

  m_dim_embedded = m->dim_embedded;
  m_displacement = mesh_displacement(m, m_bd_0, u);
  if (m_displacement == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m_displacement\n", stderr);
    return;
  }
  for (i = 0; i < m->cn[0]; ++i)
  {
    m_displacement_i = m_displacement[i];
    double_array_file_print(out, m_dim_embedded, m_displacement_i, "--raw");
  }
}

static void
mesh_displacement_unit_cochain_file_print_file_scan(FILE * out, FILE * in)
{
  mesh * m;
  matrix_sparse ** m_bd;
  double * u;

  m = mesh_file_scan(in, "--raw");
  if (m == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan mesh m in format --raw\n", stderr);
    return;
  }

  m->fc = mesh_fc(m);
  if (m->fc == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m->fc\n", stderr);
    goto m_free;
  }

  m_bd = mesh_file_scan_boundary(in, m);
  if (m_bd == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan boundary matrices m_bd from mesh file\n", stderr);
    goto m_free;
  }

  u = (double *) malloc(sizeof(double) * m->cn[1]);
  if (u == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate memory %ld bytes of memory for 1-cochain u\n",
      sizeof(double) * m->cn[1]);
    goto m_bd_free;
  }
  double_array_assign_constant(u, m->cn[1], 1.);

  mesh_displacement_file_print_raw(out, m, m_bd[0], u);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m_displacement\n", stderr);
  }

  free(u);
m_bd_free:
  matrix_sparse_array_free(m_bd, m->dim);
m_free:
  mesh_free(m);
}

int main(void)
{
  mesh_displacement_unit_cochain_file_print_file_scan(stdout, stdin);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("unsuccessful run\n", stderr);
  }
  return errno;
}
