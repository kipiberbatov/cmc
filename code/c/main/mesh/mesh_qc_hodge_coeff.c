#include <errno.h>

#include "cmc_error_message.h"
#include "mesh_qc.h"

static void mesh_qc_hodge_coeff_file_print_raw(FILE * out, const mesh * m)
{
  int i, m_dim, p;
  int * m_cn;

  m_dim = m->dim;
  m_cn = m->cn;
  for (p = 0; p <= m_dim; ++p)
  {
    for (i = 0; i < m_cn[p] - 1; ++i)
      fprintf(out, "%g ", 1.);
    fprintf(out, "%g\n", 1.);
  }
}

int main(void)
{
  mesh_qc * m;
  FILE * in, * out;

  out = stdout;
  in = stdin;
  m = mesh_file_scan(in, "--raw");
  if (m == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan mesh m in format --raw\n", stderr);
    return errno;
  }
  mesh_qc_hodge_coeff_file_print_raw(out, m);
  mesh_free(m);
  return 0;
}
