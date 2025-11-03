#include <errno.h>

#include "cmc_error_message.h"
#include "forman.h"

int main(int argc, char ** argv)
{
  char * m_format, * m_name, * new_coordinates_format, * output_format;
  mesh * m, * m_forman;

  if (argc != 5)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "number of command line arguments should be 5; instead it is %d\n", argc);
    errno = EINVAL;
    goto end;
  }

  m_format = argv[1];
  m_name = argv[2];
  new_coordinates_format = argv[3];
  output_format = argv[4];

  m = mesh_file_scan_by_name(m_name, m_format);
  if (m == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh m in from file %s in fromat %s\n",
      m_name, m_format);
    goto end;
  }

  m_forman = forman(m, new_coordinates_format);
  if (m_forman == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot calculate m_forman in new coordinates format %s\n",
      new_coordinates_format);
    goto m_free;
  }

  mesh_file_print(stdout, m_forman, output_format);

  mesh_free(m_forman);
m_free:
  mesh_free(m);
end:
  return errno;
}
