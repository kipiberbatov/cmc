#include <string.h>

#include "string_private.h"

void string_locate_in_file_line(FILE * file, int * status, const char * s)
{
  char line[81];

  while (fgets(line, sizeof(line), file))
  {
    line[strcspn(line, "\r\n")] = '\0';
    if (strcmp(line, s) == 0)
      return;
  }
  *status = 1;
}
