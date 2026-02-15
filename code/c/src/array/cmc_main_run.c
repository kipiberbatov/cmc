#include "cmc_error_message.h"
#include "cmc_command_line.h"
#include "cmc_main_compute_and_print_run.h"
#include "cmc_main__struct.h"
#include "cmc_main_state__struct.h"
#include "cmc_main_type__struct.h"
#include "cmc_main_run.h"

struct cmc_main_compute_and_print;

void cmc_main_run(
  struct cmc_main * runner,
  int * status,
  int argc,
  char ** argv)
{
  const struct cmc_main_type * type = runner->type;
  int number_of_options = type->number_of_options;
  struct cmc_main_state * state = runner->state;
  struct cmc_command_line ** options = state->options;
  struct cmc_command_line * options_list = state->options_list;
  void * arguments = state->arguments;
  void * input = state->input;
  void * data = state->data;
  char * name;
  char * format;
  void * out;

  cmc_command_line_bind(options, options_list, number_of_options);
  type->set_options(options, arguments);

  cmc_command_line_parse(options, status, number_of_options, argc, argv);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_string("cannot parse command line options\n");
    goto end;
  }
  
  name = type->get_output_channel_name(arguments);
  type->open_output_channel(&out, status, name);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_string("cannot open output channel\n");
    goto arguments_free;
  }
 
  format = type->get_output_channel_format(arguments); 
  cmc_main_compute_and_print_run(
    out,
    input,
    data,
    status,
    arguments,
    format,
    type->compute_and_print);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_string("cannot run and print\n");
    goto out_close;
  }

out_close:
  type->close_output_channel(out, status);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_string("cannot close output channel\n");
  }
arguments_free:
  type->free_arguments(arguments);
end:
  return;
}
