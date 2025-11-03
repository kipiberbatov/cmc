#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "double_array_private.h"
#include "double_array_sequence_dynamic.h"
#include "int.h"

double_array_sequence_dynamic *
double_array_sequence_dynamic_file_scan(FILE * in)
{
  size_t type_size;
  int dimension, i, j, length;
  double ** values;
  double_array_sequence_dynamic * a;

  type_size = sizeof(double_array_sequence_dynamic);
  a = (double_array_sequence_dynamic *) malloc(type_size);
  if (a == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(type_size, "a");
    goto end;
  }

  length = int_file_scan(in);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan length\n", stderr);
    goto a_free;
  }

  dimension = int_file_scan(in);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan dimension\n", stderr);
    goto a_free;
  }

  values = malloc(sizeof(double) * length);
  if (values == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * length, "values");
    goto a_free;
  }

  for (i = 0; i < length; ++i)
  {
    values[i] = double_array_file_scan_raw(in, dimension);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr,
        "cannot scan values[%s%d%s]\n",
        color_variable, i, color_none);
      goto values_free;
    }
  }
  a->length = length;
  a->dimension = dimension;
  a->capacity = length;
  a->values = values;
  return a;

  /* cleaning if an error occurs */
values_free:
  for (j = i - 1; j >= 0; --j)
    free(values[j]);
  free(values);
a_free:
  free(a);
end:
  return NULL;
}
