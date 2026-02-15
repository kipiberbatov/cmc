#ifndef _cmc_main_type__struct_h
#define _cmc_main_type__struct_h

struct cmc_command_line;
struct cmc_main_compute_and_print;

struct cmc_main_type
{
  const int number_of_options;
  void (*set_options)(struct cmc_command_line **, void *);
  char * (*get_output_channel_name)(const void *);
  char * (*get_output_channel_format)(const void *);
  void (*open_output_channel)(void **, int *, const char *);
  const struct cmc_main_compute_and_print * compute_and_print;
  void (*close_output_channel)(void *, int *);
  void (*free_arguments)(void *);
};

#endif /* _cmc_main_type__struct_h */
