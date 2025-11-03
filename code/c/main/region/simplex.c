#include <errno.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "simplex.h"

static void simplex_measure_file_print(FILE * out, const simplex * r)
{
  double r_area;

  r_area = simplex_measure(r);
  fprintf(out, "area : %g\n", r_area);
}

static void simplex_centroid_file_print(FILE * out, const simplex * r)
{
  double r_centroid[3];

  simplex_centroid(r_centroid, r);
  fputs("centroid : ", out);
  double_array_file_print(out, r->dim_embedded, r_centroid, "--raw");
  fputc('\n', out);
}

int main(void)
{
  simplex * r;
  FILE * in, * out;

  out = stdout;
  in = stdin;
  r = simplex_file_scan(in);
  if (r == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan simplex r\n", stderr);
    return errno;
  }
  simplex_measure_file_print(out, r);
  simplex_centroid_file_print(out, r);
  simplex_free(r);
  return 0;
}
