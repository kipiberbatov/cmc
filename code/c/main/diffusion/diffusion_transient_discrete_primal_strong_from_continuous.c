#include <errno.h>
#include <stdlib.h>

#include "cmc_dynamic_library.h"

#include "cmc_error_message.h"
#include "diffusion_transient_discrete_primal_strong.h"
#include "cmc_command_line.h"
#include "mesh.h"

int main(int argc, char ** argv)
{
  void * lib_handle;
  char * data_continuous_name, * error, * lib_name, * m_format, * m_name;
  int size, status;
  struct mesh * m;
  const struct diffusion_transient_continuous * data_continuous;
  struct diffusion_transient_discrete_primal_strong * data_discrete;

  cmc_command_line no_positional_arguments, option_input_data, option_lib,
                    option_mesh, option_mesh_format;

  cmc_command_line *(options[]) =
  {
    &option_mesh_format,
    &option_mesh,
    &option_input_data,
    &option_lib,
    &no_positional_arguments
  };

  cmc_command_line_set_option_string(
    &option_mesh_format, &m_format, "--mesh-format", "--raw");

  cmc_command_line_set_option_string(&option_mesh, &m_name, "--mesh", NULL);

  cmc_command_line_set_option_string(
    &option_input_data, &data_continuous_name, "--input-data", NULL);

  cmc_command_line_set_option_string(
    &option_lib, &lib_name, "--dynamic-library", NULL);

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
      "cannot scan mesh m from file %s in format %s\n", m_name, m_format);
    goto end;
  }

  lib_handle = cmc_dynamic_library_open(lib_name);
  if (lib_handle == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot open dynamic library %s\n", lib_name);
    goto m_free;
  }
  /* clear any existing errors */
  cmc_dynamic_library_error();

  *(const void **) (&data_continuous) = cmc_dynamic_library_get_symbol_address(
    lib_handle, data_continuous_name);
  error = cmc_dynamic_library_error();
  if (error)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "%s\n", error);
    goto lib_close;
  }

  data_discrete = diffusion_transient_discrete_primal_strong_from_continuous(
    m, data_continuous);
  if (data_discrete == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot discretize continuous data %s\n", stderr);
    goto lib_close;
  }

  diffusion_transient_discrete_primal_strong_file_print_raw(
    stdout, data_discrete);

  diffusion_transient_discrete_primal_strong_free(data_discrete);
lib_close:
  cmc_dynamic_library_close(lib_handle);
m_free:
  mesh_free(m);
end:
  return errno;
}
