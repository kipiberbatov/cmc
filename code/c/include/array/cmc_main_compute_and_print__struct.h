#ifndef _cmc_main_compute_and_print__struct_h
#define _cmc_main_compute_and_print__struct_h

struct cmc_main_compute_and_print_functions_one_pass;
struct cmc_main_compute_and_print_functions_many_pass;

struct cmc_main_compute_and_print
{
  enum
  {
    cmc_main_compute_and_print_id_one_pass,
    cmc_main_compute_and_print_id_many_pass
  } id;
  union
  {
    const struct cmc_main_compute_and_print_functions_one_pass * one_pass;
    const struct cmc_main_compute_and_print_functions_many_pass * many_pass;
  } functions;
};

#endif /* _cmc_main_compute_and_print__struct_h */
