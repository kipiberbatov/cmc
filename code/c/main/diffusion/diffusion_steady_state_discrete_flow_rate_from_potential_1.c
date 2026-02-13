#include <errno.h>

#include "cmc_command_line.h"
#include "cmc_error_message.h"
#include "cmc_file_open.h"
#include "cmc_file_close.h"
#include "cmc_main_compute_and_print__struct.h"
#include "cmc_main_compute_and_print_functions_one_pass__struct.h"
#include "cmc_main_generic_functions__struct.h"
#include "cmc_main_run.h"
#include "cmc_memory.h"
#include "double_array.h"
#include "diffusion_steady_state_discrete_flow_rate_from_potential.h"
#include "int.h"
#include "mesh.h"

struct problem_options
{
  cmc_command_line * dual_conductivity_format;
  cmc_command_line * dual_conductivity_name;
  cmc_command_line * mesh_format;
  cmc_command_line * mesh_name;
  cmc_command_line * mesh_hodge_format;
  cmc_command_line * mesh_hodge_name;
  cmc_command_line * potential_format;
  cmc_command_line * potential_name;
  cmc_command_line * output_format;
  cmc_command_line * output_name;
  cmc_command_line * no_positional_arguments;
};

#define SIZE ((int) (sizeof(struct problem_options) / sizeof(size_t)))

struct problem_arguments
{
  char * dual_conductivity_format;
  char * dual_conductivity_name;
  char * m_format;
  char * m_name;
  char * m_hodge_format;
  char * m_hodge_name;
  char * potential_format;
  char * potential_name;
  char * output_format;
  char * output_name;
};

static void problem_options_set(
  struct problem_options * options,
  struct problem_arguments * arguments)
{
  cmc_command_line_set_option_string(
    options->mesh_format, &(arguments->m_format), "--mesh-format", "--raw");

  cmc_command_line_set_option_string(
    options->mesh_name, &(arguments->m_name), "--mesh", NULL);

  cmc_command_line_set_option_string(
    options->mesh_hodge_format, &(arguments->m_hodge_format),
    "--hodge-star-format", "--raw");

  cmc_command_line_set_option_string(
    options->mesh_hodge_name, &(arguments->m_hodge_name), "--hodge-star", NULL);

  cmc_command_line_set_option_string(
    options->dual_conductivity_format, &(arguments->dual_conductivity_format),
    "--dual-conductivity-format", "--steady-state-dual-conductivity-raw");

  cmc_command_line_set_option_string(
    options->dual_conductivity_name, &(arguments->dual_conductivity_name),
    "--dual-conductivity", NULL);

  cmc_command_line_set_option_string(
    options->potential_format, &(arguments->potential_format),
    "--potential-format", "--raw");

  cmc_command_line_set_option_string(
    options->potential_name, &(arguments->potential_name), "--potential", NULL);

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

static void parse_arguments(
  struct problem_arguments ** arguments, int * status, int argc, char ** argv)
{
  struct cmc_command_line options_list[SIZE];
  struct problem_options options;
  
  cmc_memory_allocate((void **) arguments, status, sizeof(**arguments));
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("arguments");
    goto end;
  }

  cmc_command_line_bind((cmc_command_line **) &options, options_list, SIZE);
  problem_options_set(&options, *arguments);

  cmc_command_line_parse(
    (cmc_command_line **) &options, status, SIZE, argc, argv);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_string("cannot parse command line options\n");
    goto arguments_free;
  }

  return;

  /* cleaning if an error occurs */
arguments_free:
  cmc_memory_free((void *) arguments);
end:
  return;
}

static void open_output_channel(
  FILE ** out, int * status, const struct problem_arguments * arguments)
{
  char * name = arguments->output_name;

  if (name == NULL)
    *out = stdout;
  else
  {
    cmc_file_open(out, status, name, "w");
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      cmc_error_message_string("cannot open output file\n");
    }
  }
}

static void close_output_channel(FILE * out, int * status)
{
  if (out != stdout)
  {
    cmc_file_close(out, status);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      cmc_error_message_string("cannot close output channel\n");
    }
  }
}

static const struct cmc_main_generic_functions
generic =
{
  (void (*)(void **, int *, int, char **)) parse_arguments,
  (void (*)(void **, int *, const void * )) open_output_channel,
  (void (*)(void *, int *)) close_output_channel,
  cmc_memory_free
};

struct problem_input
{
  struct mesh * m;
  struct matrix_sparse * m_bd_1;
  struct matrix_sparse ** m_hodge;
  double * dual_conductivity;
  double * potential;
  const char * output_format;
};

static void scan_input(
  struct problem_input ** input_,
  int * status,
  const struct problem_arguments * arguments)
{
  int * m_cn;
  FILE * m_file;
  struct problem_input * input;

  cmc_memory_allocate((void **) &input, status, sizeof(*input));
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("input");
    goto end;
  }

  cmc_file_open(&m_file, status, arguments->m_name, "r");
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_string("cannot open mesh file\n");
    goto end;
  }

  input->m = mesh_file_scan(m_file, arguments->m_format);
  if (input->m == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh m from file %s in format %s\n",
      arguments->m_name, arguments->m_format);
    cmc_file_close(m_file, status);
    *status = errno;
    goto input_free;
  }

  m_cn = input->m->cn;

  input->m_bd_1 = mesh_file_scan_boundary_p(m_file, input->m, 1);
  if (input->m_bd_1 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan m_bd_1 from file %s\n", arguments->m_name);
    fclose(m_file);
    *status = errno;
    goto m_free;
  }
  fclose(m_file);

  input->m_hodge = matrix_sparse_array_file_scan_by_name(
    arguments->m_hodge_name, 2, arguments->m_hodge_format);
  if (input->m_hodge == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan m_hodge form file %s in format %s\n",
      arguments->m_hodge_name, arguments->m_hodge_format);
    *status = errno;
    goto m_bd_1_free;
  }

  input->dual_conductivity = double_array_file_scan_by_name(
    arguments->dual_conductivity_name,
    m_cn[1],
    arguments->dual_conductivity_format);
  if (input->dual_conductivity == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan dual_conductivity form file %s%s%s in format %s%s%s\n",
      color_variable, arguments->dual_conductivity_name, color_none,
      color_variable, arguments->dual_conductivity_format, color_none);
    *status = errno;
    goto m_hodge_free;
  }

  input->potential = double_array_file_scan_by_name(
    arguments->potential_name, m_cn[0], arguments->potential_format);
  if (input->potential == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan potential form file %s in format %s\n",
      arguments->potential_name, arguments->potential_format);
    *status = errno;
    goto dual_conductivity_free;
  }

  input->output_format = arguments->output_format;
  *input_ = (void *) input;
  return;

  /* cleaning if an error occurs */
dual_conductivity_free:
  cmc_memory_free(input->dual_conductivity);
m_hodge_free:
  matrix_sparse_array_free(input->m_hodge, 2);
m_bd_1_free:
  matrix_sparse_free(input->m_bd_1);
m_free:
  mesh_free(input->m);
input_free:
  cmc_memory_free(input);
end:
  return;
}

struct problem_data
{
  int size;
  double * flow_rate;
  const char * output_format;
};

static void compute_data(
  struct problem_data ** data_,
  int * status,
  const struct problem_input * input)
{
  mesh * m;
  struct problem_data * data;

  m = input->m;

  cmc_memory_allocate((void **) &data, status, sizeof(struct problem_data));
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("data");
    goto end;
  }

  data->size = m->cn[m->dim - 1];
  cmc_memory_allocate_zeros(
    (void **) &(data->flow_rate),
    status,
    sizeof(double) * data->size);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("flow_rate");
    goto data_free;
  }

  diffusion_steady_state_discrete_flow_rate_from_potential(
    data->flow_rate,
    input->m,
    input->m_bd_1,
    input->dual_conductivity,
    input->potential,
    input->m_hodge[1]);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_string("cannot calculate flow_rate");
    *status = errno;
    goto flow_rate_free;
  }

  data->output_format = input->output_format;
  *data_ = data;
  return;

  /* cleaning if an error occurs */
flow_rate_free:
  cmc_memory_free(data->flow_rate);
data_free:
  cmc_memory_free(data);
end:
  return;
}

static void free_input(struct problem_input * input)
{
  cmc_memory_free(input->potential);
  cmc_memory_free(input->dual_conductivity);
  matrix_sparse_array_free(input->m_hodge, 2);
  matrix_sparse_free(input->m_bd_1);
  mesh_free(input->m);
  cmc_memory_free(input);
}

static void
print_data(FILE * out, int * status, const struct problem_data * data)
{
  double_array_file_print(
    out, data->size, data->flow_rate, data->output_format);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_string("cannot print data\n");
    *status = errno;
  }
}

static void free_data(struct problem_data * data)
{
  cmc_memory_free(data->flow_rate);
  cmc_memory_free(data);
}

static const struct cmc_main_compute_and_print_functions_one_pass
one_pass =
{
  (void (*)(void **, int *, const void *)) scan_input,
  (void (*)(void **, int *, const void *)) compute_data,
  (void (*)(void *)) free_input,
  (void (*)(void *, int *, const void *)) print_data,
  (void (*)(void *)) free_data
};

static const struct cmc_main_compute_and_print
compute_and_print =
{
  .id = cmc_main_compute_and_print_id_one_pass,
  .functions.one_pass = &one_pass
};

int main(int argc, char ** argv)
{
  int status = 0;
  cmc_main_run(&status, argc, argv, &generic, &compute_and_print);
  if (status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_string("failed to execute\n");
  }
  return status;
}
