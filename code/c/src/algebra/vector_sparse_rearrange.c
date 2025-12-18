#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "array_indexed.h"
#include "cmc_error_message.h"
#include "double_array.h"
#include "int.h"
#include "jagged.h"
#include "vector_sparse.h"

void vector_sparse_rearrange(vector_sparse * b)
{
  double * b_values_new;
  jagged1 positions;
  array_indexed a;

  positions.a0 = b->nonzero_max;
  positions.a1 = (int *) malloc(sizeof(int) * positions.a0);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannnot allocate %zu bytes of memory for for positions.a1\n",
      sizeof(int) * positions.a0);
    goto end;
  }

  a.positions = positions.a1;
  int_array_assign_identity(a.positions, positions.a0);
  a.values = b->positions;

  array_indexed_merge_sort(&a, positions.a0);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannnot merge sort a\n");
    goto positions_a1_free;
  }

  b_values_new = (double *) malloc(sizeof(double) * b->nonzero_max);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannnot allocate %zu bytes of memory for for b_values_new\n",
      sizeof(double) * positions.a0);
    goto positions_a1_free;
  }

  double_array_compress_to_sparse_array(b_values_new, &positions, b->values);
  memcpy(b->values, b_values_new, sizeof(double) * positions.a0);

  free(b_values_new);
positions_a1_free:
  free(positions.a1);
end:
  return;
}
