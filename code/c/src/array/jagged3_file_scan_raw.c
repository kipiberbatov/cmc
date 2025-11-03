#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "int.h"
#include "jagged_private.h"

jagged3 * jagged3_file_scan_raw(FILE * in)
{
  int arr_a2_size, arr_a3_size;
  jagged3 * arr;

  arr = (jagged3 *) malloc(sizeof(jagged3));
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(jagged3), "arr");
    goto end;
  }

  arr->a0 = int_file_scan(in);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan arr->a0 from input\n", stderr);
    goto arr_free;
  }
  if (arr->a0 <= 0)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "arr->a0 = %d but it must be positive\n", arr->a0);
    errno = EINVAL;
    goto arr_free;
  }

  arr->a1 = int_array_file_scan(in, arr->a0, "--raw");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan arr->a1 in format --raw\n", stderr);
    goto arr_free;
  }
  if (!int_array_positive(arr->a0, arr->a1))
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("arr->a1 is nonpositive\n", stderr);
    errno = EINVAL;
    goto arr_a1_free;
  }

  arr_a2_size = int_array_total_sum(arr->a0, arr->a1);
  arr->a2 = int_array_file_scan(in, arr_a2_size, "--raw");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan arr->a2 in format --raw\n", stderr);
    goto arr_a1_free;
  }
  if (!int_array_positive(arr_a2_size, arr->a2))
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("arr->a2 is nonpositive\n", stderr);
    errno = EINVAL;
    goto arr_a2_free;
  }

  arr_a3_size = int_array_total_sum(arr_a2_size, arr->a2);
  arr->a3 = int_array_file_scan(in, arr_a3_size, "--raw");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan arr->a3 in format --raw\n", stderr);
    goto arr_a2_free;
  }
  return arr;

  /* cleaning if an error occurs */
arr_a2_free:
  free(arr->a2);
arr_a1_free:
  free(arr->a1);
arr_free:
  free(arr);
end:
  return NULL;
}
