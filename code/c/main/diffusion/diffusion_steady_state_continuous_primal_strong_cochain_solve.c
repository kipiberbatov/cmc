#include <errno.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "cmc_dynamic_library.h"

#include "cmc_error_message.h"
#include "double_array.h"
#include "diffusion_steady_state_continuous.h"
#include "int.h"
#include "mesh.h"

int main(int argc, char ** argv)
{
  void * lib_handle;
  char * error, * data_name, * lib_name, * m_cbd_0_name, * m_cbd_star_1_name,
       * m_format, * m_name;
  double * result;
  FILE * m_cbd_star_1_file;
  struct mesh * m;
  struct matrix_sparse * m_cbd_0, * m_cbd_star_1;
  const struct diffusion_steady_state_continuous * data;

  if (argc != 7)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("the number of command-line arguments must be 8\n", stderr);
    errno = EINVAL;
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

  m_cbd_0_name = argv[3];

  m_cbd_0 = matrix_sparse_file_scan_by_name(m_cbd_0_name, "--raw");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan m_cbd_0\n", stderr);
    goto m_free;
  }

  m_cbd_star_1_name = argv[4];

  m_cbd_star_1_file = fopen(m_cbd_star_1_name, "r");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open file %s: %s\n",
      m_cbd_star_1_name, strerror(errno));
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

  lib_name = argv[5];
  lib_handle = cmc_dynamic_library_open(lib_name);
  if (!lib_handle)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot open libshared\n", stderr);
    goto m_cbd_star_1_free;
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

  result = diffusion_steady_state_continuous_primal_strong_cochain_solve(
    m, m_cbd_0, m_cbd_star_1, data);
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
m_cbd_star_1_free:
  matrix_sparse_free(m_cbd_star_1);
m_cbd_0_free:
  matrix_sparse_free(m_cbd_0);
m_free:
  mesh_free(m);
end:
  return errno;
}
