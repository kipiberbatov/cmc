#include <errno.h>
#include <string.h>

#include "cmc_error_message.h"
#include "mesh.h"

mesh * mesh_file_scan_by_name(const char * name, const char * format)
{
  FILE * in;
  mesh * m = NULL;

  in = fopen(name, "r");
  if (in == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open file %s%s%s for reading: %s%s%s\n",
      color_variable, name, color_none,
      color_stdlib, strerror(errno), color_none);
    goto end;
  }

  m = mesh_file_scan(in, format);
  if (m == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh m from file %s%s%s in format %s%s%s\n",
      color_variable, name, color_none,
      color_variable, format, color_none);
    goto in_close;
  }

in_close:
  fclose(in);
end:
  return m;
}
