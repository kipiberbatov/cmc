#include <errno.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include <dlfcn.h>

#include "cmc_error_message.h"
#include "diffusion_transient_continuous.h"
#include "double.h"
#include "double_array_sequence_dynamic.h"
#include "int.h"
#include "mesh.h"

int main(int argc, char ** argv)
{
  void * lib_handle;
  char * data_name, * error, * lib_name, * m_cbd_0_name, * m_cbd_star_1_name,
       * m_format, * m_name, * time_step_name;
  double time_step;
  FILE * m_cbd_star_1_file;
  struct double_array_sequence_dynamic * result;
  struct matrix_sparse * m_cbd_0, * m_cbd_star_1;
  struct mesh * m;
  const struct diffusion_transient_continuous * data;

#define ARGC 8
  if (argc != ARGC)
  {
    errno = EINVAL;
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_number_of_command_line_arguments_mismatch(ARGC, argc);
    goto end;
  }

  m_format = argv[1];
  m_name = argv[2];
  m_cbd_0_name = argv[3];
  m_cbd_star_1_name = argv[4];
  lib_name = argv[5];
  data_name = argv[6];
  time_step_name = argv[7];

  m = mesh_file_scan_by_name(m_name, m_format);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh m from file %s%s%s in format %s%s%s\n",
      color_variable, m_name, color_none,
      color_variable, m_format, color_none);
    goto end;
  }

  m->fc = mesh_fc(m);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m->fc\n", stderr);
    goto m_free;
  }

  m_cbd_0 = matrix_sparse_file_scan_by_name(m_cbd_0_name, "--raw");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan m_cbd_0 from file %s%s%s in format %s%s%s\n",
      color_variable, m_cbd_0_name, color_none,
      color_variable, "--raw", color_none);
    goto m_free;
  }

  m_cbd_star_1_file = fopen(m_cbd_star_1_name, "r");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot open file %s%s%s: %s%s%s\n",
      color_variable, m_cbd_star_1_name, color_none,
      color_stdlib, strerror(errno), color_none);
    goto m_cbd_0_free;
  }
  m_cbd_star_1 = mesh_file_scan_boundary_p(m_cbd_star_1_file, m, 1);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan m_cbd_star_1\n", stderr);
    fclose(m_cbd_star_1_file);
    goto m_cbd_0_free;
  }
  fclose(m_cbd_star_1_file);

  lib_handle = dlopen(lib_name, RTLD_LAZY);
  if (!lib_handle)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open dynamic library %s%s:%s %s%s%s\n",
      color_variable, lib_name, color_none,
      color_stdlib, dlerror(), color_none);
    goto m_cbd_star_1_free;
  }
  /* clear any existing errors */
  dlerror();

  *(const void **) (&data) = dlsym(lib_handle, data_name);
  error = dlerror();
  if (error)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot resolve data %s%s%s from dynamic library %s%s%s: %s%s%s\n",
      color_variable, data_name, color_none,
      color_variable, lib_name, color_none,
      color_stdlib, error, color_none);
    goto lib_close;
  }

  time_step = double_string_scan(time_step_name);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan time_step from string %s%s%s\n",
      color_variable, time_step_name, color_none);
    goto lib_close;
  }

  result =
  diffusion_transient_continuous_primal_strong_cochain_solve_trapezoidal_to_steady_state(
    m, m_cbd_0, m_cbd_star_1, data, time_step, 0.004);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate result\n", stderr);
    goto lib_close;
  }
  double_array_sequence_dynamic_file_print(stdout, result);

  double_array_sequence_dynamic_free(result);
lib_close:
  dlclose(lib_handle);
m_cbd_star_1_free:
  matrix_sparse_free(m_cbd_star_1);
m_cbd_0_free:
  matrix_sparse_free(m_cbd_0);
m_free:
  mesh_free(m);
end:
  return errno;
}
