#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "int.h"
#include "mesh_brick.h"

static void mesh_brick_regular_file_print_raw(FILE * out, int d, int n)
{
  int p;
  int m_bd_sizes[MAX_DIM], partitions[MAX_DIM];
  mesh * m;
  int ** m_bd;

  m = mesh_brick_regular(d, n);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m\n", stderr);
    goto end;
  }
  mesh_file_print(out, m, "--raw");

  int_array_assign_constant(partitions, d, n);
  for (p = 1; p <= d; ++p)
    m_bd_sizes[p - 1] = mesh_boundary_nonzero_max(m, p);

  m_bd = mesh_brick_boundary(m->dim, partitions, m_bd_sizes);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m->bd\n", stderr);
    goto m_free;
  }
  for (p = 0; p < d; ++p)
    int_array_file_print(out, m_bd_sizes[p], m_bd[p], "--raw");

  int_array2_free(m_bd, d);
m_free:
  mesh_free(m);
end:
  return;
}

int main(int argc, char ** argv)
{
  int d, n;

#define ARGC 3
  if (argc != 3)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_number_of_command_line_arguments_mismatch(ARGC, argc);
    errno = EIO;
    goto end;
  }

  d = int_string_scan(argv[1]);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan dimension d\n", stderr);
    goto end;
  }

  if (d > MAX_DIM || d < 0)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    if (d > MAX_DIM)
      fprintf(stderr, "dimension %d is too big; limit is %d\n", d, MAX_DIM);
    else
      fprintf(stderr, "dimension is too%d but it must be nonnegative\n", d);
    errno = EINVAL;
    goto end;
  }

  n = int_string_scan(argv[2]);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan number of partitions n\n", stderr);
    goto end;
  }

  if (n <= 0)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "number of partitions %d must be positive\n", n);
    errno = EINVAL;
    goto end;
  }

  mesh_brick_regular_file_print_raw(stdout, d, n);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot generate and print mesh m\n", stderr);
    goto end;
  }

end:
  return errno;
}
