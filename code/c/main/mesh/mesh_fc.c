#include <errno.h>

#include "cmc_error_message.h"
#include "mesh.h"

int main(void)
{
  mesh * m;
  FILE * out, * in;

  out = stdout;
  in = stdin;

  m = mesh_file_scan(in, "--raw");
  if (m == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan mesh m in format --raw\n", stderr);
    goto end;
  }

  m->fc = mesh_fc(m);
  if (m->fc == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m->fc\n", stderr);
    goto m_free;
  }

  jagged4_file_print(out, m->fc, "--raw");

m_free:
  mesh_free(m);
end:
  return errno;
}
