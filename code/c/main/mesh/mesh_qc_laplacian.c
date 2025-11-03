#include <errno.h>
#include <string.h>

#include "cmc_error_message.h"
#include "mesh.h"

int main(int argc, char ** argv)
{
  int d;
  mesh * m;
  matrix_sparse ** m_bd, ** m_cbd, ** m_cbd_star;
  FILE * m_file, * m_cbd_star_file;

  if (argc != 3)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "Number of command line arguments must be 4\n");
    errno = EINVAL;
    goto end;
  }

  m_file = fopen(argv[1], "r");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot open mesh file %s: %s\n", argv[1], strerror(errno));
    goto end;
  }

  m = mesh_file_scan(m_file, "--raw");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan m\n", stderr);
    fclose(m_file);
    goto end;
  }
  d = m->dim;

  m->fc = mesh_fc(m);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m->fc\n", stderr);
    fclose(m_file);
    goto m_free;
  }

  m_bd = mesh_file_scan_boundary(m_file, m);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan m_bd\n", stderr);
    fclose(m_file);
    goto m_free;
  }

  fclose(m_file);

  m_cbd = mesh_coboundary(d, m_bd);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan m_cbd\n");
    goto m_bd_free;
  }

  m_cbd_star_file = fopen(argv[2], "r");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open m_cbd_star_file %s: %s\n",
      argv[2], strerror(errno));
    goto m_cbd_free;
  }

  m_cbd_star = mesh_file_scan_boundary(m_cbd_star_file, m);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan m_cbd_star\n", stderr);
    fclose(m_cbd_star_file);
    goto m_cbd_free;
  }
  fclose(m_cbd_star_file);

  matrix_sparse_laplacian_file_print(stdout, d, m_cbd, m_cbd_star, "--raw");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot print m_laplacian\n");
    goto m_cbd_star_free;
  }

m_cbd_star_free:
  matrix_sparse_array_free(m_cbd_star, d);
m_cbd_free:
  matrix_sparse_array_free(m_cbd, d);
m_bd_free:
  matrix_sparse_array_free(m_bd, d);
m_free:
  mesh_free(m);
end:
  return errno;
}
