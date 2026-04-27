#include "int.h"

int int_binomial(int m, int n)
{
  int a_m, a_n, d, i_m, i_n, result;

  n = (m >= 2 * n ? n : m - n);
  result = 1;
  for (i_n = 1; i_n <= n; ++i_n)
  {
    i_m = m + 1 - i_n;
    d = int_greatest_common_divisor(i_m, i_n);
    a_m = i_m / d;
    a_n = i_n / d;
    result = (result / a_n) * a_m;
  }
  return result;
}
