#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "double.h"
#include "int.h"
#include "mesh_brick.h"

static void mesh_brick_file_print_raw(
  FILE * out, int d, const double * brick_lengths, const int * partitions)
{
  int p;
  int m_bd_sizes[MAX_DIM];
  mesh * m;
  int ** m_bd;

  m = mesh_brick(d, brick_lengths, partitions);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate mesh m\n", stderr);
    goto end;
  }
  mesh_file_print(out, m, "--raw");

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
  int d, p;
  int partitions[MAX_DIM];
  double brick_lengths[MAX_DIM];

  if (argc == 1)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs(
      "there are no command line arguments, but dimension must be specified\n",
      stderr);
    return EINVAL;
  }

  d = int_string_scan(argv[1]);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan dimension d from string %s\n", argv[1]);
    return errno;
  }

  if (d > MAX_DIM || d < 0)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    if (d > MAX_DIM)
      fprintf(stderr, "dimension %d is too big; limit is %d\n", d, MAX_DIM);
    else
      fprintf(stderr, "dimension is too%d but it must be nonnegative\n", d);
    errno = EINVAL;
    return errno;
  }

  if (argc < 2 * d + 2)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "the number of command line arguments should be at least %d: use as\n"
      "%s %d brick_lengths[%d] axes_partitions[%d]",
      2 * d + 2, argv[0], d, d, d);
    return errno;
  }

  for (p = 0; p < d; ++p)
  {
    brick_lengths[p] = double_string_scan(argv[2 + p]);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot scan brick_lengths[%d] from string %s\n",
        p, argv[2 + p]);
      return errno;
    }
  }

  for (p = 0; p < d; ++p)
  {
    partitions[p] = int_string_scan(argv[2 + d + p]);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot scan partitions[%d] from string %s\n",
        p, argv[2 + d + p]);
      return errno;
    }
  }

  mesh_brick_file_print_raw(stdout, d, brick_lengths, partitions);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate and print m->bd\n", stderr);
    return errno;
  }

  return 0;
}
