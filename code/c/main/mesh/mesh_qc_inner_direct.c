#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "double_array2.h"
#include "mesh_qc.h"
#include "vector_sparse.h"

static void mesh_qc_inner_direct_file_print_raw(
  FILE * out,
  const mesh_qc * m,
  double ** m_vol)
{
  int m_dim, p;
  int * m_cn;
  double * m_inner_p;

  m_dim = m->dim;
  m_cn = m->cn;
  for (p = 0; p <= m_dim; ++p)
  {
    m_inner_p = mesh_qc_inner_direct_p(m, p, m_vol[p], m_vol[m_dim - p]);
    if (errno)
    {
      fprintf(stderr,
        "mesh_qc_inner_direct_file_print: cannot calculate m_inner[%d]\n", p);
      return;
    }

    double_array_file_print(out, m_cn[p], m_inner_p, "--raw");
    if (p != m_dim)
      fputc('\n', out);

    free(m_inner_p);
  }
}

int main(int argc, char ** argv)
{
  mesh_qc * m;
  double ** m_vol;

  if (argc != 3)
  {
    errno = EINVAL;
    fprintf(stderr, "Number of command line arguments must be 3\n");
    goto end;
  }

  m = mesh_file_scan_by_name(argv[1], "--raw");
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

  m_vol = double_array2_file_scan_by_name(argv[2], m->dim + 1, m->cn, "--raw");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan m_vol\n", stderr);
    goto m_free;
  }

  mesh_qc_inner_direct_file_print_raw(stdout, m, m_vol);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot print m_inner\n", stderr);
    goto m_vol_free;
  }

m_vol_free:
  double_array2_free(m_vol, m->dim + 1);
m_free:
  mesh_free(m);
end:
  return errno;
}
