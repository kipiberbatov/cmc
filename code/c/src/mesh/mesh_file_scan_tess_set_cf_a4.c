#include <string.h>

#include "mesh_file_scan_tess_private.h"

void mesh_file_scan_tess_set_cf_a4(
  int * cf_a4,
  int cn_1,
  int cn_2,
  int faces_total_edges,
  const int * edges_to_nodes,
  const int * faces_number_of_sides,
  const int * faces_to_subfaces)
{
  int i, index, index_local, j, sides;

  memcpy(cf_a4, edges_to_nodes, sizeof(int) * 2 * cn_1);
  index = 2 * cn_1;
  index_local = 0;
  for (i = 0; i < cn_2; ++i)
  {
    sides = faces_number_of_sides[i];
    for (j = 0; j < sides; ++j)
    {
      cf_a4[index + j] = faces_to_subfaces[index_local + j];
      cf_a4[faces_total_edges + index + j]
      = faces_to_subfaces[index_local + sides + j];
    }
    index += sides;
    index_local += 2 * sides;
  }
}
