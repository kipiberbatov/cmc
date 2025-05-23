#include <math.h>

#include "double_array.h"

double double_array_lebesgue_norm(double p, int d, const double * a)
{
  int i;
  double result = 0;

  for (i = 0; i < d; ++i)
    result += pow(fabs(a[i]), p);
  result = pow(result, 1 / p);
  return result;
}
