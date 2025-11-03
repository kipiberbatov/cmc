#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "double_array2.h"
#include "mesh_qc.h"

static void mesh_qc_hodge_file_print_raw(
  FILE * out, const mesh_qc * m, matrix_sparse ** m_bd,
  double ** m_inner, double ** m_coeff)
{
  int d, p, q;
  matrix_sparse * m_hodge_p;

  d = m->dim;
  for (p = 0; p <= d; ++p)
  {
    q = d - p;
    m_hodge_p = mesh_qc_hodge_p(m, m_bd, p, m_inner[q], m_coeff[q]);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot calculate m_hodge[%d]\n", p);
      return;
    }
    matrix_sparse_file_print(out, m_hodge_p, "--raw");
    if (p != d)
      fputc('\n', out);
    free(m_hodge_p);
  }
}

int main(int argc, char ** argv)
{
  int d;
  mesh_qc * m;
  matrix_sparse ** m_bd;
  double ** m_inner, ** m_coeff;
  FILE * m_file;

  if (argc != 4)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "Number of command line arguments must be 4\n");
    errno = EINVAL;
    return errno;
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

  m_coeff = double_array2_file_scan_by_name(argv[3], d + 1, m->cn, "--raw");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan m_coeff\n", stderr);
    goto m_inner_free;
  }

  mesh_qc_hodge_file_print_raw(stdout, m, m_bd, m_inner, m_coeff);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate and print m_hodge\n", stderr);
    goto m_coeff_free;
  }

m_coeff_free:
  double_array2_free(m_coeff, d + 1);
m_inner_free:
  double_array2_free(m_inner, d + 1);
m_bd_free:
  matrix_sparse_array_free(m_bd, d);
m_free:
  mesh_free(m);
end:
  return errno;
}
