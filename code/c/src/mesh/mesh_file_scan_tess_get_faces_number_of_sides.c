#include <errno.h>

#include "cmc_error_message.h"
#include "double.h"
#include "int.h"
#include "mesh_file_scan_tess_private.h"

void mesh_file_scan_tess_get_faces_number_of_sides(
  int * faces_number_of_sides, FILE * in, int * error, int cn_2)
{
  int c_i, i, j, tmp, x;

  for (i = 0; i < cn_2; ++i)
  {
    c_i = int_file_scan(in);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot scan %d-th 1-cell id\n", i);
      *error = errno;
      return;
    }
    if (c_i != (i + 1))
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "invalid edge index: %d != %d\n", c_i, i + 1);
      *error = 1;
      return;
    }

    faces_number_of_sides[i] = int_file_scan(in);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot scan %d-th 2-cell number of sides\n", i);
      *error = errno;
      return;
    }
    if (faces_number_of_sides[i] < 3)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr,
        " i = %d, number of sides must be at least 3; instead it is %d\n",
        i, faces_number_of_sides[i]);
      *error = 1;
      return;
    }

    for (j = 0; j < faces_number_of_sides[i]; ++j)
    {
      x = int_file_scan(in);
      if (errno)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fprintf(stderr, "unable to scan subface (%d, %d)\n", i, j);
        *error = errno;
        return;
      }
      if (x <= 0)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fprintf(stderr,
          "index of a vertex must be positive; instead it is %d\n",
          x);
        *error = 1;
        return;
      }
    }

    tmp = int_file_scan(in);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr,"cannot scan %d-th 2-cell number of sides\n", i);
      *error = errno;
      return;
    }
    if (faces_number_of_sides[i] != tmp)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr,
        "i = %d, number of sides should be %d; instead it is %d\n",
        i, tmp, faces_number_of_sides[i]);
      *error = 1;
      return;
    }

    for (j = 0; j < faces_number_of_sides[i]; ++j)
    {
      x = int_file_scan(in);
      *error = errno;
      if (*error)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fprintf(stderr, "unable to scan subface (%d, %d)\n", i, j);
        return;
      }
    }

    for (j = 0; j < 9; ++j)
    {
      double_file_scan(in);
      if (errno)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fprintf(stderr, "missing value, (i, j) = (%d, %d)\n", i, j);
        *error = errno;
        return;
      }
    }
  }
}
