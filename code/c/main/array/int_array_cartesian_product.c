#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "int.h"

static void
int_array_cartesian_product_file_print(FILE * out, int d, const int * n)
{
  int prod, i;
  int * a;

  prod = int_array_total_product(d, n);
  a = (int *) calloc(d, sizeof(int));
  if (a == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytes of memory for a\n",
      sizeof(int) * d);
    return;
  }
  i = 0;
  while(i < prod - 1)
  {
    int_array_file_print(out, d, a, "--raw");
    int_array_cartesian_product_next(a, d, n);
    ++i;
  }
  int_array_file_print(out, d, a, "--raw");
  free(a);
}

int main(int argc, char ** argv)
{
  int d, p;
  int * n;

  if (argc == 1)
    return 0;

  d = argc - 1;
  n = (int *) malloc(sizeof(int) * d);
  if (n == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytes of memory for n\n",
      sizeof(int) * d);
    goto end;
  }
  for (p = 0; p < d; ++p)
  {
    n[p] = int_string_scan(argv[1 + p]);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot scan n[%d] from string %s\n", p, argv[1 + p]);
      goto n_free;
    }
  }
  int_array_cartesian_product_file_print(stdout, d, n);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot print Cartesian products\n", stderr);
    goto n_free;
  }
n_free:
  free(n);
end:
  return errno;
}
