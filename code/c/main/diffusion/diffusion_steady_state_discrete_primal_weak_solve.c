#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <dlfcn.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "double_array2.h"
#include "diffusion_steady_state_discrete_primal_weak.h"
#include "mesh.h"

int main(int argc, char ** argv)
{
  char * data_name, * m_inner_format, * m_inner_name, * m_format, * m_name;
  int d;
  int * m_cn;
  double * potential;
  double ** m_inner;
  FILE * data_file;
  struct mesh * m;
  struct diffusion_steady_state_discrete_primal_weak * data;

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
  m_inner_format = argv[3];
  m_inner_name = argv[4];
  data_name = argv[5];

  m = mesh_file_scan_by_name(m_name, m_format);
  if (m == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh m from file %s in format %s\n", m_name, m_format);
    goto end;
  }

  m->fc = mesh_fc(m);
  if (m->fc == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m->fc\n", stderr);
    goto m_free;
  }

  d = m->dim;
  m_cn = m->cn;

  m_inner = double_array2_file_scan_by_name(
    m_inner_name, d + 1, m_cn, m_inner_format);
  if (m_inner == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan inner products from file %s in format %s\n",
      m_inner_name, m_inner_format);
    goto m_free;
  }

  data_file = fopen(data_name, "r");
  if (data_file == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open problem data file %s: %s\n", data_name, strerror(errno));
    goto m_inner_free;
  }
  data = diffusion_steady_state_discrete_primal_weak_file_scan_raw(data_file);
  if (data == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan problem data from file %s\n", data_name);
    fclose(data_file);
    goto m_inner_free;
  }
  fclose(data_file);

  potential = diffusion_steady_state_discrete_primal_weak_solve(
    m, m_inner[1], data);
  if (potential == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot find potential\n", stderr);
    goto data_free;
  }

  double_array_file_print(stdout, m_cn[0], potential, "--raw");

  free(potential);
data_free:
  diffusion_steady_state_discrete_primal_weak_free(data);
m_inner_free:
  double_array2_free(m_inner, d + 1);
m_free:
  mesh_free(m);
end:
  return errno;
}
