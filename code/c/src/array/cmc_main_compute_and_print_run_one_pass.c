#include "cmc_error_message.h"
#include "cmc_main_compute_and_print_functions_one_pass__struct.h"
#include "cmc_main_compute_and_print_run_one_pass.h"
#include "cmc_main_compute_and_print_run_one_pass_compute_data.h"

void cmc_main_compute_and_print_run_one_pass(
  void * out,
  void * input,
  void * data,
  int * status,
  const void * arguments,
  const char * format,
  const struct cmc_main_compute_and_print_functions_one_pass * one_pass)
{
  cmc_main_compute_and_print_run_one_pass_compute_data(
    input, data, status, arguments, one_pass);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_string("cannot compute data\n");
    goto end;
  }

  one_pass->print_data(out, status, data, format);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_string("cannot print data\n");
    goto data_free;
  }

data_free:
  one_pass->free_data(data);
end:
  return;
}
