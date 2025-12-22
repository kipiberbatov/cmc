#include <errno.h>
#include <stdlib.h>

#include "cmc_dynamic_library.h"

#include "cmc_error_message.h"
#include "double_array.h"
#include "double_array2.h"
#include "diffusion_steady_state_continuous.h"
#include "mesh.h"

int main(int argc, char ** argv)
{
  void * lib_handle;
  char * error, * data_name, * lib_name, * m_format, * m_inner_name, * m_name,
       * m_vol_name;
  double * result;
  double ** m_inner, ** m_vol;
  struct mesh * m;
  const struct diffusion_steady_state_continuous * data;

  if (argc != 7)
  {
    errno = EINVAL;
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("the number of command-line arguments must be 8\n", stderr);
    goto end;
  }

  m_format = argv[1];
  m_name = argv[2];
  m = mesh_file_scan_by_name(m_name, m_format);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan m\n", stderr);
    goto end;
  }

  m->fc = mesh_fc(m);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m->fc\n", stderr);
    goto m_free;
  }

  m_vol_name = argv[3];
  m_vol = double_array2_file_scan_by_name(
    m_vol_name, m->dim + 1, m->cn, "--raw");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan m_vol\n", stderr);
    goto m_free;
  }

  m_inner_name = argv[4];
  m_inner = double_array2_file_scan_by_name(
    m_inner_name, m->dim + 1, m->cn, "--raw");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan m_vol\n", stderr);
    goto m_vol_free;
  }

  lib_name = argv[5];
  lib_handle = cmc_dynamic_library_open(lib_name);
  if (!lib_handle)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot open libshared\n", stderr);
    goto m_inner_free;
  }
  /* clear any existing errors */
  cmc_dynamic_library_error();

  data_name = argv[6];
  *(const void **) (&data) = cmc_dynamic_library_get_symbol_address(
    lib_handle, data_name);
  error = cmc_dynamic_library_error();
  if (error)
  {
    fputs(error, stderr);
    fputs("\n", stderr);
    goto lib_close;
  }

  result = diffusion_steady_state_continuous_primal_weak_cochain_solve(
    m, m_vol[m->dim - 1], m_vol[m->dim], m_inner[1], data);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate result\n", stderr);
    goto lib_close;
  }

  double_array_file_print(stdout, m->cn[0], result, "--raw");

  free(result);
lib_close:
  cmc_dynamic_library_close(lib_handle);
m_inner_free:
  double_array2_free(m_inner, m->dim + 1);
m_vol_free:
  double_array2_free(m_vol, m->dim + 1);
m_free:
  mesh_free(m);
end:
  return errno;
}
