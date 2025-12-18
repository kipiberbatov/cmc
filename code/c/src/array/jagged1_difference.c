#include <stdlib.h>

#include "cmc_error_message.h"
#include "jagged.h"

jagged1 * jagged1_difference(const jagged1 * y, const jagged1 * x)
{
  int i, index, y_a0, z_a0;
  int * y_a1, * z_a1;
  jagged1 * z;

  y_a0 = y->a0;
  y_a1 = y->a1;

  z = (jagged1 *) malloc(sizeof(jagged1));
  if (z == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for z\n", sizeof(jagged1));
    return NULL;
  }

  z_a0 = y->a0;
  for (i = 0; i < y_a0; ++i)
    if (jagged1_member(x, y_a1[i]))
      --z_a0;

  z_a1 = (int *) malloc(sizeof(int) * z_a0);
  if (z_a1 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for z_a1\n", sizeof(int) * z_a0);
    free(z);
    return NULL;
  }

  index = 0;
  for (i = 0; i < y_a0; ++i)
  {
    if (!jagged1_member(x, y_a1[i]))
    {
      z_a1[index] = y_a1[i];
      ++index;
    }
  }

  z->a0 = z_a0;
  z->a1 = z_a1;
  return z;
}
