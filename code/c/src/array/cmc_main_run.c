#include "cmc_error_message.h"
#include "cmc_main_compute_and_print__struct.h"
#include "cmc_main_compute_and_print_run.h"
#include "cmc_main_generic_functions__struct.h"
#include "cmc_main_run.h"

void cmc_main_run(
  int * status,
  int argc,
  char ** argv,
  const struct cmc_main_generic_functions * generic,
  const struct cmc_main_compute_and_print * compute_and_print)
{
  void * arguments;
  void * out;

  generic->parse_arguments(&arguments, status, argc, argv);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_string("cannot parse command line arguments\n");
    goto end;
  }

  generic->open_output_channel(&out, status, arguments);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_string("cannot open output channel\n");
    goto arguments_free;
  }
  
  cmc_main_compute_and_print_run(out, status, arguments, compute_and_print);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_string("cannot run and print\n");
    goto out_close;
  }

out_close:
  generic->close_output_channel(out, status);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_string("cannot close output channel\n");
  }
arguments_free:
  generic->free_arguments(arguments);
end:
  return;
}
