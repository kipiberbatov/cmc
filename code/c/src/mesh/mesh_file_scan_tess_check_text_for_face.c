#include <string.h>

#include "cmc_error_message.h"
#include "mesh_file_scan_tess_private.h"
#include "string_private.h"

void mesh_file_scan_tess_check_text_for_face(FILE * in, int * status)
{
  const char str[] = "\n **face\n ";
  char buffer[sizeof(str)];

  string_file_scan(in, buffer, sizeof(buffer));
  if (strcmp(buffer, str))
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "expected\n\n%s\n\n", str);
    fprintf(stderr, "Instead, we have\n\n%s\n\n", buffer);
    *status = 1;
    return;
  }
}
