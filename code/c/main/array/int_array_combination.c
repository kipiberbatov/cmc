#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "int.h"

static void int_array_combination_file_print(FILE * out, int m, int n)
{
  int prod, i;
  int * a;

  prod = int_binomial(m, n);
  a = (int *) malloc(sizeof(int) * n);
  if (a == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(int) * n, "a");
    return;
  }
  int_array_assign_identity(a, n);
  i = 0;
  while(i < prod - 1)
  {
    int_array_file_print(out, n, a, "--raw");
    int_array_combination_next(a, m, n);
    ++i;
  }
  int_array_file_print(out, n, a, "--raw");
  free(a);
}

int main(int argc, char ** argv)
{
  int m, n;

#define ARGC 3
  if (argc != ARGC)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_number_of_command_line_arguments_mismatch(ARGC, argc);
    return EINVAL;
  }

  m = int_string_scan(argv[1]);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan total number of elements m from string %s\n",
      argv[1]);
    goto end;
  }
  if (m < 0)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "total number of elements %d is negative\n", m);
    errno = EINVAL;
    goto end;
  }

  n = int_string_scan(argv[2]);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan subsets size n from string %s\n", argv[2]);
    goto end;
  }
  if (n < 0)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "subsets size %d is negative\n", n);
    errno = EINVAL;
    goto end;
  }

  int_array_combination_file_print(stdout, m, n);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot print %d-element combinations of the set {0, ..., %d}\n",
      n, m - 1);
    goto end;
  }
end:
  return errno;
}
