#include <errno.h>

#include "cmc_error_message.h"
#include "jagged.h"

int main(void)
{
  jagged4 * arr;

  arr = jagged4_file_scan(stdin, "--raw");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan arr in format --raw\n", stderr);
    return errno;
  }
  jagged4_file_print(stdout, arr, "--curly");

  jagged4_free(arr);
  return 0;
}
