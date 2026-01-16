#include "cmc_rectangle.h"

/*
Average value of Gaussian numerical integration on a rectangle with a single
point (the centre)
*/
double cmc_rectangle_numerical_integration_average_value_gauss_1(
  const struct cmc_rectangle * rectangle, double (*f)(const double *))
{
  double point[2];

  point[0] = (rectangle->x0 + rectangle->x1) / 2;
  point[1] = (rectangle->y0 + rectangle->y1) / 2;

  return f(point);
}
