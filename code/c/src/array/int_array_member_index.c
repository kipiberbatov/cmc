#include "int.h"

int int_array_member_index(int n, const int * a, int element)
{
  int i;

  for (i = 0; i < n; ++i)
    if (element == a[i])
      return i;
  return -1;
}
