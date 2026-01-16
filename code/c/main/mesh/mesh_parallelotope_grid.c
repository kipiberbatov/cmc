#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "double.h"
#include "int.h"
#include "mesh_brick.h"
#include "mesh_parallelotope_grid.h"

static void mesh_parallelotope_grid_file_print_raw(FILE * out,
  int d, int n, const double * origin,
  const double * directions, const int * partitions)
{
  int p;
  int m_bd_sizes[MAX_DIM];
  mesh * m;
  int ** m_bd;

  m = mesh_parallelotope_grid(d, n, origin, directions, partitions);
  if (m == NULL)
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
  int d, index, n, p, s;
  int partitions[MAX_DIM];
  double origin[MAX_DIM], directions[MAX_DIM * MAX_DIM];
  double * directions_p;

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
      fprintf(stderr, "dimension %d but it must be nonnegative\n", d);
    errno = EINVAL;
    return errno;
  }

  n = int_string_scan(argv[2]);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan embedding dimension d from string %s\n", argv[2]);
    return errno;
  }

  if (n > MAX_DIM || n < 0)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    if (d > MAX_DIM)
      fprintf(stderr,
        "embedding dimension %d is too big; limit is %d\n",
        d, MAX_DIM);
    else
      fprintf(stderr,
        "embedding dimension is %d but it must be nonnegative\n",
        d);
    errno = EINVAL;
    return errno;
  }

  if (argc < 3 + n + n * d + d)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "the number of command line arguments should be at least %d: use as\n"
      "%s %d %d origin[%d] directions[%d * %d] partitions[%d]",
      3 + n + n * d + d, argv[0], d, n, n, d, n, d);
    return errno;
  }

  index = 3;
  for (s = 0; s < n; ++s)
  {
    origin[s] = double_string_scan(argv[index + s]);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot scan origin[%d] from string %s\n",
        s, argv[index + s]);
      return errno;
    }
  }
  index += n;

  for (p = 0; p < d; ++p)
  {
    directions_p = directions + p * n;
    for (s = 0; s < n; ++s)
    {
      directions_p[s] = double_string_scan(argv[index + s]);
      if (errno)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fprintf(stderr, "cannot scan direction_%d[%d] from string %s\n",
          p, s, argv[index + s]);
        return errno;
      }
    }
    index += n;
  }

  for (p = 0; p < d; ++p)
  {
    partitions[p] = int_string_scan(argv[index + p]);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot scan partitions[%d] from string %s\n",
        p, argv[index + p]);
      return errno;
    }
  }

  mesh_parallelotope_grid_file_print_raw(stdout,
    d, n, origin, directions, partitions);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate and print m and m->bd\n", stderr);
    return errno;
  }

  return 0;
}
