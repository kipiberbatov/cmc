#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "array_indexed.h"
#include "cmc_error_message.h"

static void update(array_indexed * b, int * i, int * k, const array_indexed * a)
{
  b->positions[*k] = a->positions[*i];
  b->values[*k] = a->values[*i];
  ++*i;
  ++*k;
}

static void array_indexed_merge_sort_ordered(
  array_indexed * a, array_indexed * b, int begin, int middle, int end)
{
  int i, j, k, length;
  int * a_values;

  a_values = a->values;
  i = begin;
  j = middle + 1;
  k = begin;

  while (i <= middle && j <= end)
  {
    if (a_values[i] <= a_values[j])
      update(b, &i, &k, a);
    else
      update(b, &j, &k, a);
  }

  if (i == middle + 1)
    while (j <= end)
      update(b, &j, &k, a);
  else
    while (i <= middle)
      update(b, &i, &k, a);

  length = end - begin + 1;
  memcpy(a->positions + begin, b->positions + begin, sizeof(int) * length);
  memcpy(a_values + begin, b->values + begin, sizeof(int) * length);
}

static void array_indexed_merge_sort_loc(
  array_indexed * a, array_indexed * b, int begin, int end)
{
  int middle = (begin + end) / 2;
  if (begin == end)
    return;
  array_indexed_merge_sort_loc(a, b, begin, middle);
  array_indexed_merge_sort_loc(a, b, middle + 1, end);
  array_indexed_merge_sort_ordered(a, b, begin, middle, end);
}

void array_indexed_merge_sort(array_indexed * a, int n)
{
  array_indexed b;

  b.positions = (int *) malloc(sizeof(int) * n);
  if (b.positions == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for b.positions\n",
      sizeof(int) * n);
    goto end;
  }

  b.values = (int *) malloc(sizeof(int) * n);
  if (b.values == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for b.values\n",
      sizeof(int) * n);
    goto b_positions_free;
  }

  array_indexed_merge_sort_loc(a, &b, 0, n - 1);

  free(b.values);
b_positions_free:
  free(b.positions);
end:
  return;
}
