#ifndef _cmc_main_generic_functions__struct_h
#define _cmc_main_generic_functions__struct_h

struct cmc_main_generic_functions
{
  void (*parse_arguments)(void **, int *, int, char **);
  void (*open_output_channel)(void **, int *, const void *);
  void (*close_output_channel)(void *, int *);
  void (*free_arguments)(void *);
};

#endif
