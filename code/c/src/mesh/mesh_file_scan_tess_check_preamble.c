#include <string.h>

#include "cmc_error_message.h"
#include "mesh_file_scan_tess_private.h"
#include "string_private.h"

void mesh_file_scan_tess_check_preamble(FILE * in, int * error)
{
  char buffer[30];
  char * str;

  /* check for "***tess\n *format\n   " */
  str = "***tess\n **format\n   ";
  string_file_scan(in, buffer, strlen(str) + 1);
  if (strcmp(buffer, str))
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "expected\n\n%s\n\n", str);
    fprintf(stderr, "Instead, we have\n\n%s\n\n", buffer);
    *error = 1;
    return;
  }

  /* check for format's value (2.0, 3.3, or 3.4) */
  string_file_scan(in, buffer, 4);
  if (strcmp(buffer, "2.0") && strcmp(buffer, "3.3") && strcmp(buffer, "3.4"))
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("input file should have its format '2.0' or '3.3' or '3.4'\n",
      stderr);
    fprintf(stderr, "Instead, we have '%s'\n", str);
    *error = 1;
    return;
  }

  /* check for "\n **general\n   " */
  str = "\n **general\n   ";
  string_file_scan(in, buffer, strlen(str) + 1);
  if (strcmp(buffer, str))
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "expected\n\n%s\n\n", str);
    fprintf(stderr, "Instead, we have\n\n%s\n\n", buffer);
    *error = 1;
    return;
  }
}
