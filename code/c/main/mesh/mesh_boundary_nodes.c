#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "mesh.h"

int main(int argc, char ** argv)
{
  char * m_format, * m_name, * out_format;
  FILE * m_file;
  mesh * m;
  jagged1 * m_bd_nodes;

  if (argc != 4)
  {
    errno = EINVAL;
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("the number of command-line arguments must be 4\n", stderr);
    goto end;
  }

  m_name = argv[1];
  m_file = fopen(m_name, "r");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot open file %s: %s\n", m_name, strerror(errno));
    goto end;
  }

  m_format = argv[2];
  m = mesh_file_scan(m_file, m_format);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan m\n", stderr);
    fclose(m_file);
    goto end;
  }
  fclose(m_file);

  m->fc = mesh_fc(m);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m->fc\n", stderr);
    goto m_free;
  }

  out_format = argv[3];
  m_bd_nodes = mesh_boundary_nodes(m);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m_bd_nodes\n", stderr);
    goto m_free;
  }

  jagged1_file_print(stdout, m_bd_nodes, out_format);

  jagged1_free(m_bd_nodes);
m_free:
  mesh_free(m);
end:
  return errno;
}
