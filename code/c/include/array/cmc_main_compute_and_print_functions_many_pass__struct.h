#ifndef _cmc_main_compute_and_print_functions_many_pass__struct_h
#define _cmc_main_compute_and_print_functions_many_pass__struct_h

struct cmc_main_compute_and_print_functions_many_pass
{
  void (*scan_input)(void **, int *, const void *);
  void (*compute_print_and_free_data_in_loop)(void *, int *, const void *);
  void (*free_input)(void *);
};

#endif /* _cmc_main_compute_and_print_functions_many_pass__struct_h */
