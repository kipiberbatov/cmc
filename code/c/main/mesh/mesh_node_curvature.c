#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "mesh.h"

static void mesh_node_curvature_file_print_raw(FILE * out, const mesh * m)
{
  double * result;

  result = mesh_node_curvature(m);
  if (result == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate result\n", stderr);
    return;
  }
  double_array_file_print(out, m->cn[0], result, "--raw");
  free(result);
}

int main(void)
{
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

  m->fc = mesh_fc(m);
  if (m->fc == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m->fc\n", stderr);
    goto m_free;
  }
  mesh_node_curvature_file_print_raw(out, m);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate and print node curvature\n", stderr);
    goto m_free;
  }

m_free:
  mesh_free(m);
end:
  return errno;
}
