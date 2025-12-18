#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "int.h"
#include "simplex.h"

simplex * simplex_file_scan(FILE * in)
{
  simplex * s;

  s = (simplex *) malloc(sizeof(simplex));
  if (s == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for s\n",
      sizeof(simplex));
    goto end;
  }

  s->dim_embedded = int_file_scan(in);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan s->dim_embedded\n", stderr);
    goto end;
  }

  s->dim = int_file_scan(in);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan s->dim\n", stderr);
    goto end;
  }

  s->coord = double_array_file_scan(
    in, s->dim_embedded * (1 + s->dim), "--raw");
  if (s->coord == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan s->coord\n", stderr);
    goto s_free;
  }
  return s;

  /* cleaning if an error occurs */
s_free:
  free(s);
end:
  return NULL;
}
