#include <errno.h>
#include <string.h>

#include "cmc_error_message.h"
#include "double.h"
#include "mesh_qc.h"

static void mesh_qc_hodge_codifferential_p_file_print(
  FILE * out, int d, int p, const matrix_sparse * m_cbd_d_minus_p,
  matrix_sparse ** m_hodge)
{
  matrix_sparse * m_hodge_codifferential_p;

  m_hodge_codifferential_p = mesh_qc_hodge_codifferential_p(
    d, p, m_cbd_d_minus_p, m_hodge);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot calculate m_hodge_codifferential[%d]\n", p);
    return;
  }
  matrix_sparse_file_print(out, m_hodge_codifferential_p, "--raw");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot print m_hodge_codifferential[%d]\n", p);
    matrix_sparse_free(m_hodge_codifferential_p);
    return;
  }
  matrix_sparse_free(m_hodge_codifferential_p);
}


static void mesh_qc_hodge_codifferential_file_print_raw(
  FILE * out, int d, matrix_sparse ** m_cbd, matrix_sparse ** m_hodge)
{
  int p;

  for (p = 1; p <= d; ++p)
  {
    mesh_qc_hodge_codifferential_p_file_print(
      out, d, p, m_cbd[d - p], m_hodge);
    if (errno)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stderr,
        "cannot calculate and print m_hodge_codifferential[%d]\n",
        p);
      return;
    }
    if (p < d)
      fputc('\n', out);
  }
}

int main(int argc, char ** argv)
{
  char * m_hodge_name, * m_name;
  int d;
  FILE * m_file;
  matrix_sparse ** m_bd, ** m_cbd, ** m_hodge;
  mesh_qc * m;

#define ARGC 3
  if (argc != ARGC)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_number_of_command_line_arguments_mismatch(ARGC, argc);
    return EINVAL;
  }

  m_name = argv[1];
  m_hodge_name = argv[2];

  m_file = fopen(argv[1], "r");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot open mesh file %s: %s\n", m_name, strerror(errno));
    goto end;
  }

  m = mesh_file_scan(m_file, "--raw");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan m from file %s in format --raw\n", m_name);
    fclose(m_file);
    goto end;
  }

  d = m->dim;

  m->fc = mesh_fc(m);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m->fc\n", stderr);
    mesh_free(m);
    fclose(m_file);
    goto end;
  }

  m_bd = mesh_file_scan_boundary(m_file, m);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan m_bd from file %s\n", m_name);
    mesh_free(m);
    fclose(m_file);
    goto end;
  }

  mesh_free(m);
  fclose(m_file);

  m_cbd = mesh_coboundary(d, m_bd);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate m_cbd\n", stderr);
    matrix_sparse_array_free(m_bd, d);
    goto end;
  }
  matrix_sparse_array_free(m_bd, d);

  m_hodge = matrix_sparse_array_file_scan_by_name(m_hodge_name, d + 1, "--raw");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr, "cannot scan m_hodge from file %s\n", m_hodge_name);
    goto m_cbd_free;
  }

  mesh_qc_hodge_codifferential_file_print_raw(stdout, d, m_cbd, m_hodge);
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot calculate and print Hodge codifferentials\n", stderr);
    goto m_hodge_free;
  }

m_hodge_free:
  matrix_sparse_array_free(m_hodge, d + 1);
m_cbd_free:
  matrix_sparse_array_free(m_cbd, d);
end:
  return errno;
}
