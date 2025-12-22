#include <errno.h>
#include <stdlib.h>

#include "cmc_dynamic_library.h"

#include "cmc_error_message.h"
#include "double_array2.h"
#include "diffusion_steady_state_discrete_mixed_weak.h"
#include "mesh.h"

int main(int argc, char ** argv)
{
  void * lib_handle;
  char * data_continuous_name, * error, * lib_name, * m_format, * m_name,
       * m_vol_format, * m_vol_name;
  int d;
  int * m_cn;
  double ** m_vol;
  struct mesh * m;
  const struct diffusion_steady_state_continuous * data_continuous;
  struct diffusion_steady_state_discrete_mixed_weak * data_discrete;

#define ARGC 7
  if (argc != ARGC)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_number_of_command_line_arguments_mismatch(ARGC, argc);
    errno = EINVAL;
    goto end;
  }

  m_format = argv[1];
  m_name = argv[2];
  m_vol_format = argv[3];
  m_vol_name = argv[4];
  lib_name = argv[5];
  data_continuous_name = argv[6];

  m = mesh_file_scan_by_name(m_name, m_format);
  if (m == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh m from file %s in format %s\n", m_name, m_format);
    goto end;
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
    goto m_free;
  }

  lib_handle = cmc_dynamic_library_open(lib_name);
  if (lib_handle == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot open dynamic library %s\n", lib_name);
    goto m_vol_free;
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

  data_discrete = diffusion_steady_state_discrete_mixed_weak_from_continuous(
    m, m_vol[d - 1], m_vol[d], data_continuous);
  if (data_discrete == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot discretize continuous data %s\n", stderr);
    goto lib_close;
  }

  diffusion_steady_state_discrete_mixed_weak_file_print_raw(
    stdout, data_discrete);

  diffusion_steady_state_discrete_mixed_weak_free(data_discrete);
lib_close:
  cmc_dynamic_library_close(lib_handle);
m_vol_free:
  double_array2_free(m_vol, d + 1);
m_free:
  mesh_free(m);
end:
  return errno;
}
