#include "cmc_error_message.h"
#include "cmc_command_line.h"

void cmc_command_line_file_print(
  FILE * out, int size, cmc_command_line ** options)
{
  int i, j, size_j, total_j;
  void * data_j_i, * data_j;
  const cmc_command_line * option_j;

  for (j = 0; j < size; ++j)
  {
    option_j = options[j];
    size_j = option_j->type_size;
    data_j = option_j->arguments;
    total_j = option_j->number_of_arguments;
    if (j < size - 1)
      fprintf(out, "%s[%d] ->", option_j->name, total_j);
    else
      fprintf(out, "positional_arguments[%d] ->", total_j);
    for (i = 0; i < total_j; ++i)
    {
      fputc(' ', out);
      data_j_i = (void *) ((char *) data_j + size_j * i);
      option_j->file_print(out, data_j_i);
    }
    fputc('\n', out);
  }
}
