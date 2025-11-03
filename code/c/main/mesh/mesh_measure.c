#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "mesh.h"

int main(void)
{
  int ind, m_dim, p;
  int * m_cn;
  double * m_vol;
  mesh * m;
  FILE * in, * out;

  out = stdout;
  in = stdin;

  m = mesh_file_scan(in, "--raw");
  if (m == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan mesh m in format --raw\n", stderr);
    goto end;
  }

  m_dim = m->dim;
  m_cn = m->cn;

  m_vol = mesh_measure(m);
  if (m_vol == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot find m_vol\n", stderr);
    goto m_free;
  }

  ind = 0;
  for (p = 0; p <= m_dim; ++p)
  {
    double_array_file_print(out, m_cn[p], m_vol + ind, "--raw");
    ind += m_cn[p];
  }

  free(m_vol);
m_free:
  mesh_free(m);
end:
  return errno;
}
