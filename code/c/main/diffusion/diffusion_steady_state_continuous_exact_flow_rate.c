#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <dlfcn.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "mesh.h"

int main(int argc, char ** argv)
{
  void * lib_handle;
  char * error, * function_name, * lib_name, * m_format, * m_name,
       * output_format;
  int d;
  double * flow_rate;
  FILE * m_file;
  struct mesh * m;
  struct matrix_sparse * m_bd_1, * m_bd_2, * m_bd_3;
  struct matrix_sparse * m_cbd_2 = NULL;
  void (*function)(double *, const struct mesh *, const struct matrix_sparse *);

#define ARGC 6
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
  function_name = argv[4];
  output_format = argv[5];

  m_file = fopen(m_name, "r");
  if (m_file == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot open mesh file %s: %s\n", m_name, strerror(errno));
    goto end;
  }

  m = mesh_file_scan(m_file, m_format);
  if (m == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan mesh m from file %s in format %s\n",
      m_name, m_format);
    fclose(m_file);
    goto end;
  }
  d = m->dim;

  m_bd_1 = mesh_file_scan_boundary_p(m_file, m, 1);
  if (m_bd_1 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan m_bd_1 from file %s\n", m_name);
    fclose(m_file);
    goto m_free;
  }
  if (d == 3)
  {
    matrix_sparse_free(m_bd_1);

    m_bd_2 = mesh_file_scan_boundary_p(m_file, m, 2);
    if (m_bd_2 == NULL)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot scan m_bd_2 from file %s\n", m_name);
      fclose(m_file);
      goto m_free;
    }
    matrix_sparse_free(m_bd_2);

    m_bd_3 = mesh_file_scan_boundary_p(m_file, m, 3);
    if (m_bd_3 == NULL)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot scan m_bd_3 from file %s\n", m_name);
      fclose(m_file);
      goto m_free;
    }
    m_cbd_2 = matrix_sparse_transpose(m_bd_3);
    if (m_cbd_2 == NULL)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot calculate m_cbd_2 %s\n", m_name);
      matrix_sparse_free(m_bd_3);
      fclose(m_file);
      goto m_free;
    }
    matrix_sparse_free(m_bd_3);
    m_bd_1 = m_cbd_2;
  }
  fclose(m_file);

  lib_handle = dlopen(lib_name, RTLD_LAZY);
  if (lib_handle == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot open dynamic library %s\n", lib_name);
    goto m_bd_1_free;
  }
  /* clear any existing errors */
  dlerror();

  *(void **) (&function) = dlsym(lib_handle, function_name);
  error = dlerror();
  if (error)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "%s\n", error);
    errno = 1;
    goto lib_close;
  }

  flow_rate = (double *) malloc(sizeof(double) * m->cn[d - 1]);
  if (flow_rate == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m->cn[d - 1], "flow_rate");
    goto lib_close;
  }

  if (d == 2)
    function(flow_rate, m, m_bd_1);
  else /* d == 3 */
    function(flow_rate, m, m_cbd_2);
  double_array_file_print(stdout, m->cn[d - 1], flow_rate, output_format);

  free(flow_rate);
lib_close:
  dlclose(lib_handle);
m_bd_1_free:
  matrix_sparse_free(m_bd_1);
m_free:
  mesh_free(m);
end:
  return errno;
}
