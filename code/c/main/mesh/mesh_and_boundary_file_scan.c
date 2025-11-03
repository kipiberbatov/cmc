#include <errno.h>
#include <string.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "cmc_command_line.h"
#include "mesh_and_boundary.h"

int main(int argc, char ** argv)
{
  int d, p, size, status, total_options;
  char * m_format, * m_name;
  double ** bd;
  FILE * m_and_bd_file;
  mesh * m;
  mesh_and_boundary * m_and_bd;
  jagged1 m_cfn_pp1_p;

  cmc_command_line option_mesh_format, positional_argument_mesh;

  cmc_command_line *(options[]) =
  {
    &option_mesh_format,
    &positional_argument_mesh
  };

  cmc_command_line_set_option_string(
    &option_mesh_format, &m_format, "--mesh-format", "--raw");

  cmc_command_line_set_option_string(
    &positional_argument_mesh, &m_name, NULL, NULL);

  total_options = (int) (sizeof(options) / sizeof(*options));
  status = 0;
  cmc_command_line_parse(options, &status, total_options, argc, argv);
  if (status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot parse command line options\n", stderr);
    return status;
  }

  m_and_bd_file = fopen(m_name, "r");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open mesh file %s%s%s for reading:%s\n",
      color_variable, m_format, color_none, strerror(errno));
    return errno;
  }

  m_and_bd = mesh_and_boundary_file_scan(m_and_bd_file, m_format);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh and boundary in format %s%s%s\n",
      color_variable, m_format, color_none);
    fclose(m_and_bd_file);
    return errno;
  }
  fclose(m_and_bd_file);

  m = m_and_bd->_mesh;
  bd = m_and_bd->boundary;
  d = m->dim;
  mesh_file_print(stdout, m, "--raw");
  for (p = 0; p < d; ++p)
  {
    mesh_cfn_part2(&m_cfn_pp1_p, m, p + 1, p);
    size = jagged1_total_sum(&m_cfn_pp1_p);
    double_array_file_print(stdout, size, bd[p], "--raw");
  }
  mesh_and_boundary_free(m_and_bd);
  return 0;
}
