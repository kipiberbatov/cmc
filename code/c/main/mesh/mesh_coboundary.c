#include <errno.h>
#include <stdlib.h>

#include "cmc_error_message.h"
#include "mesh.h"

static void mesh_coboundary_file_print(
  FILE * out, int d, matrix_sparse ** m_bd, char * format)
{
  int p;
  matrix_sparse * m_bd_p_plus_1, * m_cbd_p;

  for (p = 0; p < d; ++p)
  {
    m_bd_p_plus_1 = m_bd[p];
    m_cbd_p = matrix_sparse_transpose(m_bd_p_plus_1);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot transpose matrix [%d]\n", p);
      matrix_sparse_free(m_cbd_p);
      return;
    }
    matrix_sparse_file_print(out, m_cbd_p, format);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr, "cannot print transposed matrix [%d]\n", p);
      matrix_sparse_free(m_cbd_p);
      return;
    }
    if (p < d - 1)
      fputc('\n', out);
    matrix_sparse_free(m_cbd_p);
  }
}

int main(int argc, char ** argv)
{
  char * format;
  int d;
  matrix_sparse ** m_bd;
  mesh * m;

#define ARGC 2
  if (argc != ARGC)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_number_of_command_line_arguments_mismatch(ARGC, argc);
    return EINVAL;
  }

  format = argv[1];

  m = mesh_file_scan(stdin, "--raw");
  if (m == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan mesh m in format --raw\n", stderr);
    goto end;
  }
  d = m->dim;

  m_bd = mesh_file_scan_boundary(stdin, m);
  if (m_bd == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan boundary operators m_bd\n", stderr);
    goto m_free;
  }

  mesh_coboundary_file_print(stdout, d, m_bd, format);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot print calculate and print %d coboundary operators in format %s\n",
      d, format);
    goto m_bd_free;
  }

m_bd_free:
  matrix_sparse_array_free(m_bd, d);
m_free:
  mesh_free(m);
end:
  return errno;
}
