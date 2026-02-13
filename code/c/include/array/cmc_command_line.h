#ifndef _cmc_command_line_h
#define _cmc_command_line_h

#include <stdio.h>

/*
struct cmc_command_line

Fields with constant values:
  . name
      This is the name of the option, always starts with "--" unless it is NULL
      which is saved for positional arguments (always the last option).
  . type_size
      The size of the type needed for malloc() when
      maximal_number_of_arguments > 1. (Otherwise, it does not matter).
  . minimal_number_of_arguments
      Specifies the minimal number of arguments an option must have (usually 0).
  . maximal_number_of_arguments
      Specifies the maximal number of arguments an option must have.
      If there is no maximum, INT_MAX = 2^{31} - 1 is usually used.
  . scan
      Pointer to a function that scans input from a string and returns to an
      undetermined type (void *). Variable 'status' is set to a nonzero value if
      an error occurs.
  . file_print
      Pointer to a function that prints the data to a file.
  . destroy
      Pointer to a function that destroys the memory allocated by scan, if any.
      If no memory is being alocated, NULL can be used.
  . default_argument
      The default argument an option takes, if any (NULL if not presented).
      It is used if no arguments are parsed.

Fields with mutable values:
  . index
      The current index of an option, initially 0. This index is incremented any
      time a command line argument is parsed even though it will not be used.
      However, a warning is sent to stderr, that that argument will be ignored.
  . number_of_arguments
      The number of parsed arguments, initially 0.
      It never exceeds maximal_number_of_arguments.
      If there are no ignored arguments, number_of_arguments == index.
      If number_of_arguments is less than minimal_number_of_arguments, parsing
      of command-line arguments will fail.
  . arguments
      Void pointer to the list of maximal_number_of_arguments parsed arguments.
      If maximal_number_of_arguments == 0, it is NULL.
      If maximal_number_of_arguments == 1, no additional memory is allocated.
*/
typedef struct cmc_command_line
{
  const char * name;
  size_t type_size;
  int minimal_number_of_arguments;
  int maximal_number_of_arguments;
  void (*string_scan)(void * data, int * status, const char * data_name);
  void (*file_print)(FILE * out, const void * data);
  void (*set_default)(void * argument, const void * default_argument);
  void (*destroy)(void * data);
  const void * default_argument;
  int index;
  int number_of_arguments;
  void * arguments;
} cmc_command_line;

void cmc_command_line_bind(
  cmc_command_line ** options,
  cmc_command_line * options_list,
  int size);

void cmc_command_line_parse(
  cmc_command_line ** options, int * status,
  int size, int argc, char ** argv);

void cmc_command_line_file_print(
  FILE * out, int size, cmc_command_line ** options);

void cmc_command_line_set_option_no_arguments(
  cmc_command_line * option, void * value,
  const char * name, const void * default_argument);

void cmc_command_line_set_option_int(
  cmc_command_line * option, int * value, const char * name,
  const int * default_argument);

void cmc_command_line_set_option_double(
  cmc_command_line * option, double * value, const char * name,
  const double * default_argument);

void cmc_command_line_set_option_string(
  cmc_command_line * option, char ** value, const char * name,
  const char * default_argument);

void cmc_command_line_set_option_string_array(
  cmc_command_line * option, const char * name);

void cmc_command_line_set_no_positional_arguments(cmc_command_line * option);

#endif /* _cmc_command_line_h */
