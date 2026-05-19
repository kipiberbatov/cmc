#include <errno.h>

#include "cmc_command_line.h"
#include "cmc_diffusion_discrete_primal_weak_a_advective.h"
#include "cmc_error_message.h"
#include "cmc_file_open_output_channel.h"
#include "cmc_file_close_output_channel.h"
#include "cmc_main__struct.h"
#include "cmc_main_compute_and_print_functions_one_pass__struct.h"
#include "cmc_main_compute_and_print__struct.h"
#include "cmc_main_run.h"
#include "cmc_main_state__struct.h"
#include "cmc_main_type__struct.h"
#include "cmc_memory.h"
#include "double_array.h"
#include "matrix_sparse.h"
#include "mesh.h"

struct cmc_diffusion_discrete_primal_weak_a_advective_input
{
  struct mesh * K;
  struct matrix_sparse * cbd_dm1;
  double * dual_capacity;
  double * volumetric_flow_rate;
};

void cmc_diffusion_discrete_primal_weak_a_advective_input_free_values(
  struct cmc_diffusion_discrete_primal_weak_a_advective_input * input)
{
  mesh_free(input->K);
  matrix_sparse_free(input->cbd_dm1);
  cmc_memory_free(input->dual_capacity);
  cmc_memory_free(input->volumetric_flow_rate);
}

struct cmc_diffusion_discrete_primal_weak_a_advective_arguments
{
  char * K_format;
  char * K_name;
  char * cbd_dm1_format;
  char * cbd_dm1_name;
  char * dual_capacity_format;
  char * dual_capacity_name;
  char * volumetric_flow_rate_format;
  char * volumetric_flow_rate_name;
  char * output_format;
  char * output_name;
};

static void cmc_diffusion_discrete_primal_weak_a_advective_input_scan(
  struct cmc_diffusion_discrete_primal_weak_a_advective_input * input,
  int * status,
  const struct cmc_diffusion_discrete_primal_weak_a_advective_arguments *
    arguments)
{
  int d, i;
  int * cn;
  double * dual_capacity, * volumetric_flow_rate;
  struct matrix_sparse ** cbd;
  struct mesh * K;

  K = mesh_file_scan_by_name(arguments->K_name, arguments->K_format);
  if (K == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_string("cannot scan the mesh K\n");
    *status = errno;
    goto end;
  }

  K->fc = mesh_fc(K);
  if (K->fc == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_cannot_calculate("K->fc");
    *status = errno;
    goto K_free;
  }

  input->K = K;

  cn = K->cn;
  d = K->dim;

  cbd = matrix_sparse_array_file_scan_by_name(
    arguments->cbd_dm1_name, d, arguments->cbd_dm1_format);
  if (cbd == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_string("cannot scan the coboundary operator\n");
    *status = errno;
    goto K_free;
  }
  input->cbd_dm1 = cbd[d - 1];
  for (i = d - 2; i >= 0; --i)
    matrix_sparse_free(cbd[i]);
  cmc_memory_free(cbd);

  dual_capacity = double_array_file_scan_by_name(
    arguments->dual_capacity_name,
    cn[0],
    arguments->dual_capacity_format);
  if (dual_capacity == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_string("cannot scan the dual capacity\n");
    *status = errno;
    goto cbd_dm1_free;
  }
  input->dual_capacity = dual_capacity;

  volumetric_flow_rate = double_array_file_scan_by_name(
    arguments->volumetric_flow_rate_name,
    cn[d - 1],
    arguments->volumetric_flow_rate_format);
  if (volumetric_flow_rate == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_string("cannot scan the volumetric flow rate\n");
    *status = errno;
    goto dual_capacity_free;
  }
  input->volumetric_flow_rate = volumetric_flow_rate;

  return;

  /* cleaning if an error occurs */
dual_capacity_free:
  cmc_memory_free(dual_capacity);
cbd_dm1_free:
  matrix_sparse_free(input->cbd_dm1);
K_free:
  mesh_free(K);
end:
  return;
}

struct cmc_diffusion_discrete_primal_weak_a_advective_options
{
  struct cmc_command_line * mesh_format;
  struct cmc_command_line * mesh_name;
  struct cmc_command_line * coboundary_dm1_format;
  struct cmc_command_line * coboundary_dm1_name;
  struct cmc_command_line * dual_capacity_format;
  struct cmc_command_line * dual_capacity_name;
  struct cmc_command_line * volumetric_flow_rate_format;
  struct cmc_command_line * volumetric_flow_rate_name;
  struct cmc_command_line * output_format;
  struct cmc_command_line * output_name;
  struct cmc_command_line * no_positional_arguments;
};

static void cmc_diffusion_discrete_primal_weak_a_advective_options_set(
  struct cmc_diffusion_discrete_primal_weak_a_advective_options * options,
  struct cmc_diffusion_discrete_primal_weak_a_advective_arguments *
    arguments)
{
  cmc_command_line_set_option_string(
    options->mesh_format, &(arguments->K_format), "--mesh-format", "--raw");

  cmc_command_line_set_option_string(
    options->mesh_name, &(arguments->K_name), "--mesh", NULL);

  cmc_command_line_set_option_string(
    options->coboundary_dm1_format, &(arguments->cbd_dm1_format),
    "--coboundary-dm1-format", "--raw");

  cmc_command_line_set_option_string(
    options->coboundary_dm1_name, &(arguments->cbd_dm1_name),
    "--coboundary-dm1", NULL);

  cmc_command_line_set_option_string(
    options->dual_capacity_format, &(arguments->dual_capacity_format),
    "--dual-capacity-format", "--raw");

  cmc_command_line_set_option_string(
    options->dual_capacity_name, &(arguments->dual_capacity_name),
    "--dual-capacity", NULL);

  cmc_command_line_set_option_string(
    options->volumetric_flow_rate_format,
    &(arguments->volumetric_flow_rate_format),
    "--volumetric-flow-rate-format", "--raw");

  cmc_command_line_set_option_string(
    options->volumetric_flow_rate_name, &(arguments->volumetric_flow_rate_name),
    "--volumetric-flow-rate", NULL);

  cmc_command_line_set_option_string(
    options->output_format, &(arguments->output_format),
    "--output-format", "--raw");

  cmc_command_line_set_option_string(
    options->output_name, &(arguments->output_name), "--output", NULL);
  options->output_name->minimal_number_of_arguments = 0;

  /* there are no positional arguments */
  cmc_command_line_set_option_no_arguments(
    options->no_positional_arguments, NULL, NULL, NULL);
}

extern const struct cmc_main_compute_and_print
cmc_diffusion_discrete_primal_weak_a_advective_compute_and_print;

static char * get_output_channel_name(const struct
  cmc_diffusion_discrete_primal_weak_a_advective_arguments * arguments)
{
  return arguments->output_name;
}

static char * get_output_channel_format(const struct
  cmc_diffusion_discrete_primal_weak_a_advective_arguments * arguments)
{
  return arguments->output_format;
}

static void do_nothing(void * p){}

static void cmc_diffusion_discrete_primal_weak_a_advective_(
  struct matrix_sparse ** a_advective_pointer,
  int * status,
  const struct cmc_diffusion_discrete_primal_weak_a_advective_input * input)
{
  cmc_diffusion_discrete_primal_weak_a_advective(
    a_advective_pointer,
    status,
    input->K,
    input->cbd_dm1,
    input->dual_capacity,
    input->volumetric_flow_rate);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_cannot_calculate("a_advective_pointer\n");
  }
}

static void matrix_sparse_file_print_(
  FILE * out, int * status, matrix_sparse ** a, const char * format)
{
  matrix_sparse_file_print(out, *a, format);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_string("cannot print sparse matrix a\n");
    *status = errno;
  }
}

static void matrix_sparse_free_(struct matrix_sparse ** a)
{
  matrix_sparse_free(*a);
}

static const struct cmc_main_compute_and_print_functions_one_pass
cmc_diffusion_discrete_primal_weak_a_advective_one_pass =
{
  (void (*)(void *, int *, const void *))
    cmc_diffusion_discrete_primal_weak_a_advective_input_scan,
  (void (*)(void *, int *, const void *))
    cmc_diffusion_discrete_primal_weak_a_advective_,
  (void (*)(void *))
    cmc_diffusion_discrete_primal_weak_a_advective_input_free_values,
  (void (*)(void *, int *, const void *, const char *))
    matrix_sparse_file_print_,
  (void (*)(void *)) matrix_sparse_free_
};

const struct cmc_main_compute_and_print
cmc_diffusion_discrete_primal_weak_a_advective_compute_and_print =
{
  .id = cmc_main_compute_and_print_id_one_pass,
  .functions.one_pass =
    &cmc_diffusion_discrete_primal_weak_a_advective_one_pass
};

const struct cmc_main_type
cmc_diffusion_discrete_primal_weak_a_advective_type =
{
  sizeof(struct cmc_diffusion_discrete_primal_weak_a_advective_options)
  / sizeof(size_t),
  (void (*)(struct cmc_command_line **, void *)) cmc_diffusion_discrete_primal_weak_a_advective_options_set,
  (char * (*)(const void *)) get_output_channel_name,
  (char * (*)(const void *)) get_output_channel_format,
  (void (*)(void **, int *, const char * )) cmc_file_open_output_channel,
  &cmc_diffusion_discrete_primal_weak_a_advective_compute_and_print,
  (void (*)(void *, int *)) cmc_file_close_output_channel,
  do_nothing
};

int main(int argc, char ** argv)
{
  enum
  {
    SIZE =
      sizeof(struct cmc_diffusion_discrete_primal_weak_a_advective_options)
      / sizeof(struct cmc_command_line *)
  };
  struct cmc_command_line options_list[SIZE];
  struct cmc_diffusion_discrete_primal_weak_a_advective_options options;
  struct cmc_diffusion_discrete_primal_weak_a_advective_arguments arguments;
  struct cmc_diffusion_discrete_primal_weak_a_advective_input input;
  struct matrix_sparse * data;
  struct cmc_main_state state =
  {
    options_list,
    (struct cmc_command_line **) &options,
    (void *) &arguments,
    (void *) &input,
    (void *) &data
  };
  struct cmc_main runner =
  {
    &cmc_diffusion_discrete_primal_weak_a_advective_type,
    &state
  };
  int status = 0;

  cmc_main_run(&runner, &status, argc, argv);
  if (status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_string("failed to execute\n");
  }
  return status;
}
