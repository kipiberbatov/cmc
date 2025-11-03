#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "int.h"
#include "jagged.h"
#include "vector_sparse_private.h"

static int all_values_in_range(
  int a_length, int a_nonzero_max, const int * a_positions)
{
  int i;

  for (i = 0; i < a_nonzero_max; ++i)
    if (a_positions[i] < 0 || a_positions[i] >= a_length)
      return 0;
  return 1;
}

static int all_values_different(int a_nonzero_max, const int * a_positions)
{
  int i, j;

  for (i = 0; i < a_nonzero_max - 1; ++i)
    for (j = i + 1; j < a_nonzero_max; ++j)
      if (a_positions[i] == a_positions[j])
        return 0;
  return 1;
}

static int vector_sparse_positions_possible(
  int a_length, int a_nonzero_max, const int * a_positions)
{
  if (!all_values_in_range(a_length, a_nonzero_max, a_positions))
    return 0;
  if (!all_values_different(a_nonzero_max, a_positions))
    return 0;
  return 1;
}

vector_sparse * vector_sparse_file_scan_raw(FILE * in)
{
  vector_sparse * a;

  a = (vector_sparse *) malloc(sizeof(vector_sparse));
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(vector_sparse), "a");
    goto end;
  }

  a->length = int_file_scan(in);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan a->length\n", stderr);
    goto a_free;
  }
  if (a->length <= 0)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("a->length is nonpositive\n", stderr);
    errno = EINVAL;
    goto a_free;
  }

  a->nonzero_max = int_file_scan(in);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan a->nonzero_max\n", stderr);
    goto a_free;
  }
  if (a->nonzero_max <= 0 || a->nonzero_max > a->length)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "a->nonzero_max = %d is not in [0, %d)\n",
      a->nonzero_max, a->length);
    errno = EINVAL;
    goto a_free;
  }

  a->positions = int_array_file_scan(in, a->nonzero_max, "--raw");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan a->positions in format --raw\n", stderr);
    goto a_free;
  }
  if(!vector_sparse_positions_possible(a->length, a->nonzero_max, a->positions))
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("a->positions is impossible\n", stderr);
    errno = EINVAL;
    goto a_positions_free;
  }

  a->values = double_array_file_scan(in, a->nonzero_max, "--raw");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan a->values in format --raw\n", stderr);
    goto a_positions_free;
  }

  return a;

  /* cleaning if an error occurs */
a_positions_free:
  free(a->positions);
a_free:
  free(a);
end:
  return NULL;
}
