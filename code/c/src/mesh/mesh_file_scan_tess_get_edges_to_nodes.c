#include <errno.h>

#include "cmc_error_message.h"
#include "int.h"
#include "mesh_file_scan_tess_private.h"

void mesh_file_scan_tess_get_edges_to_nodes(int * edges_to_nodes, FILE * in,
  int * status, int cn_1)
{
  int c_i, i, j, x;

  for (i = 0; i < cn_1; ++i)
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
    for (j = 0; j <= 1; ++j)
    {
      edges_to_nodes[2 * i + j] = int_file_scan(in);
      if (errno)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fprintf(stderr, "unable to scan edge node (%d, %d)\n", i, j);
        *status = errno;
        return;
      }
      --edges_to_nodes[2 * i + j];
    }
    x = int_file_scan(in);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "missing value, i = %d\n", i);
      *status = errno;
      return;
    }
    if (x != 0)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr,
        "i = %d, last values must be zeroes; instead we have %d\n",
        i, x);
      *status = 1;
      return;
    }
  }
}
