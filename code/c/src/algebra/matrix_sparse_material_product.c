#include "cmc_error_message.h"
#include "matrix_sparse.h"

matrix_sparse * matrix_sparse_material_product(
  const matrix_sparse * m_cbd_0,
  const double * kappa_1,
  const matrix_sparse * m_cbd_star_1)
{
  matrix_sparse * result, * m_cbd_star_1_material;

  m_cbd_star_1_material = matrix_sparse_copy(m_cbd_star_1);
  if (m_cbd_star_1_material == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot initialize m_cbd_star_1_material\n", stderr);
    return NULL;
  }
  matrix_sparse_multiply_with_diagonal_matrix(m_cbd_star_1_material, kappa_1);

  result = matrix_sparse_product(m_cbd_star_1_material, m_cbd_0);
  if (result == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate result\n", stderr);
    matrix_sparse_free(m_cbd_star_1_material);
    return NULL;
  }
  matrix_sparse_free(m_cbd_star_1_material);

  return result;
}
