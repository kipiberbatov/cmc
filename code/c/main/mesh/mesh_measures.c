#include <errno.h>

#include "cmc_error_message.h"
#include "double_array2.h"
#include "mesh_qc.h"
#include "cmc_command_line.h"

int main(int argc, char ** argv)
{
  char * m_format, * m_name, * m_measures_name, * output_format;
  int size, status;
  double ** m_measures;
  mesh * m;

  cmc_command_line no_positional_arguments, option_mesh, option_mesh_format,
                    option_mesh_measures, option_output_format;

  cmc_command_line *(options[]) =
  {
    &option_mesh_format,
    &option_mesh,
    &option_mesh_measures,
    &option_output_format,
    &no_positional_arguments
  };

  cmc_command_line_set_option_string(
    &option_mesh_format, &m_format, "--mesh-format", "--raw");

  cmc_command_line_set_option_string(&option_mesh, &m_name, "--mesh", NULL);

  cmc_command_line_set_option_string(&option_mesh_measures, &m_measures_name,
    "--mesh-measures-function", "default");

  cmc_command_line_set_option_string(&option_output_format,
    &output_format, "--output-format", "raw");

  /* there are no positional arguments */
  cmc_command_line_set_option_no_arguments(
    &no_positional_arguments, NULL, NULL, NULL);

  size = (int) (sizeof(options) / sizeof(*options));
  status = 0;
  cmc_command_line_parse(options, &status, size, argc, argv);
  if (status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot parse command line options\n", stderr);
    return status;
  }

  m = mesh_file_scan_by_name(m_name, m_format);
  if (m == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh m from file %s in format %s\n",
      m_name, m_format);
    goto end;
  }

  m->fc = mesh_fc(m);
  if (m->fc == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m->fc\n", stderr);
    goto m_free;
  }

  mesh_measures(&m_measures, &status, m, m_measures_name);
  if (status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m_measures\n", stderr);
    goto m_free;
  }

  double_array2_file_print(stdout, &status,
    m->dim + 1, m->cn, m_measures, output_format);
  if (status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot print m_measures\n", stderr);
    goto m_measures_free;
  }

m_measures_free:
  double_array2_free(m_measures, m->dim);
m_free:
  mesh_free(m);
end:
  return errno;
}
