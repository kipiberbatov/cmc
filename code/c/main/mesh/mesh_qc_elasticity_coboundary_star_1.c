#include <errno.h>
#include <string.h>

#include "cmc_error_message.h"
#include "double.h"
#include "double_array.h"
#include "double_array2.h"
#include "mesh_qc.h"

static void mesh_qc_elasticity_coboundary_star_1_file_print_raw(
  FILE * out, const mesh_qc * m, const matrix_sparse * m_bd_1,
  const double * m_inner_1, const double * m_inner_0, double lambda, double mu)
{
  int m_elasticity_cbd_star_1_nonzero_max;
  matrix_sparse * m_elasticity_cbd_star_1;

  m_elasticity_cbd_star_1 =
    mesh_qc_elasticity_coboundary_star_1(m, m_bd_1, m_inner_1, m_inner_0, lambda, mu);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m_elasticity_cbd_star_1\n", stderr);
    return;
  }

  m_elasticity_cbd_star_1_nonzero_max
    = m_elasticity_cbd_star_1->cols_total[m_elasticity_cbd_star_1->cols];

  double_array_file_print(out, m_elasticity_cbd_star_1_nonzero_max,
                          m_elasticity_cbd_star_1->values, "--raw");

  matrix_sparse_free_shared(m_elasticity_cbd_star_1);
}

int main(int argc, char ** argv)
{
  int d;
  mesh_qc * m;
  matrix_sparse ** m_bd;
  double lambda, mu;
  double ** m_inner;
  FILE * m_file;

  if (argc != 5)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "number of command line arguments must be 5\n");
    errno = EINVAL;
    goto end;
  }

  lambda = double_string_scan(argv[1]);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan lambda\n", stderr);
    goto end;
  }

  mu = double_string_scan(argv[2]);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan mu\n", stderr);
    goto end;
  }

  m_file = fopen(argv[3], "r");
  if (errno)
  {
    fprintf(stderr, "cannot open mesh file %s: %s\n", argv[3], strerror(errno));
    goto end;
  }

  m = mesh_file_scan(m_file, "--raw");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan m\n", stderr);
    fclose(m_file);
    goto end;
  }
  d = m->dim;

  m->fc = mesh_fc(m);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m->fc\n", stderr);
    fclose(m_file);
    goto m_free;
  }

  m_bd = mesh_file_scan_boundary(m_file, m);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan m_bd\n", stderr);
    fclose(m_file);
    goto m_free;
  }

  fclose(m_file);

  m_inner = double_array2_file_scan_by_name(argv[4], d + 1, m->cn, "--raw");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan m_vol\n", stderr);
    goto m_bd_free;
  }

  mesh_qc_elasticity_coboundary_star_1_file_print_raw(
    stdout, m, m_bd[0], m_inner[1], m_inner[0], lambda, mu);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate and print result\n", stderr);
    goto m_inner_free;
  }

m_inner_free:
  double_array2_free(m_inner, d + 1);
m_bd_free:
  matrix_sparse_array_free(m_bd, d);
m_free:
  mesh_free(m);
end:
  return errno;
}
