#include <errno.h>
#include <stdlib.h>

#include <dlfcn.h>

#include "cmc_error_message.h"
#include "diffusion_steady_state_discrete_primal_strong.h"
#include "mesh.h"

int main(int argc, char ** argv)
{
  char * data_continuous_name, * error, * lib_name, * m_format, * m_name;
  void * lib_handle;
  struct mesh * m;
  const struct diffusion_steady_state_continuous * data_continuous;
  struct diffusion_steady_state_discrete_primal_strong * data_discrete;

#define ARGC 5
  if (argc != ARGC)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_number_of_command_line_arguments_mismatch(ARGC, argc);
    errno = EINVAL;
    goto end;
  }

  m_format = argv[1];
  m_name = argv[2];
  lib_name = argv[3];
  data_continuous_name = argv[4];

  m = mesh_file_scan_by_name(m_name, m_format);
  if (m == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh m from file %s in format %s\n", m_name, m_format);
    goto end;
  }

  lib_handle = dlopen(lib_name, RTLD_LAZY);
  if (lib_handle == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot open dynamic library %s\n", lib_name);
    goto m_free;
  }
  /* clear any existing errors */
  dlerror();

  *(const void **) (&data_continuous) = dlsym(lib_handle, data_continuous_name);
  error = dlerror();
  if (error)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "%s\n", error);
    goto lib_close;
  }

  data_discrete = diffusion_steady_state_discrete_primal_strong_from_continuous(
    m, data_continuous);
  if (data_discrete == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot discretize continuous data %s\n", stderr);
    goto lib_close;
  }

  diffusion_steady_state_discrete_primal_strong_file_print_raw(
    stdout, data_discrete);

  diffusion_steady_state_discrete_primal_strong_free(data_discrete);
lib_close:
  dlclose(lib_handle);
m_free:
  mesh_free(m);
end:
  return errno;
}
