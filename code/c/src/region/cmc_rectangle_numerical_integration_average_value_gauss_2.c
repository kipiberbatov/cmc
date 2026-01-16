#include <math.h>

#include "cmc_rectangle.h"

/*
Average value of Gaussian numerical integration on a rectangle with 2 * 2 points
(the images of {(s_x / sqrt(3), s_y / sqrt(3)) | s_x, s_y in {-1, 1}} when they
are located on the rectangle [-1, 1] * [-1, 1])
*/
double cmc_rectangle_numerical_integration_average_value_gauss_2(
  const struct cmc_rectangle * rectangle, double (*f)(const double *))
{
  double result, sqrt_3, x0, x1, x_middle, x_rest, y0, y1, y_middle, y_rest;
  double point[2];

  sqrt_3 = sqrt(3);
  x0 = rectangle->x0;
  x1 = rectangle->x1;
  y0 = rectangle->y0;
  y1 = rectangle->y1;
  x_middle = (x0 + x1) / 2.;
  x_rest = (x1 - x0) / (2. * sqrt_3);
  y_middle = (y0 + y1) / 2.;
  y_rest = (y1 - y0) / (2. * sqrt_3);

  /* - - */
  point[0] = x_middle - x_rest;
  point[1] = y_middle - y_rest;
  result = f(point);

  /* - + */
  point[1] = y_middle + y_rest;
  result += f(point);

  /* + + */
  point[0] = x_middle + x_rest;
  result += f(point);

  /* + - */
  point[1] = y_middle - y_rest;
  result += f(point);

  return result / 4;
}
