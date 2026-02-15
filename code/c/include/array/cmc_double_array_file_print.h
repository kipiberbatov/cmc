#include <stdio.h>

struct cmc_double_array;

void cmc_double_array_file_print(
  FILE * out,
  int * status,
  const struct cmc_double_array * data,
  const char * format);
