#include <errno.h>
#include <stdlib.h>

#include "cmc_dynamic_library.h"

#include "cmc_error_message.h"
#include "double_array.h"
#include "mesh.h"

int main(int argc, char ** argv)
{
  void * lib_handle;
  char * error, * function_name, * lib_name, * m_format, * m_name,
       * output_format;
  double * potential;
  struct mesh * m;
  void (*function)(double *, const struct mesh *);

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

  *(void **) (&function) = cmc_dynamic_library_get_symbol_address(
    lib_handle, function_name);
  error = cmc_dynamic_library_error();
  if (error)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "%s\n", error);
    goto lib_close;
  }

  potential = (double *) malloc(sizeof(double) * m->cn[0]);
  if (potential == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m->cn[0], "potential");
    goto lib_close;
  }

  function(potential, m);
  double_array_file_print(stdout, m->cn[0], potential, output_format);

  free(potential);
lib_close:
  cmc_dynamic_library_close(lib_handle);
m_free:
  mesh_free(m);
end:
  return errno;
}
