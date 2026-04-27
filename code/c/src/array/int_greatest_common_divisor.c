#include "int.h"

int int_greatest_common_divisor(int m, int n)
{
  int a;
  while (n != 0)
  {
    a = n;
    n = m % n;
    m = a;
  }
  return m;
}
