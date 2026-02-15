#include "cmc_error_message.h"
#include "cmc_main_compute_and_print_functions_one_pass__struct.h"
#include "cmc_main_compute_and_print_run_one_pass_compute_data.h"

void cmc_main_compute_and_print_run_one_pass_compute_data(
  void * input,
  void * data,
  int * status,
  const void * arguments,
  const struct cmc_main_compute_and_print_functions_one_pass * one_pass)
{
  one_pass->scan_input(input, status, arguments);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_string("cannot scan input\n");
    goto end;
  }

  one_pass->compute_data(data, status, input);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_string("cannot compute data\n");
    goto input_free;
  }

input_free:
  one_pass->free_input(input);
end:
  return;
}
