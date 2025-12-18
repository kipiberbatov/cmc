#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "int.h"
#include "mesh_disk_polar.h"

int main(int argc, char ** argv)
{
  int m_bd_values_size, na, nd;
  double * m_bd_values;
  mesh * m;

  if (argc != 3)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "number of command-line arguments should be 3;"
      "instead it is %d\n", argc);
    goto end;
  }

  na = int_string_scan(argv[1]);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan number of angles na\n", stderr);
    goto end;
  }

  nd = int_string_scan(argv[2]);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan number of disks nd\n", stderr);
    goto end;
  }

  m = mesh_disk_polar(na, nd, 1, 0, 0);
  if (m == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan number of disks nd\n", stderr);
    goto end;
  }

  m_bd_values_size = na * (8 * nd - 1);
  m_bd_values = (double *) malloc(sizeof(double) * m_bd_values_size);
  if (m_bd_values == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot allocate %zu bytes of memory for m_bd_values\n",
      sizeof(double) * m_bd_values_size);
    goto m_free;
  }
  mesh_disk_polar_boundary_values(m_bd_values, na, nd);

  mesh_file_print(stdout, m, "--raw");
  double_array_file_print(stdout, m_bd_values_size, m_bd_values, "--raw");

  free(m_bd_values);
m_free:
  mesh_free(m);
end:
  return errno;
}
