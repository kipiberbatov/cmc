#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "cmc_memory.h"
#include "int.h"
#include "mesh.h"
#include "mesh_and_boundary.h"
#include "mesh_file_scan_tess_private.h"
#include "mesh_private.h"
#include "string_private.h"

typedef struct non_flattened_jagged2
{
  int a0;
  int * a1;
  int ** a2;
} non_flattened_jagged2;

static void non_flattened_jagged2_free(non_flattened_jagged2 * x)
{
  int_array2_free(x->a2, x->a0);
  free(x->a1);
  free(x);
}

static int find_total_max(
  int cn_p, const int * cfn_p_q, const int * cf_p_q, const int * cfn_q_r)
{
  int cfn_p_q_i, i, j, j_local, position, total, total_max;
  const int * cf_p_q_i;

  total_max = 0;
  position = 0;
  for (i = 0; i < cn_p; ++i)
  {
    cfn_p_q_i = cfn_p_q[i];
    cf_p_q_i = cf_p_q + position;
    position += cfn_p_q_i;
    total = 0;
    for (j_local = 0; j_local < cfn_p_q_i; ++j_local)
    {
      j = cf_p_q_i[j_local];
      total += cfn_q_r[j];
    }
    if (total_max < total)
      total_max = total;
  }
  return total_max / 2;
}

static void find_union(
  int * cf_p_r_i, int * cfn_p_r_i_address,
  int i, int cfn_p_q_i, const int * cf_p_q_i,
  const int * cfn_q_r, const int * cf_q_r)
{
  int cfn_p_r_i, j, j_local, k, k_local, q_r_index, value;

  cfn_p_r_i = 0;
  for (j_local = 0; j_local < cfn_p_q_i; ++j_local)
  {
    j = cf_p_q_i[j_local];
    q_r_index = int_array_total_sum(j, cfn_q_r);
    for (k_local = 0; k_local < cfn_q_r[j]; ++k_local)
    {
      k = q_r_index + k_local;
      value = cf_q_r[k];
      if (!int_array_member(cfn_p_r_i, cf_p_r_i, value))
      {
        cf_p_r_i[cfn_p_r_i] = value;
        ++cfn_p_r_i;
      }
    }
  }
  *cfn_p_r_i_address = cfn_p_r_i;
}

static non_flattened_jagged2 * poset_transitive(
  int cn_p,
  const int * cfn_p_q,
  const int * cf_p_q,
  const int * cfn_q_r,
  const int * cf_q_r)
{
  int cfn_p_r_i, cfn_p_q_i, i, position, total_max;
  const int * cf_p_q_i;
  int * a1, * a2_i, * cf_p_r_i;
  int ** a2;
  non_flattened_jagged2 * result;

  result = (non_flattened_jagged2 *) malloc(sizeof(non_flattened_jagged2));
  if (result == NULL)
    goto end;
  a1 = (int *) malloc(sizeof(int) * cn_p);
  if (a1 == NULL)
    goto result_free;
  a2 = (int **) malloc(sizeof(int *) * cn_p);
  if (a2 == NULL)
    goto a1_free;

  total_max = find_total_max(cn_p, cfn_p_q, cf_p_q, cfn_q_r);

  i = 0;
  cf_p_r_i = (int *) malloc(sizeof(int) * total_max);
  if (cf_p_r_i == NULL)
    goto a2_free;

  position = 0;
  for (i = 0; i < cn_p; ++i)
  {
    cf_p_q_i = cf_p_q + position;
    cfn_p_q_i = cfn_p_q[i];
    find_union(cf_p_r_i, &cfn_p_r_i, i, cfn_p_q_i, cf_p_q_i, cfn_q_r, cf_q_r);
    a2_i = (int *) malloc(sizeof(int) * cfn_p_r_i);
    if (a2_i == NULL)
      goto cf_p_r_i_free;
    memcpy(a2_i, cf_p_r_i, sizeof(int) * cfn_p_r_i);
    a1[i] = cfn_p_r_i;
    a2[i] = a2_i;
    position += cfn_p_q_i;
  }
  free(cf_p_r_i);

  result->a0 = cn_p;
  result->a1 = a1;
  result->a2 = a2;
  return result;

  /* cleaning if an error occurs */
cf_p_r_i_free:
  free(cf_p_r_i);
a2_free:
  int_array2_free(a2, i);
a1_free:
  free(a1);
result_free:
  free(result);
end:
  return NULL;
}

void mesh_file_scan_tess_with_options(
  mesh_and_boundary ** m_and_bd, FILE * in, int * status, int has_boundary)
{
  int c_size, d, offset_cfn, offset_cf,
      cf_a2_size, cf_a3_size, cf_a4_size,
      cfn_2_1_total, cfn_3_0_total, cfn_3_1_total, cfn_3_2_total, i, pos_i;
  long position;
  int * c, * cn,
      * cf_1_0, * cf_2_0, * cf_2_1, * cf_3_0, * cf_3_1, * cf_3_2, 
      * cfn_2_1, * cfn_3_0, * cfn_3_1, * cfn_3_2;
  double * boundary_values_1 = NULL, * boundary_values_2 = NULL,
         * boundary_values_3 = NULL, * coordinates;
  double ** boundary_values;
  non_flattened_jagged2 * tmp;
  mesh * m;
  jagged4 * cf;

  mesh_file_scan_tess_check_preamble(in, status);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("the preamble is not in the right format\n", stderr);
    goto end;
  }

  d = mesh_file_scan_tess_get_dimension(in, status);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan dimension\n", stderr);
    goto end;
  }

  mesh_file_scan_tess_check_text_for_cell(in, status);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("the cell text is not in the right format\n", stderr);
    goto end;
  }

  cmc_memory_allocate((void **) m_and_bd, status, sizeof(mesh_and_boundary));
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("m_and_bd");
    goto end;
  }

  cmc_memory_allocate((void **) &m, status, sizeof(mesh));
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("m");
    goto m_and_bd_free;
  }

  m->dim = d;

  cmc_memory_allocate((void **) &cn, status, sizeof(int) * (d + 1));
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("cn");
    goto m_free;
  }

  cn[d] = mesh_file_scan_tess_get_number_of_maximal_cells(in, status);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan the number of maximal cells\n", stderr);
    goto cn_free;
  }

  string_locate_in_file_line(in, status, " **vertex");
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot find the vertex field\n", stderr);
    goto cn_free;
  }

  cn[0] = mesh_file_scan_tess_get_cells_number_0(in, status);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannnot scan the number of nodes\n", stderr);
    goto cn_free;
  }

  cmc_memory_allocate(
    (void **) &coordinates, status, sizeof(double) * cn[0] * d);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("coordinates");
    goto cn_free;
  }

  mesh_file_scan_tess_get_coordinates(coordinates, in, status, d, cn[0]);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan coordinates\n", stderr);
    goto coordinates_free;
  }

  mesh_file_scan_tess_check_text_for_edge(in, status);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot find the edge field\n", stderr);
    goto coordinates_free;
  }

  cn[1] = mesh_file_scan_tess_get_cells_number_1(in, status);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan the number of edges\n", stderr);
    goto coordinates_free;
  }

  cmc_memory_allocate((void **) &cf_1_0, status, sizeof(int) * 2 * cn[1]);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("cf_1_0");
    goto coordinates_free;
  }

  mesh_file_scan_tess_get_cells_to_faces_1_0(cf_1_0, in, status, cn[1]);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan the edges' nodes\n", stderr);
    goto cf_1_0_free;
  }

  if (has_boundary)
  {
    cmc_memory_allocate((void **) &boundary_values, status, sizeof(double) * d);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      cmc_error_message_memory_allocate("boundary_values");
      goto cf_1_0_free;
    }
    cmc_memory_allocate(
      (void **) &boundary_values_1, status, sizeof(double) * 2 * cn[1]);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      cmc_error_message_memory_allocate("boundary_values_1");
      goto boundary_values_free;
    }
    mesh_boundary_values_1_set(boundary_values_1, cn[1]);
    boundary_values[0] = boundary_values_1;
  }

  mesh_file_scan_tess_check_text_for_face(in, status);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot find the face field\n", stderr);
    goto boundary_values_1_free;
  }

  cn[2] = mesh_file_scan_tess_get_cells_number_2(in, status);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan the number of faces\n", stderr);
    goto boundary_values_1_free;
  }

  c_size = int_array_total_sum(d + 1, cn);
  cmc_memory_allocate((void **) &c, status, sizeof(int) * c_size);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("m->c");
    goto boundary_values_1_free;
  }

  cmc_memory_allocate((void **) &cfn_2_1, status, sizeof(int) * cn[2]);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("cfn_2_1");
    goto c_free;
  }

  position = ftell(in);
  mesh_file_scan_tess_get_cells_to_faces_number_2_1(cfn_2_1, in, status, cn[2]);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan the number of sides per face\n", stderr);
    goto cfn_2_1_free;
  }
  fseek(in, position, SEEK_SET);

  cfn_2_1_total = int_array_total_sum(cn[2], cfn_2_1);

  cmc_memory_allocate((void **) &cf_2_0, status, sizeof(int) * cfn_2_1_total);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("cf_2_0");
    goto cfn_2_1_free;
  }

  position = ftell(in);
  mesh_file_scan_tess_get_cells_to_faces_2_0(
    cf_2_0, in, status, cn[2], cfn_2_1);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan faces' nodes\n", stderr);
    goto cf_2_0_free;
  }
  fseek(in, position, SEEK_SET);

  cmc_memory_allocate((void **) &cf_2_1, status, sizeof(int) * cfn_2_1_total);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("cf_2_1");
    goto cf_2_0_free;
  }

  position = ftell(in);
  mesh_file_scan_tess_get_cells_to_faces_2_1(
    cf_2_1, in, status, cn[2], cfn_2_1);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan faces' edges\n", stderr);
    goto cf_2_1_free;
  }
  fseek(in, position, SEEK_SET);

  if (has_boundary)
  {
    cmc_memory_allocate(
      (void **) &boundary_values_2, status, sizeof(double) * cfn_2_1_total);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      cmc_error_message_memory_allocate("boundary_values_2");
      goto cf_2_1_free;
    }
    mesh_file_scan_tess_get_boundary_values_2(boundary_values_2, in, status,
      cn[2], cfn_2_1_total);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fputs("cannot scan boundary_values_2\n", stderr);
      goto boundary_values_2_free;
    }
    boundary_values[1] = boundary_values_2;
  }

  cmc_memory_allocate((void **) &cf, status, sizeof(jagged4));
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("cf");
    goto boundary_values_2_free;
  }

  cf->a0 = d;
  cmc_memory_allocate((void **) &(cf->a1), status, sizeof(int) * cf->a0);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("cf->a1");
    goto cf_free;
  }
  mesh_cf_a1(cf->a1, d);

  cf_a2_size = int_array_total_sum(d, cf->a1);
  cmc_memory_allocate((void **) &(cf->a2), status, sizeof(int) * cf_a2_size);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("cf->a2");
    goto cf_a1_free;
  }
  mesh_cf_a2(cf->a2, d, cn);

  cf_a3_size = int_array_total_sum(cf_a2_size, cf->a2);
  cmc_memory_allocate((void **) &(cf->a3), status, sizeof(int) * cf_a3_size);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("cf->a3");
    goto cf_a2_free;
  }

  /* put cfn_1_0 into cf->a3 */
  int_array_assign_constant(cf->a3, cn[1], 2);
  offset_cfn = cn[1];

  /* put cfn_2_0 into cf->a3 */
  memcpy(cf->a3 + offset_cfn, cfn_2_1, sizeof(int) * cn[2]);
  offset_cfn += cn[2];

  /* put cfn_2_1 into cf->a3 */
  memcpy(cf->a3 + offset_cfn, cfn_2_1, sizeof(int) * cn[2]);
  offset_cfn += cn[2];

  cfn_3_0_total=0;
  cfn_3_1_total=0;
  cfn_3_2_total=0;
  if (d == 3)
  {
    mesh_file_scan_tess_check_text_for_polyhedron(in, status);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fputs("cannot find the polyhedron field\n", stderr);
      goto cf_a3_free;
    }

    if (int_file_scan(in) != cn[3])
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fputs("mismatch in number of 3-cells\n", stderr);
      goto cf_a3_free;
    }

    cmc_memory_allocate((void **) &cfn_3_2, status, sizeof(int) * cn[3]);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      cmc_error_message_memory_allocate("cfn_3_2");
      goto cf_a3_free;
    }

    position = ftell(in);
    mesh_file_scan_tess_get_cells_to_faces_number_3_2(
      cfn_3_2, in, status, cn[3]);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fputs("cannot scan cfn_3_2\n", stderr);
      goto cfn_3_2_free;
    }
    fseek(in, position, SEEK_SET);

    cfn_3_2_total = int_array_total_sum(cn[3], cfn_3_2);

    cmc_memory_allocate((void **) &cf_3_2, status, sizeof(int) * cfn_3_2_total);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      cmc_error_message_memory_allocate("cf_3_2");
      goto cfn_3_2_free;
    }

    position = ftell(in);
    mesh_file_scan_tess_get_cells_to_faces_3_2(
      cf_3_2, in, status, cn[3], cfn_3_2);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fputs("cannot scan faces' nodes\n", stderr);
      goto cf_3_2_free;
    }
    fseek(in, position, SEEK_SET);

    cmc_memory_allocate((void **) &cfn_3_0, status, sizeof(int) * cn[3]);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      cmc_error_message_memory_allocate("cfn_3_0");
      goto cf_3_2_free;
    }

    tmp = poset_transitive(cn[3], cfn_3_2, cf_3_2, cfn_2_1, cf_2_0);
    if (tmp == NULL)
      goto cf_3_2_free;
    memcpy(cfn_3_0, tmp->a1, sizeof(int) * cn[3]);
    cfn_3_0_total = int_array_total_sum(cn[3], cfn_3_0);
    cmc_memory_allocate(
      (void **) &cf_3_0, status, sizeof(int) * cfn_3_0_total);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      cmc_error_message_memory_allocate("cfn_3_0");
      non_flattened_jagged2_free(tmp);
      goto cfn_3_0_free;
    }
    pos_i = 0;
    for (i = 0; i < cn[3]; ++i)
    {
      memcpy(cf_3_0 + pos_i, tmp->a2[i], sizeof(int) * tmp->a1[i]);
      pos_i += tmp->a1[i];
    }
    non_flattened_jagged2_free(tmp);

    cmc_memory_allocate((void **) &cfn_3_1, status, sizeof(int) * cn[3]);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      cmc_error_message_memory_allocate("cfn_3_1");
      goto cf_3_0_free;
    }

    tmp = poset_transitive(cn[3], cfn_3_2, cf_3_2, cfn_2_1, cf_2_1);
    if (tmp == NULL)
      goto cf_3_0_free;
    memcpy(cfn_3_1, tmp->a1, sizeof(int) * cn[3]);
    cfn_3_1_total = int_array_total_sum(cn[3], cfn_3_1);
    cmc_memory_allocate(
      (void **) &cf_3_1, status, sizeof(int) * cfn_3_1_total);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      cmc_error_message_memory_allocate("cfn_3_0");
      non_flattened_jagged2_free(tmp);
      goto cfn_3_1_free;
    }
    pos_i = 0;
    for (i = 0; i < cn[3]; ++i)
    {
      memcpy(cf_3_1 + pos_i, tmp->a2[i], sizeof(int) * tmp->a1[i]);
      pos_i += tmp->a1[i];
    }
    non_flattened_jagged2_free(tmp);

    /* put cfn_3_0 into cf->a3 */
    memcpy(cf->a3 + offset_cfn, cfn_3_0, sizeof(int) * cn[3]);
    offset_cfn += cn[3];

    /* put cfn_3_1 into cf->a3 */
    memcpy(cf->a3 + offset_cfn, cfn_3_1, sizeof(int) * cn[3]);
    offset_cfn += cn[3];

    /* put cfn_3_2 into cf->a3 */
    memcpy(cf->a3 + offset_cfn, cfn_3_2, sizeof(int) * cn[3]);
    offset_cfn += cn[3];

    if (has_boundary)
    {
      cmc_memory_allocate(
        (void **) &boundary_values_3, status, sizeof(double) * cfn_3_2_total);
      if (*status)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        cmc_error_message_memory_allocate("boundary_values_2");
        goto cf_3_1_free;
      }
      mesh_file_scan_tess_get_boundary_values_3(boundary_values_3, in, cn[3]);
      boundary_values[2] = boundary_values_3;
    }
  }

  cf_a4_size = int_array_total_sum(cf_a3_size, cf->a3);
  cmc_memory_allocate((void **) &(cf->a4), status, sizeof(int) * cf_a4_size);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("cf->a4");
    goto boundary_values_3_free;
  }

  /* put cf_1_0 into cf->a4 */
  memcpy(cf->a4, cf_1_0, sizeof(int) * 2 * cn[1]);
  offset_cf = 2 * cn[1];

  /* put cf_2_0 into cf->a4 */
  memcpy(cf->a4 + offset_cf, cf_2_0, sizeof(int) * cfn_2_1_total);
  offset_cf += cfn_2_1_total;

  /* put cf_2_1 into cf->a4 */
  memcpy(cf->a4 + offset_cf, cf_2_1, sizeof(int) * cfn_2_1_total);
  offset_cf += cfn_2_1_total;

  if (d == 3)
  {
    /* put cf_3_0 into cf->a4 */
    memcpy(cf->a4 + offset_cf, cf_3_0, sizeof(int) * cfn_3_0_total);
    offset_cf += cfn_3_0_total;

    /* put cf_3_1 into cf->a4 */
    memcpy(cf->a4 + offset_cf, cf_3_1, sizeof(int) * cfn_3_1_total);
    offset_cf += cfn_3_1_total;

    /* put cf_3_2 into cf->a4 */
    memcpy(cf->a4 + offset_cf, cf_3_2, sizeof(int) * cfn_3_2_total);

    cmc_memory_free(cf_3_1);
    cmc_memory_free(cfn_3_1);
    cmc_memory_free(cf_3_0);
    cmc_memory_free(cfn_3_0);
    cmc_memory_free(cf_3_2);
    cmc_memory_free(cfn_3_2);
  }

  cmc_memory_free(cf_2_1);
  cmc_memory_free(cf_2_0);
  cmc_memory_free(cfn_2_1);
  cmc_memory_free(cf_1_0);

  m->dim = d;
  m->dim_embedded = d;
  m->coord = coordinates;
  m->cn = cn;
  m->c = c;
  m->cf = cf;
  m->fc = NULL;
  (*m_and_bd)->_mesh = m;
  (*m_and_bd)->boundary = boundary_values;
  goto end;

  /* cleaning if an error occurs */
  cmc_memory_free(cf->a4);
boundary_values_3_free:
  cmc_memory_free(boundary_values_3);
cf_3_1_free:
  cmc_memory_free(cf_3_1);
cfn_3_1_free:
  cmc_memory_free(cfn_3_1);
cf_3_0_free:
  cmc_memory_free(cf_3_0);
cfn_3_0_free:
  cmc_memory_free(cfn_3_0);
cf_3_2_free:
  cmc_memory_free(cf_3_2);
cfn_3_2_free:
  cmc_memory_free(cfn_3_2);
cf_a3_free:
  cmc_memory_free(cf->a3);
cf_a2_free:
  cmc_memory_free(cf->a2);
cf_a1_free:
  cmc_memory_free(cf->a1);
cf_free:
  cmc_memory_free(cf);
boundary_values_2_free:
  cmc_memory_free(boundary_values_2);
cf_2_1_free:
  cmc_memory_free(cf_2_1);
cf_2_0_free:
  cmc_memory_free(cf_2_0);
cfn_2_1_free:
  cmc_memory_free(cfn_2_1);
c_free:
  cmc_memory_free(c);
boundary_values_1_free:
  cmc_memory_free(boundary_values_1);
boundary_values_free:
  cmc_memory_free(boundary_values);
cf_1_0_free:
  cmc_memory_free(cf_1_0);
coordinates_free:
  cmc_memory_free(coordinates);
cn_free:
  cmc_memory_free(cn);
m_free:
  cmc_memory_free(m);
m_and_bd_free:
  cmc_memory_free(m_and_bd);
end:
  return;
}
