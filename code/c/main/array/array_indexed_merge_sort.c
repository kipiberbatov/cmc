#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "array_indexed.h"
#include "cmc_error_message.h"
#include "int.h"
#include "jagged.h"

int main(void)
{
  int n;
  jagged1 * arr = NULL;
  array_indexed a;
  FILE * in, * out;

  out = stdout;
  in = stdin;

  arr = jagged1_file_scan(in, "--raw");
  if (arr == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan arr in format --raw\n", stderr);
    goto end;
  }

  n = arr->a0;

  a.positions = (int *) malloc(sizeof(int) * n);
  if (a.positions == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytes of memory for a.positions\n",
      sizeof(int) * n);
    goto arr_free;
  }
  int_array_assign_identity(a.positions, n);

  a.values = (int *) malloc(sizeof(int) * n);
  if (a.values == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %ld bytes of memory for a.positions\n",
      sizeof(int) * n);
    goto a_positions_free;
  }
  memcpy(a.values, arr->a1, sizeof(int) * n);

  array_indexed_merge_sort(&a, n);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot merge sort a\n", stderr);
    goto a_values_free;
  }

  fprintf(stdout, "%d\n", arr->a0);
  int_array_file_print(out, n, a.values, "--raw");

a_values_free:
  free(a.values);
a_positions_free:
  free(a.positions);
arr_free:
  jagged1_free(arr);
end:
  return errno;
}
