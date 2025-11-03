#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "cmc_command_line.h"

static int cmc_command_line_is_option(const char * option)
{
  return (strlen(option) > 2) && option[0] == '-' && option[1] == '-';
}

static int cmc_command_line_length(const char * option)
{
  int i, length = 0;

  for (i = 0; option[i] != '\0' && option[i] != '='; ++i)
    ++length;
  return length;
}

static int cmc_command_line_is_without_equal(const char * option)
{
  return option[cmc_command_line_length(option)] == '\0';
}

static int cmc_command_line_index(
  int size, cmc_command_line ** options, const char * option)
{
  int j, n;
  const cmc_command_line * option_j;

  n = cmc_command_line_length(option);
  for (j = 0; j < size - 1; ++j)
  {
    option_j = options[j];
    if (strlen(option_j->name) == n && !strncmp(option, option_j->name, n))
      return j;
  }
  return -1;
}

static void cmc_command_line_find_number_of_occurences_optional(
  cmc_command_line ** options, int * status, int * i,
  int size, int argc, char * option_name)
{
  int j;
  cmc_command_line * option_j;

  j = cmc_command_line_index(size, options, option_name);
  if (j == -1)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "%s%.*s%s is not a valid option\n",
      color_variable, cmc_command_line_length(option_name), option_name,
      color_none);
    *status = 1;
    return;
  }
  option_j = options[j];
  if (option_j->number_of_arguments < option_j->maximal_number_of_arguments)
    ++option_j->number_of_arguments;
  if (option_j->maximal_number_of_arguments > 0)
  {
    if (cmc_command_line_is_without_equal(option_name))
    {
      ++*i;
      if (*i == argc)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fprintf(stderr,
          "last option %s%s%s has no arguments\n",
          color_variable, option_j->name, color_none);
        *status = 1;
        return;
      }
    }
  }
}

static void cmc_command_line_find_number_of_occurences(
  cmc_command_line ** options, int * status,
  int size, int argc, char ** argv)
{
  int i, j;
  cmc_command_line * option_j;

  for (i = 1; i < argc; ++i)
  {
    if (cmc_command_line_is_option(argv[i]))
    {
      cmc_command_line_find_number_of_occurences_optional(
        options, status, &i, size, argc, argv[i]);
      if (*status)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fprintf(stderr, "cannot parse argument %s%s%s\n",
          color_variable, argv[i], color_none);
        return;
      }
    }
    else /* positional argument */
    {
      j = size - 1;
      option_j = options[j];
      if (option_j->number_of_arguments < option_j->maximal_number_of_arguments)
        ++option_j->number_of_arguments;
    }
  }
}

static void cmc_command_line_check_minimality(
  cmc_command_line ** options, int * status, int size)
{
  int j, min_j, total_j;
  cmc_command_line * option_j;

  for (j = 0; j < size; ++j)
  {
    option_j = options[j];
    total_j = option_j->number_of_arguments;
    min_j = option_j->minimal_number_of_arguments;
    if (min_j > total_j)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr,
        "the minimal number of arguments for option %s%s%s is %s%d%s "
        "but only %s%d%s were found\n",
        color_variable, option_j->name, color_none,
        color_variable, min_j, color_none,
        color_variable, total_j, color_none);
      *status = 1;
      return;
    }
  }
}

static void cmc_destroy_array(void * arguments,
  int total, int type_size, void (*destroy)(void *))
{
  int i, offset;
  void * data;

  for (i = total - 1; i >= 0; --i)
  {
    offset = type_size * i;
    data = (void *) (((char *) arguments) + offset);
    if (destroy != NULL)
      destroy(data);
  }
}

static void cmc_command_line_free_arguments(
  cmc_command_line ** options, int size)
{
  int j, max_j, type_size_j, total_j;
  void * arguments_j;
  void (*destroy_j)(void *);
  cmc_command_line * option_j;

  for (j = size - 1; j >= 0; --j)
  {
    option_j = options[j];
    max_j = option_j->maximal_number_of_arguments;
    total_j = option_j->number_of_arguments;
    type_size_j = option_j->type_size;
    arguments_j = option_j->arguments;
    destroy_j = option_j->destroy;
    if (total_j > 0)
    {
      if (max_j >= 1)
        cmc_destroy_array(arguments_j, total_j, type_size_j, destroy_j);
      if (max_j >= 2)
        free(arguments_j);
    }
  }
}

static void cmc_command_line_allocate_arguments(
  cmc_command_line ** options, int * status,
  int size, int argc, char ** argv)
{
  int j, max_j, total_j;
  cmc_command_line * option_j;

  for (j = 0; j < size; ++j)
  {
    option_j = options[j];
    max_j = option_j->maximal_number_of_arguments;
    total_j = option_j->number_of_arguments;
    if (max_j >= 2)
    {
      if (total_j > 0)
      {
        option_j->arguments = malloc(option_j->type_size * total_j);
        if (option_j->arguments == NULL)
        {
          cmc_error_message_position_in_code(__FILE__, __LINE__);
          fprintf(stderr,
            "cannot allocate %ld bytes of memory for option %s%s%s",
            option_j->type_size * total_j,
            color_variable, option_j->name, color_none);
          *status = 1;
          cmc_command_line_free_arguments(options, j);
          return;
        }
      }
    }
  }
}

static cmc_command_line * cmc_command_line_find_option_index(
  cmc_command_line ** options, int size, int n, const char * argument)
{
  int j;
  cmc_command_line * option_j;

  for (j = 0; j < size - 1; ++j)
  {
    option_j = options[j];
    if (strlen(option_j->name) == n && !strncmp(argument, option_j->name, n))
      return option_j;
  }
  return NULL;
}

static void cmc_command_line_set_optional_argument_name(
  char ** data_name, int * i, char ** argv, int n)
{
  if (cmc_command_line_is_without_equal(argv[*i]))
  {
    *data_name = argv[*i + 1];
    ++*i;
  }
  else
    *data_name = argv[*i] + n + 1;
}

static void cmc_command_line_set_optional_argument_data(
  cmc_command_line * option_j, int * status, const char * data_name)
{
  int offset;
  void * data;

  if (option_j->index < option_j->maximal_number_of_arguments)
  {
    offset = option_j->type_size * option_j->index;
    data = (void *) (((char *) option_j->arguments) + offset);
    option_j->string_scan(data, status, data_name);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr,
        "cannot scan data for option %s%s%s from string %s%s%s\n",
        color_variable, option_j->name, color_none,
        color_variable, data_name, color_none);
      return;
    }
  }
  else
  {
    fprintf(stderr,
      "%sWarning:%s option %s%s%s can take at most %s%d%s argument%s. "
      "Argument with index %s%d%s and value %s%s%s is ignored\n",
      color_red, color_none,
      color_variable, option_j->name, color_none,
      color_variable, option_j->maximal_number_of_arguments, color_none,
      option_j->maximal_number_of_arguments == 1 ? "" : "s",
      color_variable, option_j->index, color_none,
      color_variable, data_name, color_none);
  }
  ++option_j->index;
}

static void cmc_command_line_set_optional_argument(
  cmc_command_line ** options, int * i, int * status,
  int size, char ** argv)
{
  int n;
  char * data_name;
  cmc_command_line * option_j;

  n = cmc_command_line_length(argv[*i]);
  option_j = cmc_command_line_find_option_index(options, size, n, argv[*i]);
  if (option_j->maximal_number_of_arguments > 0)
  {
    cmc_command_line_set_optional_argument_name(&data_name, i, argv, n);
    cmc_command_line_set_optional_argument_data(option_j, status, data_name);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr,
        "cannot set option %s%s%s from string %s%s%s\n",
        color_variable, option_j->name, color_none,
        color_variable, data_name, color_none);
      return;
    }
  }
  else
  {
    option_j->arguments = (void *) option_j->default_argument;
    ++option_j->index;
  }
}

static void cmc_command_line_set_positional_argument(
  cmc_command_line * option_j, int * status, const char * data_name)
{
  int offset;
  void * data;

  if (option_j->index < option_j->maximal_number_of_arguments)
  {
    offset = option_j->type_size * option_j->index;
    data = (void *) (((char *) option_j->arguments) + offset);
    option_j->string_scan(data, status, data_name);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr,
        "cannot scan data for option %s%s%s from string %s%s%s\n",
        color_variable, option_j->name, color_none,
        color_variable, data_name, color_none);
      return;
    }
  }
  else
  {
    fprintf(stderr,
      "%sWarning:%s there could be at most %s%d%s positional argument%s. "
      "Argument with index %s%d%s and value %s%s%s is ignored\n",
      color_red, color_none,
      color_variable, option_j->maximal_number_of_arguments, color_none,
      option_j->maximal_number_of_arguments == 1 ? "" : "s",
      color_variable, option_j->index, color_none,
      color_variable, data_name, color_none);
  }
  ++option_j->index;
}

static void cmc_command_line_set_arguments(
  cmc_command_line ** options, int * status,
  int size, int argc, char ** argv)
{
  int i, j;

  for (i = 1; i < argc; ++i)
  {
    if (cmc_command_line_is_option(argv[i]))
    {
      cmc_command_line_set_optional_argument(options, &i, status, size, argv);
      if (*status)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fputs("cannot set optional argument\n", stderr);
        return;
      }
    }
    else
    {
      j = size - 1;
      cmc_command_line_set_positional_argument(options[j], status, argv[i]);
      if (*status)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fputs("cannot set positional argument\n", stderr);
        return;
      }
    }
  }
}

static void
cmc_command_line_set_default(cmc_command_line ** options, int size)
{
  int j;
  cmc_command_line * option_j;

  for (j = 0; j < size; ++j)
  {
    option_j = options[j];
    if (option_j->number_of_arguments == 0 &&
        option_j->maximal_number_of_arguments == 1 &&
        option_j->default_argument != NULL)
    {
      option_j->set_default(option_j->arguments, option_j->default_argument);
    }
  }
}

void cmc_command_line_parse(
  cmc_command_line ** options, int * status,
  int size, int argc, char ** argv)
{
  cmc_command_line_find_number_of_occurences(
    options, status, size, argc, argv);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot find number of occurences of arguments\n", stderr);
    return;
  }

  cmc_command_line_check_minimality(options, status, size);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("an option has less than minimal number of arguments\n", stderr);
    return;
  }

  cmc_command_line_allocate_arguments(options, status, size, argc, argv);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot allocate memory for command-line arguments\n", stderr);
    return;
  }

  cmc_command_line_set_arguments(options, status, size, argc, argv);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot set optional arguments\n", stderr);
    cmc_command_line_free_arguments(options, size);
    return;
  }

  cmc_command_line_set_default(options, size);
}
