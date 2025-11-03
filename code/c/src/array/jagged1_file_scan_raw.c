#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "int.h"
#include "jagged_private.h"

jagged1 * jagged1_file_scan_raw(FILE * in)
{
  jagged1 * arr;

  arr = (jagged1 *) malloc(sizeof(jagged1));
  if (arr == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(jagged1), "arr");
    goto end;
  }

  arr->a0 = int_file_scan(in);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan arr->a0\n", stderr);
    goto arr_free;
  }
  if (arr->a0 < 0)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "arr->a0 = %d\n but it must be non-negative\n", arr->a0);
    errno = EINVAL;
    goto arr_free;
  }

  arr->a1 = int_array_file_scan(in, arr->a0, "--raw");
  if (arr->a1 == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan arr->a1\n", stderr);
    goto arr_free;
  }

  return arr;

  /* cleaning if an error occurs */
arr_free:
  free(arr);
end:
  return NULL;
}
