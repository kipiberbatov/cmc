#include "cmc_error_message.h"
#include "cmc_main_compute_and_print_run.h"
#include "cmc_main_compute_and_print_run_one_pass.h"
#include "cmc_main_compute_and_print_run_many_pass.h"
#include "cmc_main_compute_and_print__struct.h"

struct cmc_main_compute_and_print_functions_one_pass;
struct cmc_main_compute_and_print_functions_many_pass;

void cmc_main_compute_and_print_run(
  void * out,
  int * status,
  const void * arguments,
  const struct cmc_main_compute_and_print * compute_and_print)
{
  switch (compute_and_print->id)
  {
  case cmc_main_compute_and_print_id_one_pass:
    cmc_main_compute_and_print_run_one_pass(
      out,
      status,
      arguments,
      compute_and_print->functions.one_pass);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      cmc_error_message_string("cannot compute and print in one pass\n");
    }
    break;
  case cmc_main_compute_and_print_id_many_pass:
    cmc_main_compute_and_print_run_many_pass(
      out,
      status,
      arguments,
      compute_and_print->functions.many_pass);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      cmc_error_message_string("cannot compute and print in multiple passes\n");
    }
    break;
  default:
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_string("runner id ");
    cmc_error_message_variable_int(compute_and_print->id);
    cmc_error_message_string(" is not supported\n");
    *status = 1;
    break;
  }
}
