#ifndef _cmc_main_state__struct_h
#define _cmc_main_state__struct_h

struct cmc_command_line;

struct cmc_main_state
{
  struct cmc_command_line * options_list;
  struct cmc_command_line ** options;
  void * arguments;
  void * input;
  void * data;
};

#endif /* _cmc_main_state__struct_h */
