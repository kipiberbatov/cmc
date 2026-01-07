#include <errno.h>

#include "cmc_error_message.h"
#include "double.h"
#include "int.h"
#include "mesh_file_scan_tess_private.h"

void mesh_file_scan_tess_get_cells_to_faces_number_2_1(
  int * cfn_2_1, FILE * in, int * status, int cn_2)
{
  int c_i, i, j, tmp, x;

  for (i = 0; i < cn_2; ++i)
  {
    c_i = int_file_scan(in);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot scan %d-th 1-cell id\n", i);
      *status = errno;
      return;
    }
    if (c_i != (i + 1))
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "invalid edge index: %d != %d\n", c_i, i + 1);
      *status = 1;
      return;
    }

    cfn_2_1[i] = int_file_scan(in);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot scan %d-th 2-cell number of sides\n", i);
      *status = errno;
      return;
    }
    if (cfn_2_1[i] < 3)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr,
        " i = %d, number of sides must be at least 3; instead it is %d\n",
        i, cfn_2_1[i]);
      *status = 1;
      return;
    }

    for (j = 0; j < cfn_2_1[i]; ++j)
    {
      x = int_file_scan(in);
      if (errno)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fprintf(stderr, "unable to scan subface (%d, %d)\n", i, j);
        *status = errno;
        return;
      }
      if (x <= 0)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fprintf(stderr,
          "index of a vertex must be positive; instead it is %d\n",
          x);
        *status = 1;
        return;
      }
    }

    tmp = int_file_scan(in);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr,"cannot scan %d-th 2-cell number of sides\n", i);
      *status = errno;
      return;
    }
    if (cfn_2_1[i] != tmp)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr,
        "i = %d, number of sides should be %d; instead it is %d\n",
        i, tmp, cfn_2_1[i]);
      *status = 1;
      return;
    }

    for (j = 0; j < cfn_2_1[i]; ++j)
    {
      x = int_file_scan(in);
      *status = errno;
      if (*status)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fprintf(stderr, "unable to scan subface (%d, %d)\n", i, j);
        return;
      }
    }

    mesh_file_scan_tess_skip_garbage_face_values(in, status, i);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot skip garbage values for cell %d\n", i);
      return;
    }
  }
}
