#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "jagged.h"

jagged1 * jagged1_complement(int n, const jagged1 * arr)
{
  int i, ind;
  jagged1 * res;

  res = (jagged1 *) malloc(sizeof(jagged1));
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(jagged1), "res");
    goto end;
  }

  res->a0 = n - arr->a0;

  res->a1 = (int *) malloc(sizeof(int) * res->a0);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(int) * res->a0, "res->a1");
    goto res_free;
  }

  ind = 0;
  for (i = 0; i < n; ++i)
  {
    if (!jagged1_member(arr, i))
    {
      res->a1[ind] = i;
      ++ind;
    }
  }

  return res;

  /* cleaning if an error occurs */
res_free:
  free(res);
end:
  return NULL;
}
