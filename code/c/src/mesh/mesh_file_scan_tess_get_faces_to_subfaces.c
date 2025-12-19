#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "double.h"
#include "int.h"
#include "mesh_file_scan_tess_private.h"

/* error is impossible there, as data is checked on the previous call */
void mesh_file_scan_tess_get_faces_to_subfaces(int * faces_to_subfaces,
  FILE * in, int cn_2, int faces_total_edges)
{
  int faces_number_of_sides_i, i, index, j;

  index = 0;
  for (i = 0; i < cn_2; ++i)
  {
    int_file_scan(in); /* c_i; */
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot scan integer for i = %d\n", i);
      return;
    }

    faces_number_of_sides_i = int_file_scan(in);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot scan faces_number_of_sides[%d]\n", i);
      return;
    }
    if (faces_number_of_sides_i <= 2)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr,
        "faces_number_of_sides[%d] should be at least 3; instead it is %d\n",
        i, faces_number_of_sides_i);
      errno = 1;
      return;
    }
    for (j = 0; j < faces_number_of_sides_i; ++j)
    {
      faces_to_subfaces[index] = int_file_scan(in) - 1;
      if (errno)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fprintf(stderr, "cannot scan faces_to_subfaces[%d]\n", index);
        return;
      }
      ++index;
    }

    faces_number_of_sides_i = int_file_scan(in);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot scan faces_number_of_sides[%d]\n", i);
      return;
    }
    for (j = 0; j < faces_number_of_sides_i; ++j)
    {
      faces_to_subfaces[index] = abs(int_file_scan(in)) - 1;
      if (errno)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fprintf(stderr, "cannot scan faces_to_subfaces[%d]\n", index);
        return;
      }
      ++index;
    }

    for (j = 0; j < 9; ++j)
    {
      double_file_scan(in);
      if (errno)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fprintf(stderr, "unable to skip garbage value[%d]\n", j);
        return;
      }
    }
  }
}
