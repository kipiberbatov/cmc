#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "cmc_dynamic_library.h"

#include "cmc_error_message.h"
#include "double_array2.h"
#include "diffusion_transient_discrete_mixed_weak.h"
#include "cmc_command_line.h"
#include "mesh.h"

int main(int argc, char ** argv)
{
  char * data_continuous_name, * error, * lib_name, * m_format, * m_name,
       * m_hodge_name, * m_hodge_format, * m_vol_format, * m_vol_name;
  int d, size, status;
  int * m_cn;
  double ** m_vol;
  void * lib_handle;
  FILE * m_file;
  struct matrix_sparse * m_bd_1;
  struct matrix_sparse ** m_hodge;
  struct mesh * m;  const struct diffusion_transient_continuous * data_continuous;
  struct diffusion_transient_discrete_mixed_weak * data_discrete;

  cmc_command_line no_positional_arguments, option_input_data, option_lib,
                    option_mesh, option_mesh_format, option_mesh_hodge,
                    option_mesh_hodge_format, option_mesh_vol,
                    option_mesh_vol_format;

  cmc_command_line *(options[]) =
  {
    &option_mesh_format,
    &option_mesh,
    &option_mesh_hodge_format,
    &option_mesh_hodge,
    &option_mesh_vol_format,
    &option_mesh_vol,
    &option_input_data,
    &option_lib,
    &no_positional_arguments
  };

  cmc_command_line_set_option_string(&option_mesh_format, &m_format,
    "--mesh-format", "--raw");

  cmc_command_line_set_option_string(&option_mesh, &m_name, "--mesh", NULL);

  cmc_command_line_set_option_string(&option_mesh_hodge_format,
    &m_hodge_format, "--mesh-hodge-star-format", "--raw");

  cmc_command_line_set_option_string(&option_mesh_hodge, &m_hodge_name,
    "--mesh-hodge-star", NULL);

  cmc_command_line_set_option_string(
    &option_mesh_vol_format, &m_vol_format, "--mesh-volumes-format", "--raw");

  cmc_command_line_set_option_string(
    &option_mesh_vol, &m_vol_name, "--mesh-volumes", NULL);

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

  m_file = fopen(m_name, "r");
  if (m_file == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open mesh file %s: %s\n",
      m_name, strerror(errno));
    goto end;
  }

  m = mesh_file_scan(m_file, m_format);
  if (m == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh m from file %s in format %s\n",
      m_name, m_format);
    fclose(m_file);
    goto end;
  }

  m_bd_1 = mesh_file_scan_boundary_p(m_file, m, 1);
  if (m_bd_1 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh m_bd_1 from file %s in format %s\n",
      m_name, m_format);
    fclose(m_file);
    goto m_free;
  }
  fclose(m_file);

  m->fc = mesh_fc(m);
  if (m->fc == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m->fc\n", stderr);
    goto m_bd_1_free;
  }

  d = m->dim;
  m_cn = m->cn;

  m_vol = double_array2_file_scan_by_name(
    m_vol_name, d + 1, m_cn, m_vol_format);
  if (m_vol == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan measures m_vol from file %s in format %s\n",
      m_vol_name, m_vol_format);
    goto m_bd_1_free;
  }

  m_hodge = matrix_sparse_array_file_scan_by_name(
    m_hodge_name, d + 1, m_hodge_format);
  if (m_hodge == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan measures m_hodge from file %s in format %s\n",
      m_hodge_name, m_hodge_format);
    goto m_vol_free;
  }

  lib_handle = cmc_dynamic_library_open(lib_name);
  error = cmc_dynamic_library_error();
  if (error)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "%s\n", error);
    goto m_hodge_free;
  }

  *(const void **) (&data_continuous) = cmc_dynamic_library_get_symbol_address(
    lib_handle, data_continuous_name);
  error = cmc_dynamic_library_error();
  if (error)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "%s\n", error);
    goto lib_close;
  }

  data_discrete = diffusion_transient_discrete_mixed_weak_from_continuous(
    m, m_vol[d - 1], m_vol[d], m_bd_1, m_hodge[1], data_continuous);
  if (data_discrete == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot discretize continuous data %s\n", stderr);
    goto lib_close;
  }

  diffusion_transient_discrete_mixed_weak_file_print_raw(
    stdout, data_discrete);

  diffusion_transient_discrete_mixed_weak_free(data_discrete);
lib_close:
  cmc_dynamic_library_close(lib_handle);
m_hodge_free:
  matrix_sparse_array_free(m_hodge, d + 1);
m_vol_free:
  double_array2_free(m_vol, d + 1);
m_bd_1_free:
  matrix_sparse_free(m_bd_1);
m_free:
  mesh_free(m);
end:
  return errno;
}
