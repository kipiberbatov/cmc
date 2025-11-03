#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "int.h"
#include "matrix_sparse.h"

static void
matrix_sparse_file_print_file_scan(FILE * out, FILE * in, char * format)
{
  matrix_sparse * a;

  a = matrix_sparse_file_scan(in, "--raw");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan matrix a in format --raw\n", stderr);
    goto a_free;
  }

  matrix_sparse_file_print(out, a, format);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot print matrix a in format %s\n", format);
    goto a_free;
  }

a_free:
  free(a);
}

static void matrix_sparse_array_file_print_file_scan(
  FILE * out, FILE * in, char * format, int d)
{
  int p;

  for (p = 0; p < d; ++p)
  {
    matrix_sparse_file_print_file_scan(out, in, format);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot scan %d-th matrix in format %s\n", p, format);
    }
    if (p < d - 1)
      fputc('\n', out);
  }
}

int main(int argc, char ** argv)
{
  char * format, * list;
  int d;

  format = argv[1];
  if (argc == 4)
  {
    list = argv[2];
    if (!strcmp(list, "list"))
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "%s != list\n", list);
      errno = EINVAL;
      return errno;
    }
    d = int_string_scan(argv[3]);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot scan dimension d from string %s\n", argv[3]);
      return errno;
    }
    matrix_sparse_array_file_print_file_scan(stdout, stdin, format, d);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "printf result in format %s\n", format);
      return errno;
    }
    return errno;
  }
  matrix_sparse_file_print_file_scan(stdout, stdin, format);
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "printf result in format %s\n", format);
    return errno;
  }
  return errno;
}
