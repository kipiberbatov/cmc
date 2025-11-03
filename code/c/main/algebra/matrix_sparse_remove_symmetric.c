#include <errno.h>
#include <string.h>

#include "cmc_error_message.h"
#include "jagged.h"
#include "matrix_sparse.h"

int main(int argc, char ** argv)
{
  char * a_format, * a_name, * rows_format, * rows_name, * out_format;
  FILE * rows_file;
  matrix_sparse * a, * b;
  jagged1 * rows;

#define ARGC 6
  if (argc != ARGC)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_number_of_command_line_arguments_mismatch(ARGC, argc);
    errno = EIO;
    goto end;
  }

  /* a = m_laplacian_0 */
  a_name = argv[1];
  a_format = argv[2];
  a = matrix_sparse_file_scan_by_name(a_name, a_format);
  if (a == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan matrix a from file %s in format %s\n",
      a_name, a_format);
    goto end;
  }

  /* rows = m_bd_nodes */
  rows_name = argv[3];
  rows_format = argv[4];

  rows_file = fopen(rows_name, "r");
  if (rows_file == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan open file %s for reading: %s\n",
      rows_name, strerror(errno));
    goto end;
  }
  rows = jagged1_file_scan(rows_file, rows_format);
  if (rows == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan rows from file %s in format %s\n",
      rows_name, rows_format);
    fclose(rows_file);
    goto a_free;
  }
  fclose(rows_file);

  b = matrix_sparse_remove_symmetric(a, rows);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate restricted matrix b\n", stderr);
    goto rows_free;
  }

  out_format = argv[5];
  matrix_sparse_file_print(stdout, b, out_format);

  matrix_sparse_free(b);
rows_free:
  jagged1_free(rows);
a_free:
  matrix_sparse_free(a);
end:
  return errno;
}
