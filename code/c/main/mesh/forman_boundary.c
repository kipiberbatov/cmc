#include <errno.h>
#include <string.h>

#include "cmc_error_message.h"
#include "double_array.h"
#include "forman.h"

static void mesh_boundary_file_print(
  FILE * out, int m_dim, matrix_sparse ** m_bd, const char * output_format)
{
  int m_bd_p_nonzero_max, p;
  const matrix_sparse * m_bd_p;

  for (p = 1; p <= m_dim; ++p)
  {
    m_bd_p = m_bd[p - 1];
    m_bd_p_nonzero_max = m_bd_p->cols_total[m_bd_p->cols];
    double_array_file_print(out,
      m_bd_p_nonzero_max, m_bd_p->values, output_format);
  }
}

static void forman_boundary_file_print(
  FILE * out, const mesh * m, matrix_sparse ** m_bd,
  const char * new_coordinates_format, const char * output_format)
{
  mesh * m_forman;
  matrix_sparse ** m_forman_boundary;

  m_forman = forman(m, new_coordinates_format);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m_forman\n", stderr);
    goto end;
  }
  mesh_file_print(out, m_forman, "--raw");

  m_forman_boundary = forman_boundary(m, m_forman, m_bd);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m_forman->bd\n", stderr);
    goto m_forman_free;
  }

  mesh_boundary_file_print(out, m->dim, m_forman_boundary, output_format);

  matrix_sparse_array_free(m_forman_boundary, m->dim);
m_forman_free:
  mesh_free(m_forman);
end:
  return;
}

int main(int argc, char ** argv)
{
  char * m_format, * m_name, * new_coordinates_format, * output_format;
  FILE * m_file;
  matrix_sparse ** m_bd;
  mesh * m;

  if (argc != 5)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "number of command line arguments should be 5; instead it is %d\n", argc);
    errno = EINVAL;
    goto end;
  }

  m_format = argv[1];
  m_name = argv[2];
  new_coordinates_format = argv[3];
  output_format = argv[4];

  m_file = fopen(m_name, "r");
  if (m_file == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot open mesh file %s: %s\n", m_name, strerror(errno));
    goto end;
  }

  m = mesh_file_scan(m_file, m_format);
  if (m == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh m in from file %s in fromat %s\n",
      m_name, m_format);
    fclose(m_file);
    goto end;
  }

  m->fc = mesh_fc(m);
  if (m->fc == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m->fc\n", stderr);
    goto m_free;
  }

  m_bd = mesh_file_scan_boundary(m_file, m);
  if (m_bd == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan m_bd\n", stderr);
    fclose(m_file);
    goto m_free;
  }

  fclose(m_file);

  forman_boundary_file_print(stdout,
    m, m_bd, new_coordinates_format, output_format);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate and print m_forman->bd\n", stderr);
    goto m_bd_free;
  }

m_bd_free:
  matrix_sparse_array_free(m_bd, m->dim);
m_free:
  mesh_free(m);
end:
  return errno;
}
