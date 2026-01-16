#include "jagged.h"

int jagged1_part1(const jagged1 * arr, int i1)
{
  int p1;

  /* undefined behaviour if (i1 < 0 || i1 >= arr->a0) */
  p1 = arr->a1[i1];

  return p1;
}
