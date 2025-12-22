#include "cmc_dynamic_library.h"

#include "double_array2.h"
#include "diffusion_steady_state_discrete_file_print_raw.h"
#include "diffusion_steady_state_discrete_free.h"
#include "diffusion_steady_state_discrete_from_continuous.h"
#include "cmc_command_line.h"
#include "cmc_error_message.h"
#include "cmc_memory.h"
#include "mesh.h"

struct diffusion_steady_state_discrete_pre_processing;

int main(int argc, char ** argv)
{
  void * lib_handle;
  char * data_continuous_name, * error, * lib_name, * m_format, * m_name,
       * m_vol_format, * m_vol_name, * output_format, * output_name,
       * pre_processing_name;
  int d, size, status;
  int * m_cn;
  double ** m_vol;
  FILE * output;
  struct jagged1 * m_boundary_dm1;
  struct mesh * m;
  const struct diffusion_steady_state_continuous * data_continuous;
  struct diffusion_steady_state_discrete * data_discrete;
  const struct diffusion_steady_state_discrete_pre_processing * pre_processing;

  cmc_command_line option_data_continuous_name, option_lib_name, 
    option_mesh_format, option_mesh_name, option_no_positional_arguments,
    option_pre_processing_name, option_m_vol_format, option_m_vol_name,
    option_output_format, option_output_name;

  cmc_command_line *(options[]) =
  {
    &option_mesh_format,
    &option_mesh_name,
    &option_m_vol_format,
    &option_m_vol_name,
    &option_lib_name,
    &option_data_continuous_name,
    &option_pre_processing_name,
    &option_output_format,
    &option_output_name,
    &option_no_positional_arguments
  };

  cmc_command_line_set_option_string(
    &option_mesh_format, &m_format, "--mesh-format", "--raw");

  cmc_command_line_set_option_string(
    &option_mesh_name, &m_name, "--mesh", NULL);

  cmc_command_line_set_option_string(
    &option_m_vol_format, &m_vol_format, "--mesh-measures-format", "--raw");

  cmc_command_line_set_option_string(
    &option_m_vol_name, &m_vol_name, "--mesh-measures", NULL);

  cmc_command_line_set_option_string(
    &option_lib_name, &lib_name, "--dynamic-library", NULL);

  cmc_command_line_set_option_string(
    &option_data_continuous_name, &data_continuous_name, "--data", NULL);

  cmc_command_line_set_option_string(
    &option_pre_processing_name, &pre_processing_name,
    "--pre-processing", NULL);

  cmc_command_line_set_option_string(
    &option_output_format, &output_format, "--output-format", "--raw");

  cmc_command_line_set_option_string(
    &option_output_name, &output_name, "--output", NULL);
  option_output_name.minimal_number_of_arguments = 0;

  /* there are no positional arguments */
  cmc_command_line_set_option_no_arguments(
    &option_no_positional_arguments, NULL, NULL, NULL);

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
    cmc_error_message_cannot_calculate("m");
    status = 1;
    goto end;
  }

  d = m->dim;
  m_cn = m->cn;

  m->fc = mesh_fc(m);
  if (m->fc == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_cannot_calculate("m->fc");
    status = 1;
    goto m_free;
  }

  mesh_boundary_dm1(&m_boundary_dm1, &status, m);
  if (status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_cannot_calculate("m_boundary_dm1");
    goto m_free;
  }

  m_vol = double_array2_file_scan_by_name(
    m_vol_name, d + 1, m_cn, m_vol_format);
  if (m_vol == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_cannot_calculate("m_vol");
    status = 1;
    goto m_free;
  }

  lib_handle = cmc_dynamic_library_open(lib_name);
  if (lib_handle == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot open dynamic library %s\n", lib_name);
    status = 1;
    goto m_vol_free;
  }
  /* clear any existing errors */
  cmc_dynamic_library_error();

  *(const void **) (&data_continuous) = cmc_dynamic_library_get_symbol_address(lib_handle, data_continuous_name);
  error = cmc_dynamic_library_error();
  if (error)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "%s\n", error);
    status = 1;
    goto lib_close;
  }

  *(const void **) (&pre_processing) = cmc_dynamic_library_get_symbol_address(
    lib_handle, pre_processing_name);
  error = cmc_dynamic_library_error();
  if (error)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "%s\n", error);
    status = 1;
    goto lib_close;
  }

  diffusion_steady_state_discrete_from_continuous(&data_discrete, &status,
    m, m_boundary_dm1, m_vol[d - 1], m_vol[d], data_continuous, pre_processing);
  if (data_discrete == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_cannot_calculate("data_discrete");
    goto lib_close;
  }

  if (output_name == NULL)
    diffusion_steady_state_discrete_file_print_raw(stdout, data_discrete);
  else
  {
    output = fopen(output_name, "w");
    if (output == NULL)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot open file %s for writing \n", output_name);
      status = 1;
      goto data_discrete_free;
    }
    diffusion_steady_state_discrete_file_print_raw(output, data_discrete);
    fclose(output);
  }

data_discrete_free:
  diffusion_steady_state_discrete_free(data_discrete);
lib_close:
  cmc_dynamic_library_close(lib_handle);
m_vol_free:
  double_array2_free(m_vol, d + 1);
m_free:
  mesh_free(m);
end:
  return status;
}
