#include "cmc_memory.h"
#include "cmc_double_array__struct.h"
#include "cmc_double_array_free_values.h"

void cmc_double_array_free_values(struct cmc_double_array * data)
{
  cmc_memory_free(data->values);
}
