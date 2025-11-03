#include <errno.h>

#include "cmc_error_message.h"
#include "double.h"
#include "int.h"
#include "mesh_file_scan_tess_private.h"

#define EPSILON .0000000001

void mesh_file_scan_tess_get_coordinates(double * coordinates, FILE * in,
  int * error, int d, int cn_0)
{
  int c_i, i, j;
  double x;

  for (i = 0; i < cn_0; ++i)
  {
    c_i = int_file_scan(in);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot scan %d-th 0-cell id\n", i);
      *error = errno;
      return;
    }
    if (c_i != (i + 1))
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "invalid vertex index: %d != %d\n", c_i, i + 1);
      *error = 1;
      return;
    }
    for (j = 0; j < d; ++j)
    {
      x = double_file_scan(in);
      if (errno)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fprintf(stderr, "unable to scan coordinate (%d, %d)\n", i, j);
        *error = errno;
        return;
      }
      if (x < EPSILON && -x < EPSILON)
        coordinates[d * i + j] = 0;
      else
        coordinates[d * i + j] = x;
    }
    for (j = d; j < 4; ++j)
    {
      x = double_file_scan(in);
      if (errno)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fprintf(stderr, "missing value\n");
        *error = errno;
        return;
      }
      if (x != 0)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fprintf(stderr,
          "i = %d, last values must be zeroes; instead we have %g\n",
          i, x);
        *error = 1;
        return;
      }
    }
  }
}
