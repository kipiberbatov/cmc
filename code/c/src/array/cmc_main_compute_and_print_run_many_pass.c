#include "cmc_error_message.h"
#include "cmc_main_compute_and_print_functions_many_pass__struct.h"
#include "cmc_main_compute_and_print_run_many_pass.h"

void cmc_main_compute_and_print_run_many_pass(
  void * out,
  void * input,
  void * data,
  int * status,
  const void * arguments,
  const char * format,
  const struct cmc_main_compute_and_print_functions_many_pass * many_pass)
{
  many_pass->scan_input(input, status, arguments);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_string("cannot scan input\n");
    goto end;
  }

  many_pass->compute_print_and_free_data_in_loop(
    out, data, status, input, format);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_string("fail to execute the compute-print-free loop\n");
    goto input_free;
  }

input_free:
  many_pass->free_input(input);
end:
  return;
}
