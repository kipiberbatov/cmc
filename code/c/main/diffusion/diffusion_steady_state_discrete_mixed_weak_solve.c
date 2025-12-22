#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "double_array2.h"
#include "diffusion_steady_state_discrete_mixed_weak.h"
#include "mesh.h"

int main(int argc, char ** argv)
{
  char * data_name, * m_inner_format, * m_inner_name, * m_format, * m_name;
  int d;
  int * m_cn;
  double * flow_rate, * dual_potential;
  double ** m_inner;
  FILE * data_file, * m_file;
  struct matrix_sparse * m_cbd_dm1;
  struct matrix_sparse ** m_bd;
  struct mesh * m;
  struct diffusion_steady_state_discrete_mixed_weak * data;

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
    fprintf(stderr,
      "cannot scan mesh m from file %s in format %s\n", m_name, m_format);
    fclose(m_file);
    goto end;
  }

  m->fc = mesh_fc(m);
  if (m->fc == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m->fc\n", stderr);
    goto m_free;
  }

  m_bd = mesh_file_scan_boundary(m_file, m);
  if (m_bd == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan m_bd\n", stderr);
    fclose(m_file);
    goto m_free;
  }

  fclose(m_file);

  d = m->dim;
  m_cn = m->cn;

  m_cbd_dm1 = matrix_sparse_transpose(m_bd[d - 1]);
  if (m_cbd_dm1 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m->fc\n", stderr);
    goto m_bd_free;
  }

  m_inner = double_array2_file_scan_by_name(
    m_inner_name, d + 1, m_cn, m_inner_format);
  if (m_inner == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan inner products from file %s in format %s\n",
      m_inner_name, m_inner_format);
    goto m_cbd_dm1_free;
  }

  data_file = fopen(data_name, "r");
  if (data_file == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open problem data file %s: %s\n", data_name, strerror(errno));
    goto m_inner_free;
  }
  data = diffusion_steady_state_discrete_mixed_weak_file_scan_raw(data_file);
  if (data == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan problem data from file %s\n", data_name);
    fclose(data_file);
    goto m_inner_free;
  }
  fclose(data_file);

  flow_rate = (double *) malloc(sizeof(double) * m->cn[d - 1]);
  if (flow_rate == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m->cn[d - 1], "flow_rate");
    goto data_free;
  }

  dual_potential = (double *) malloc(sizeof(double) * m->cn[d]);
  if (dual_potential == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m->cn[d], "dual_potential");
    goto flow_rate_free;
  }

  diffusion_steady_state_discrete_mixed_weak_solve(
    flow_rate, dual_potential, m, m_cbd_dm1, m_inner[d - 1], m_inner[d], data);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot find flow_rate and potential\n", stderr);
    goto dual_potential_free;
  }

  fprintf(stdout, "%d\n", m->cn[d - 1]);
  fprintf(stdout, "%d\n", m->cn[d]);
  double_array_file_print(stdout, m->cn[d - 1], flow_rate, "--raw");
  double_array_file_print(stdout, m->cn[d], dual_potential, "--raw");

dual_potential_free:
  free(dual_potential);
flow_rate_free:
  free(flow_rate);
data_free:
  diffusion_steady_state_discrete_mixed_weak_free(data);
m_inner_free:
  double_array2_free(m_inner, d + 1);
m_cbd_dm1_free:
  matrix_sparse_free(m_cbd_dm1);
m_bd_free:
  matrix_sparse_array_free(m_bd, d);
m_free:
  mesh_free(m);
end:
  return errno;
}
