#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <dlfcn.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "double_matrix.h"
#include "diffusion_transient_continuous.h"
#include "diffusion_transient_discrete_dual_flow_rate_from_potential.h"
#include "int.h"
#include "unsigned_approximation.h"

int main(int argc, char ** argv)
{
  void * lib_handle;
  char * data_name, * error, * dual_flow_rate_format, * lib_name, * m_format,
       * m_name, * m_bd_1_name, * number_of_steps_name, * potential_format,
       * potential_name;
  int number_of_steps;
  double * dual_flow_rate, * kappa_1, * potential;
  FILE * m_file, * m_bd_1_file;
  struct mesh * m;
  struct matrix_sparse * m_bd_1;
  const struct diffusion_transient_continuous * data;

#define ARGC 10
  if (argc != ARGC)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_number_of_command_line_arguments_mismatch(ARGC, argc);
    return EINVAL;
  }

  m_format = argv[1];
  m_name = argv[2];
  m_bd_1_name = argv[3];
  lib_name = argv[4];
  data_name = argv[5];
  number_of_steps_name = argv[6];
  potential_format = argv[7];
  potential_name = argv[8];
  dual_flow_rate_format = argv[9];

  m_file = fopen(m_name, "r");
  if (m_file == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open mesh file %s for reading: %s\n",
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

  if (m_bd_1_name[1] == 0 && m_bd_1_name[0] == '-')
  {
    m_bd_1 = mesh_file_scan_boundary_p(m_file, m, 1);
    if (m_bd_1 == NULL)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr,
        "cannot scan boundary matrix m_bd_1 from mesh file %s\n",
        m_name);
      goto m_free;
    }
    fclose(m_file);
  }
  else
  {
    fclose(m_file);
    m_bd_1_file = fopen(m_bd_1_name, "r");
    if (m_bd_1_file == NULL)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr,
        "cannot open mesh file %s for reading: %s\n",
        m_bd_1_name, strerror(errno));
      goto m_free;
    }
    m_bd_1 = mesh_file_scan_boundary_p(m_bd_1_file, m, 1);
    if (m_bd_1)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fputs("cannot scan sparse matrix m_bd_1\n", stderr);
      fclose(m_bd_1_file);
      goto m_free;
    }
    fclose(m_bd_1_file);
  }

  lib_handle = dlopen(lib_name, RTLD_LAZY);
  if (!lib_handle)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot open library %s\n", lib_name);
    goto m_bd_1_free;
  }
  /* clear any existing errors */
  dlerror();

  *(const void **) (&data) = dlsym(lib_handle, data_name);
  error = dlerror();
  if (error)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot read %s: %s\n", data_name, error);
    goto lib_close;
  }

  number_of_steps = int_string_scan(number_of_steps_name);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan number_of_steps\n", stderr);
    goto m_free;
  }

  potential = double_array_file_scan_by_name(
    potential_name, m->cn[0] * (number_of_steps + 1), potential_format);
  if (potential == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan potential from file %s in format %s\n",
      potential_name, potential_format);
    goto lib_close;
  }

  kappa_1 = (double *) malloc(sizeof(double) * m->cn[1]);
  if (kappa_1 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m->cn[1], "kappa_1");
    goto potential_free;
  }
  unsigned_approximation_of_scalar_field_on_1_cells(kappa_1, m, data->kappa_1);

  dual_flow_rate = (double *) malloc(
    sizeof(double) * m->cn[1] * (number_of_steps + 1));
  if (dual_flow_rate == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m->cn[1] * (number_of_steps + 1),
      "dual_flow_rate");
    goto kappa_1_free;
  }

  diffusion_transient_discrete_dual_flow_rate_from_potential(
    dual_flow_rate, m, m_bd_1, kappa_1, number_of_steps, potential);

  double_matrix_file_print(stdout,
    number_of_steps + 1, m->cn[1], dual_flow_rate, dual_flow_rate_format);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot print dual_flow_rate in format %s\n",
      dual_flow_rate_format);
  }

  free(dual_flow_rate);
kappa_1_free:
  free(kappa_1);
potential_free:
  free(potential);
lib_close:
  dlclose(lib_handle);
m_bd_1_free:
  matrix_sparse_free(m_bd_1);
m_free:
  mesh_free(m);
end:
  return errno;
}
