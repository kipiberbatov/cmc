#ifndef _cmc_main_compute_and_print_functions_one_pass__struct_h
#define _cmc_main_compute_and_print_functions_one_pass__struct_h

struct cmc_main_compute_and_print_functions_one_pass
{
  void (*scan_input)(void *, int *, const void *);
  void (*compute_data)(void *, int *, const void *);
  void (*free_input)(void *);
  void (*print_data)(void *, int *, const void *, const char *);
  void (*free_data)(void *);
};

#endif /* _cmc_main_compute_and_print_functions_one_pass__struct_h */
