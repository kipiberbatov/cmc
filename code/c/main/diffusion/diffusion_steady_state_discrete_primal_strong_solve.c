#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "diffusion_steady_state_discrete_primal_strong.h"
#include "mesh.h"

int main(int argc, char ** argv)
{
  char * data_name, * m_cbd_0_name, * m_cbd_star_1_name, * m_format, * m_name;
  double * potential;
  FILE * data_file, * m_cbd_star_1_file;
  struct matrix_sparse * m_cbd_0, * m_cbd_star_1;
  struct mesh * m;
  struct diffusion_steady_state_discrete_primal_strong * data;

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
  m_cbd_0_name = argv[3];
  m_cbd_star_1_name = argv[4];
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

  m_cbd_0 = matrix_sparse_file_scan_by_name(m_cbd_0_name, "--raw");
  if (m_cbd_0 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan m_cbd_0\n", stderr);
    goto m_free;
  }

  m_cbd_star_1_file = fopen(m_cbd_star_1_name, "r");
  if (m_cbd_star_1_file == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open adjoint coboundary matrix file %s for reading: %s\n",
      m_cbd_star_1_name, strerror(errno));
    goto m_cbd_0_free;
  }
  m_cbd_star_1 = mesh_file_scan_boundary_p(m_cbd_star_1_file, m, 1);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan m_cbd_star_1 from file %s\n", m_cbd_star_1_name);
    fclose(m_cbd_star_1_file);
    goto m_cbd_0_free;
  }
  fclose(m_cbd_star_1_file);

  data_file = fopen(data_name, "r");
  if (data_file == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open problem data file %s: %s\n", data_name, strerror(errno));
    goto m_cbd_star_1_free;
  }
  data = diffusion_steady_state_discrete_primal_strong_file_scan_raw(data_file);
  if (data == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan problem data from file %s\n", data_name);
    fclose(data_file);
    goto m_cbd_star_1_free;
  }
  fclose(data_file);

  potential = diffusion_steady_state_discrete_primal_strong_solve(
    m, m_cbd_0, m_cbd_star_1, data);
  if (potential == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate potential\n", stderr);
    goto data_free;
  }

  double_array_file_print(stdout, m->cn[0], potential, "--raw");

  free(potential);
data_free:
  diffusion_steady_state_discrete_primal_strong_free(data);
m_cbd_star_1_free:
  matrix_sparse_free(m_cbd_star_1);
m_cbd_0_free:
  matrix_sparse_free(m_cbd_0);
m_free:
  mesh_free(m);
end:
  return errno;
}
