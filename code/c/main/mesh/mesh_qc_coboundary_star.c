#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "double_array2.h"
#include "mesh_qc.h"

static void mesh_qc_coboundary_star_file_print_raw(
  FILE * out, const mesh_qc * m, matrix_sparse ** m_bd, double ** m_inner)
{
  int m_cbd_star_p_nonzero_max, m_dim, p;
  matrix_sparse * m_cbd_star_p;

  m_dim = m->dim;
  for (p = 1; p <= m_dim; ++p)
  {
    m_cbd_star_p =
      mesh_qc_coboundary_star_p(m, p, m_bd[p - 1], m_inner[p], m_inner[p - 1]);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot calculate m_cbd_star[%d]\n", p);
      return;
    }

    m_cbd_star_p_nonzero_max = m_cbd_star_p->cols_total[m_cbd_star_p->cols];
    double_array_file_print(
      out, m_cbd_star_p_nonzero_max, m_cbd_star_p->values, "--raw");
    matrix_sparse_free_shared(m_cbd_star_p);
  }
}

int main(int argc, char ** argv)
{
  int d;
  mesh_qc * m;
  matrix_sparse ** m_bd;
  double ** m_inner;
  FILE * m_file;

  if (argc != 3)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "number of command line arguments must be 3\n");
    errno = EINVAL;
    goto end;
  }

  m_file = fopen(argv[1], "r");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot open mesh file %s: %s\n", argv[1], strerror(errno));
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

  m_inner = double_array2_file_scan_by_name(argv[2], d + 1, m->cn, "--raw");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan m_vol\n", stderr);
    goto m_bd_free;
  }

  mesh_qc_coboundary_star_file_print_raw(stdout, m, m_bd, m_inner);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot print m_inner\n", stderr);
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
