#include "cmc_error_message.h"
#include "double_array.h"
#include "int.h"
#include "mesh_brick.h"

mesh * mesh_brick_regular(int d, int n)
{
  int partitions[MAX_DIM];
  double brick_lengths[MAX_DIM];
  mesh * m;

  int_array_assign_constant(partitions, d, n);
  double_array_assign_constant(brick_lengths, d, 1.);
  m = mesh_brick(d, brick_lengths, partitions);
  if (m == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m\n", stderr);
    return NULL;
  }
  return m;
}
