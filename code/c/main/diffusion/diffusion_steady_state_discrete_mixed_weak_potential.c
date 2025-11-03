#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "diffusion_steady_state_discrete_mixed_weak.h"
#include "double_array.h"
#include "double_array2.h"
#include "int.h"
#include "mesh_qc.h"

int main(int argc, char ** argv)
{
  char * data_name, * m_vol_format, * m_vol_name, * m_format, * m_name,
       * solution_name;
  int d, m_cn_dm1, m_cn_d;
  int * m_cn;
  double * flow_rate, * potential, * dual_potential;
  double ** m_vol;
  FILE * data_file, * m_file, * solution_file;
  struct mesh * m;
  struct diffusion_steady_state_discrete_mixed_weak * data;

#define ARGC 7
  if (argc != ARGC)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_number_of_command_line_arguments_mismatch(ARGC, argc);
    errno = EINVAL;
    goto end;
  }

  m_format = argv[1];
  m_name = argv[2];
  m_vol_format = argv[3];
  m_vol_name = argv[4];
  data_name = argv[5];
  solution_name = argv[6];

  m_file = fopen(m_name, "r");
  if (m_file == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot open mesh file %s: %s\n", m_name, strerror(errno));
    goto end;
  }

  m = mesh_file_scan_by_name(m_name, m_format);
  if (m == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh m from file %s in format %s\n", m_name, m_format);
    goto end;
  }

  d = m->dim;
  m_cn = m->cn;

  m->fc = mesh_fc(m);
  if (m->fc == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m->fc\n", stderr);
    goto m_free;
  }

  m_vol = double_array2_file_scan_by_name(
    m_vol_name, d + 1, m_cn, m_vol_format);
  if (m_vol == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan cells' measures from file %s in format %s\n",
      m_vol_name, m_vol_format);
    goto m_free;
  }

  data_file = fopen(data_name, "r");
  if (data_file == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open problem data file %s: %s\n", data_name, strerror(errno));
    goto m_vol_free;
  }
  data = diffusion_steady_state_discrete_mixed_weak_file_scan_raw(data_file);
  if (data == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan problem data from file %s\n", data_name);
    fclose(data_file);
    goto m_vol_free;
  }
  fclose(data_file);

  solution_file = fopen(solution_name, "r");
  if (solution_file == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open problem solution file %s: %s\n",
      solution_name, strerror(errno));
    goto data_free;
  }
  m_cn_dm1 = int_file_scan(solution_file);
  m_cn_d = int_file_scan(solution_file);

  flow_rate = double_array_file_scan(solution_file, m_cn_dm1, "--raw");
  if (flow_rate == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan flow_rate from file in format --raw %s\n", solution_name);
    fclose(solution_file);
    goto data_free;
  }
  free(flow_rate);

  dual_potential = double_array_file_scan(solution_file, m_cn_d, "--raw");
  if (dual_potential == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan dual_potential from file in format --raw %s\n",
      solution_name);
    fclose(solution_file);
    goto data_free;
  }
  fclose(solution_file);

  potential = (double *) malloc(sizeof(double) * m->cn[0]);
  if (potential == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m->cn[0], "potential");
    goto dual_potential_free;
  }

  mesh_qc_hodge_star_d(potential, m, m_vol[d], dual_potential);
  double_array_assemble_from_sparse_array(
    potential, data->boundary_dirichlet_0, data->g_dirichlet_0);

  double_array_file_print(stdout, m->cn[0], potential, "--raw");

  free(potential);
dual_potential_free:
  free(dual_potential);
data_free:
  diffusion_steady_state_discrete_mixed_weak_free(data);
m_vol_free:
  double_array2_free(m_vol, d + 1);
m_free:
  mesh_free(m);
end:
  return errno;
}
