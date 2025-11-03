#include <errno.h>

#include "cmc_error_message.h"
#include "mesh_qc.h"

int main(void)
{
  mesh * m;
  matrix_sparse * m_cbd_0, * m_cbd_1, * m_cbd_star_elasticity_1,
                * m_cbd_star_elasticity_2, * m_laplacian_elasticity_1;
  matrix_sparse ** m_bd;

  m = mesh_file_scan(stdin, "--raw");
  if (m == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan mesh m in format --raw\n", stderr);
    goto end;
  }

  m_bd = mesh_file_scan_boundary(stdin, m);
  if (m_bd == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan boundary matrices m_bd from mesh file\n", stderr);
    goto m_free;
  }

  m_cbd_0 = matrix_sparse_transpose(m_bd[0]);
  if (m_cbd_0 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m_cbd_0\n", stderr);
    goto m_bd_free;
  }

  m_cbd_1 = matrix_sparse_transpose(m_bd[1]);
  if (m_cbd_1 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m_cbd_1\n", stderr);
    goto m_cbd_0_free;
  }

  m_cbd_star_elasticity_1 = m_bd[0];
  m_cbd_star_elasticity_2 = m_bd[1];

  m_laplacian_elasticity_1 = matrix_sparse_laplacian_p(
    m_cbd_0, m_cbd_1, m_cbd_star_elasticity_1, m_cbd_star_elasticity_2);
  if (m_laplacian_elasticity_1 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m_laplacian_elasticity_1\n", stderr);
    goto m_cbd_1_free;
  }

  matrix_sparse_file_print(stdout, m_laplacian_elasticity_1, "--raw");

  matrix_sparse_free(m_laplacian_elasticity_1);
m_cbd_1_free:
  matrix_sparse_free(m_cbd_1);
m_cbd_0_free:
  matrix_sparse_free(m_cbd_0);
m_bd_free:
  matrix_sparse_array_free(m_bd, m->dim);
m_free:
  mesh_free(m);
end:
  return errno;
}
