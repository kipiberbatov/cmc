#include <errno.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "cmc_error_message.h"
#include "cmc_memory.h"

#include "double.h"
#include "double_array.h"
#include "int.h"
#include "mesh.h"
#include "mesh_and_boundary.h"

/* mesh private function */
void string_locate_in_file_line(FILE *file,
  int *status,
  const char *s);
/* custom function */
void mesh_generate_diffusivity_metal_private(int *status,
  const mesh *m,
  double **rodrigues,
  double D_0,
  int Q_1,
  int Q_2,
  double T,
  int to_print_D_g);
void mesh_generate_diffusivity_metal_hydrogen_diffusivity_edges_in_K(
  int *status,
  const mesh *m,
  double **d_crystal,
  double **d_g,
  int to_print_diffusivity_value);
void mesh_generate_diffusivity_metal_scan_rodrigues(
  double **rodrigues,
  int *status,
  FILE *in,
  int cn_d);
void mesh_generate_diffusivity_metal_get_coord_0(double *vertex_data,
  const mesh *m,
  int v_id);
double mesh_generate_diffusivity_metal_get_coord_0_i(const mesh *m,
  int v_id,
  int i);
int mesh_generate_diffusivity_metal_get_cfn_3_0(const mesh *m,
  int p_id);
int mesh_generate_diffusivity_metal_get_cfn_3_2(const mesh *m,
  int p_id);
int mesh_generate_diffusivity_metal_get_cfn_2_1(const mesh *m,
  int f_id);
void mesh_generate_diffusivity_metal_get_cf_3_0(int *cf_3_0,
  const mesh *m,
  int p_id);
void mesh_generate_diffusivity_metal_get_cf_3_2(int *cf_3_2,
  const mesh *m,
  int p_id);
void mesh_generate_diffusivity_metal_get_cf_2_1(int *cf_2_1,
  const mesh *m,
  int f_id);
void mesh_generate_diffusivity_metal_get_center_coord_3(
  double *center_coord,
  int *status,
  const mesh *m,
  int p_id);
void mesh_generate_diffusivity_metal_get_max_height(double *H,
  int *status,
  const mesh *m);
void mesh_generate_diffusivity_metal_get_height(double *hi_a,
  int *status,
  const mesh *m);
void mesh_generate_diffusivity_metal_calculate_crystal_tensor(
  double **tensor,
  int *status,
  const mesh *m,
  double D_0,
  int Q_1,
  int Q_2,
  double T);
void mesh_generate_diffusivity_metal_calculate_rodrigues_tensor(
  double **tensor,
  int *status,
  const mesh *m,
  double **rodrigues);
void mesh_generate_diffusivity_metal_calculate_crystal_diffusivity(
  double **diffusivity,
  int cn_d,
  double **crystal_tensor,
  double **rodrigues_tensor);

int main(int argc, char **argv)
{
  char *m_name, *m_output_type;
  int i, cn_d, Q_1, Q_2, status, to_print_D_g;
  long position;
  double D_0, T;
  double **rodrigues = NULL;
  FILE *m_and_bd_file;
  struct mesh_and_boundary *m_and_bd = NULL;
  struct mesh *m = NULL;

  if (argc != 7)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "the number of command-line arguments must be 7; instead it is "
      "%d\n",
      argc);
    errno = EINVAL;
    goto end;
  }

  m_name = argv[1];
  m_output_type = argv[2];
  D_0 = atof(argv[3]);
  Q_1 = atoi(argv[4]);
  Q_2 = atoi(argv[5]);
  T = atof(argv[6]);

  if (strcmp(m_output_type, "D_g") == 0)
  {
    to_print_D_g = 1;
  }
  else if (strcmp(m_output_type, "diffusivity_value") == 0)
  {
    to_print_D_g = 0;
  }
  else
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "no defined output type : %s ,error : %s, please input D_g or "
      "diffusivity_value.\n",
      m_output_type,
      strerror(errno));
    goto end;
  }

  m_and_bd_file = fopen(m_name, "rb");
  if (m_and_bd_file == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot open tess file %s: %s\n",
      m_name,
      strerror(errno));
    goto end;
  }

  position = ftell(m_and_bd_file);
  m_and_bd = mesh_and_boundary_file_scan(m_and_bd_file, "tess");
  if (errno)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh and boundary in format %s%s%s\n",
      color_variable,
      "tess",
      color_none);
    fclose(m_and_bd_file);
    return errno;
  }

  m = m_and_bd->_mesh;
  if (m == NULL)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot scan mesh m in format 'tess'\n", stderr);
    fclose(m_and_bd_file);
    goto end;
  }

  fseek(m_and_bd_file, position, SEEK_SET);

  cn_d = m->cn[m->dim];
  status = 0;

  cmc_memory_allocate(
    (void **)&rodrigues, &status, sizeof(double *) * cn_d);
  if (status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("rodrigues");
    fclose(m_and_bd_file);
    goto m_and_bd_free;
  }

  for (i = 0; i < cn_d; i++)
  {
    cmc_memory_allocate(
      (void **)&rodrigues[i], &status, sizeof(double) * 3);
    if (status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stdout, "malloc error in rodrigues[%d]\n", i);
      fclose(m_and_bd_file);
      goto rodrigues_free;
    }
  }

  /* scan rodrigues from tess */
  mesh_generate_diffusivity_metal_scan_rodrigues(
    rodrigues, &status, m_and_bd_file, cn_d);
  if (status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
      "cannot scan mesh and boundary in format %s%s%s\n",
      color_variable,
      "tess",
      color_none);
    fclose(m_and_bd_file);
    goto rodrigues_d_free;
  }

  fclose(m_and_bd_file);

  /* main calculation */
  mesh_generate_diffusivity_metal_private(
    &status, m, rodrigues, D_0, Q_1, Q_2, T, to_print_D_g);
  if (status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stdout,
      "error in function : %s\n",
      "mesh_generate_diffusivity_metal_private");
    return status;
  }

rodrigues_d_free:
  for (i = 0; i < cn_d; i++)
  {
    cmc_memory_free(rodrigues[i]);
  }

rodrigues_free:
  cmc_memory_free(rodrigues);

m_and_bd_free:
  mesh_and_boundary_free(m_and_bd);

end:
  return errno;
}

void mesh_generate_diffusivity_metal_private(int *status,
  const mesh *m,
  double **rodrigues,
  double D_0,
  int Q_1,
  int Q_2,
  double T,
  int to_print_D_g)
{
  int i, j, cn_d;
  double **crystal_tensor = NULL;
  double **rodrigues_tensor = NULL;
  double **crystal_diffusivity = NULL;

  cn_d = m->cn[m->dim];

  /* malloc crystal_tensor */
  cmc_memory_allocate(
    (void **)&crystal_tensor, status, sizeof(double *) * cn_d);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("crystal_tensor");
    return;
  }

  /* crystal_tensor, size is cn_d * 3. */
  for (i = 0; i < cn_d; i++)
  {
    cmc_memory_allocate(
      (void **)&crystal_tensor[i], status, sizeof(double) * 3);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      cmc_error_message_memory_allocate("crystal_tensor[i]");
      return;
    }

    memset(crystal_tensor[i], 0, sizeof(double) * 3);
  }

  /* calculate D(crystal) */
  mesh_generate_diffusivity_metal_calculate_crystal_tensor(
    crystal_tensor, status, m, D_0, Q_1, Q_2, T);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stdout,
      "error in function : %s\n",
      "mesh_generate_diffusivity_metal_calculate_crystal_tensor");
    return;
  }

  /* malloc rodrigues_tensor */
  cmc_memory_allocate(
    (void **)&rodrigues_tensor, status, sizeof(double *) * cn_d);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("rodrigues_tensor");
    return;
  }

  /* rodrigues_tensor, size is cn_d * 3 * 3. */
  for (i = 0; i < cn_d; i++)
  {
    cmc_memory_allocate(
      (void **)&rodrigues_tensor[i], status, sizeof(double) * 9);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      cmc_error_message_memory_allocate("rodrigues_tensor[i]");
      return;
    }

    memset(rodrigues_tensor[i], 0, sizeof(double) * 9);
  }

  /* calculate R_g */
  mesh_generate_diffusivity_metal_calculate_rodrigues_tensor(
    rodrigues_tensor, status, m, rodrigues);

  /* malloc crystal_diffusivity */
  cmc_memory_allocate(
    (void **)&crystal_diffusivity, status, sizeof(double *) * cn_d);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("crystal_diffusivity");
    return;
  }

  /* crystal_diffusivity, size is cn_d * 3 * 3. */
  for (i = 0; i < cn_d; i++)
  {
    cmc_memory_allocate(
      (void **)&crystal_diffusivity[i], status, sizeof(double) * 9);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      cmc_error_message_memory_allocate("crystal_diffusivity[i]");
      return;
    }

    memset(crystal_diffusivity[i], 0, sizeof(double) * 9);
  }

  /* calculate D_g */
  mesh_generate_diffusivity_metal_calculate_crystal_diffusivity(
    crystal_diffusivity, cn_d, crystal_tensor, rodrigues_tensor);

  if (to_print_D_g)
  {
    /* print D_crystal */
    fprintf(stdout, "D_crystal : \n");
    for (i = 0; i < cn_d; i++)
    {
      fprintf(stdout, "%g ", crystal_tensor[i][0]);
      fprintf(stdout, "%g ", 0.0);
      fprintf(stdout, "%g ", 0.0);
      fprintf(stdout, "\n%g ", 0.0);
      fprintf(stdout, "%g ", crystal_tensor[i][1]);
      fprintf(stdout, "%g ", 0.0);
      fprintf(stdout, "\n%g ", 0.0);
      fprintf(stdout, "%g ", 0.0);
      fprintf(stdout, "%g \n", crystal_tensor[i][2]);

      if (i != cn_d - 1)
      {
        fprintf(stdout, "\n");
      }
    }

    /* print R_g */
    fprintf(stdout, "\nR_g : \n");
    /* free rodrigues_tensor */
    for (i = 0; i < cn_d; i++)
    {
      for (j = 0; j < 9; j++)
      {
        fprintf(stdout, "%g ", rodrigues_tensor[i][j]);

        if (j % 3 == 2)
        {
          fprintf(stdout, "\n");
        }
      }

      if (i != cn_d - 1)
      {
        fprintf(stdout, "\n");
      }
    }

    /* print D_g */
    fprintf(stdout, "\nD_g : \n");
    for (i = 0; i < cn_d; i++)
    {
      for (j = 0; j < 9; j++)
      {
        fprintf(stdout, "%g ", crystal_diffusivity[i][j]);

        if (j % 3 == 2)
        {
          fprintf(stdout, "\n");
        }
      }

      if (i != cn_d - 1)
      {
        fprintf(stdout, "\n");
      }
    }
  }

  mesh_generate_diffusivity_metal_hydrogen_diffusivity_edges_in_K(
    status,
    m,
    crystal_tensor,
    crystal_diffusivity,
    to_print_D_g ? 0 : 1);

  /* free crystal_diffusivity */
  for (i = 0; i < cn_d; i++)
  {
    cmc_memory_free(crystal_diffusivity[i]);
  }
  cmc_memory_free(crystal_diffusivity);

  /* free rodrigues_tensor */
  for (i = 0; i < cn_d; i++)
  {
    cmc_memory_free(rodrigues_tensor[i]);
  }
  cmc_memory_free(rodrigues_tensor);

  /* free crystal_tensor */
  for (i = 0; i < cn_d; i++)
  {
    cmc_memory_free(crystal_tensor[i]);
  }
  cmc_memory_free(crystal_tensor);
}

void mesh_generate_diffusivity_metal_hydrogen_diffusivity_edges_in_K(
  int *status,
  const mesh *m,
  double **d_crystal,
  double **d_g,
  int to_print_diffusivity_value)
{
  int i, j, k, cn_d, cn_2, cn_1, poly_to_face_number,
    face_to_edge_number, value_number, cfn_3_2, cfn_2_1, count;
  int *cf_3_2 = NULL;
  int *cf_2_1 = NULL;
  double *diffusivity_grain = NULL;
  double *diffusivity_poly_to_surface = NULL;
  double *diffusivity_surface = NULL;
  double *diffusivity_surface_to_edge = NULL;
  double *diffusivity_edge = NULL;
  double *diffusivity_edge_to_node = NULL;
  double *diffusivity_value = NULL;

  cn_d = m->cn[m->dim];
  cn_2 = m->cn[2];
  cn_1 = m->cn[1];

  /* malloc diffusivity_grain */
  cmc_memory_allocate(
    (void **)&diffusivity_grain, status, sizeof(double) * cn_d);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("diffusivity_grain");
    return;
  }

  poly_to_face_number = 0;

  for (i = 0; i < cn_d; i++)
  {
    diffusivity_grain[i] =
      (d_crystal[i][0] + d_crystal[i][1] + d_crystal[i][2]) / 3.0;

    poly_to_face_number +=
      mesh_generate_diffusivity_metal_get_cfn_3_2(m, i);
  }

  /* malloc diffusivity_poly_to_surface */
  cmc_memory_allocate((void **)&diffusivity_poly_to_surface,
    status,
    sizeof(double) * poly_to_face_number);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("diffusivity_poly_to_surface");
    cmc_memory_free(diffusivity_grain);
    return;
  }

  poly_to_face_number = 0;
  cfn_3_2 = 0;

  for (i = 0; i < cn_d; i++)
  {
    cfn_3_2 = mesh_generate_diffusivity_metal_get_cfn_3_2(m, i);

    for (j = 0; j < cfn_3_2; j++)
    {
      diffusivity_poly_to_surface[poly_to_face_number + j] =
        diffusivity_grain[i];
    }

    poly_to_face_number += cfn_3_2;
  }

  /* malloc diffusivity_surface */
  cmc_memory_allocate(
    (void **)&diffusivity_surface, status, sizeof(double) * cn_2);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("diffusivity_surface");
    cmc_memory_free(diffusivity_grain);
    cmc_memory_free(diffusivity_poly_to_surface);
    return;
  }

  memset(diffusivity_surface, 0, sizeof(double) * cn_2);

  for (i = 0; i < cn_2; i++)
  {
    /* count of overlapped polyhedrons by curr face : i */
    count = 0;

    for (j = 0; j < cn_d; j++)
    {
      cfn_3_2 = mesh_generate_diffusivity_metal_get_cfn_3_2(m, j);
      /* malloc cf_3_2 */
      cmc_memory_allocate(
        (void **)&cf_3_2, status, sizeof(int) * cfn_3_2);
      if (*status)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        cmc_error_message_memory_allocate("cf_3_2");
        cmc_memory_free(diffusivity_grain);
        cmc_memory_free(diffusivity_poly_to_surface);
        cmc_memory_free(diffusivity_surface);
        return;
      }

      mesh_generate_diffusivity_metal_get_cf_3_2(cf_3_2, m, j);
      for (k = 0; k < cfn_3_2; k++)
      {
        if (i == cf_3_2[k])
        {
          diffusivity_surface[i] += diffusivity_grain[j];
          count++;
        }
      }

      cmc_memory_free(cf_3_2);
    }

    if (count > 2)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stdout,
        "face %d 's overlap polyhedron count : %d, but should not be "
        "greater "
        "than 2.\n",
        i,
        count);
      cmc_memory_free(diffusivity_grain);
      cmc_memory_free(diffusivity_poly_to_surface);
      cmc_memory_free(diffusivity_surface);
      *status = 1;
      return;
    }

    if (count > 0)
    {
      diffusivity_surface[i] /= count;
    }
  }

  cfn_2_1 = 0;
  face_to_edge_number = 0;

  for (i = 0; i < cn_2; i++)
  {
    cfn_2_1 = mesh_generate_diffusivity_metal_get_cfn_2_1(m, i);
    face_to_edge_number += cfn_2_1;
  }

  /* malloc diffusivity_surface_to_edge */
  cmc_memory_allocate((void **)&diffusivity_surface_to_edge,
    status,
    sizeof(double) * face_to_edge_number);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("diffusivity_surface_to_edge");
    cmc_memory_free(diffusivity_grain);
    cmc_memory_free(diffusivity_poly_to_surface);
    cmc_memory_free(diffusivity_surface);
    return;
  }

  face_to_edge_number = 0;

  for (i = 0; i < cn_2; i++)
  {
    cfn_2_1 = mesh_generate_diffusivity_metal_get_cfn_2_1(m, i);

    for (j = 0; j < cfn_2_1; j++)
    {
      diffusivity_surface_to_edge[face_to_edge_number + j] =
        diffusivity_surface[i];
    }

    face_to_edge_number += cfn_2_1;
  }

  /* malloc diffusivity_edge */
  cmc_memory_allocate(
    (void **)&diffusivity_edge, status, sizeof(double) * cn_1);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("diffusivity_edge");
    cmc_memory_free(diffusivity_grain);
    cmc_memory_free(diffusivity_poly_to_surface);
    return;
  }

  memset(diffusivity_edge, 0, sizeof(double) * cn_1);

  for (i = 0; i < cn_1; i++)
  {
    /* count of overlapped face by curr edge : i */
    count = 0;

    for (j = 0; j < cn_2; j++)
    {
      cfn_2_1 = mesh_generate_diffusivity_metal_get_cfn_2_1(m, j);
      /* malloc cf_2_1 */
      cmc_memory_allocate(
        (void **)&cf_2_1, status, sizeof(int) * cfn_2_1);
      if (*status)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        cmc_error_message_memory_allocate("cf_2_1");
        cmc_memory_free(diffusivity_grain);
        cmc_memory_free(diffusivity_poly_to_surface);
        cmc_memory_free(diffusivity_surface);
        cmc_memory_free(diffusivity_surface_to_edge);
        cmc_memory_free(diffusivity_edge);
        return;
      }

      mesh_generate_diffusivity_metal_get_cf_2_1(cf_2_1, m, j);
      for (k = 0; k < cfn_2_1; k++)
      {
        /* count = overlap edge number */
        if (i == cf_2_1[k])
        {
          diffusivity_edge[i] += diffusivity_surface[j];
          count++;
        }
      }

      cmc_memory_free(cf_2_1);
    }

    if (count > 0)
    {
      diffusivity_edge[i] /= count;
    }
  }

  /* malloc diffusivity_edge_to_node */
  cmc_memory_allocate((void **)&diffusivity_edge_to_node,
    status,
    sizeof(double) * cn_1 * 2);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("diffusivity_edge_to_node");
    cmc_memory_free(diffusivity_grain);
    cmc_memory_free(diffusivity_poly_to_surface);
    cmc_memory_free(diffusivity_surface);
    cmc_memory_free(diffusivity_surface_to_edge);
    cmc_memory_free(diffusivity_edge);
    return;
  }

  for (i = 0; i < cn_1; i++)
  {
    diffusivity_edge_to_node[2 * i] = diffusivity_edge[i];
    diffusivity_edge_to_node[2 * i + 1] = diffusivity_edge[i];
  }

  cmc_memory_allocate((void **)&diffusivity_value,
    status,
    sizeof(double)
      * (cn_1 * 2 + face_to_edge_number + poly_to_face_number));
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("diffusivity_edge_to_node");
    cmc_memory_free(diffusivity_grain);
    cmc_memory_free(diffusivity_poly_to_surface);
    cmc_memory_free(diffusivity_surface);
    cmc_memory_free(diffusivity_surface_to_edge);
    cmc_memory_free(diffusivity_edge);
    cmc_memory_free(diffusivity_edge_to_node);
    return;
  }

  value_number = 0;

  for (i = 0; i < cn_1 * 2; i++)
  {
    diffusivity_value[value_number + i] = diffusivity_edge_to_node[i];
  }

  value_number += cn_1 * 2;

  for (i = 0; i < face_to_edge_number; i++)
  {
    diffusivity_value[value_number + i] =
      diffusivity_surface_to_edge[i];
  }

  value_number += face_to_edge_number;

  for (i = 0; i < poly_to_face_number; i++)
  {
    diffusivity_value[value_number + i] =
      diffusivity_poly_to_surface[i];
  }

  value_number += poly_to_face_number;

  if (to_print_diffusivity_value)
  {
    // fprintf(stdout, "\ndiffusivity_grain : ");
    // double_array_file_print(stdout, cn_d, diffusivity_grain,
    // "--raw"); fprintf(stdout, "diffusivity_poly_to_surface : ");
    // double_array_file_print(stdout,
    //   poly_to_face_number,
    //   diffusivity_poly_to_surface,
    //   "--raw");
    // fprintf(stdout, "diffusivity_surface : ");
    // double_array_file_print(stdout, cn_2, diffusivity_surface,
    // "--raw"); fprintf(stdout, "diffusivity_surface_to_edge : ");
    // double_array_file_print(stdout,
    //   face_to_edge_number,
    //   diffusivity_surface_to_edge,
    //   "--raw");
    // fprintf(stdout, "diffusivity_edge : ");
    // double_array_file_print(stdout, cn_1, diffusivity_edge, "--raw");
    // fprintf(stdout, "diffusivity_edge_to_node : ");
    // double_array_file_print(
    //   stdout, cn_1 * 2, diffusivity_edge_to_node, "--raw");
    // fprintf(stdout, "diffusivity_value length :
    // %d\n",value_number);
    // fprintf(stdout, "diffusivity_value : ");
    double_array_file_print(
      stdout, value_number, diffusivity_value, "--raw");
  }

  cmc_memory_free(diffusivity_grain);
  cmc_memory_free(diffusivity_poly_to_surface);
  cmc_memory_free(diffusivity_surface);
  cmc_memory_free(diffusivity_surface_to_edge);
  cmc_memory_free(diffusivity_edge);
  cmc_memory_free(diffusivity_edge_to_node);
  cmc_memory_free(diffusivity_value);
}

void mesh_generate_diffusivity_metal_scan_rodrigues(
  double **rodrigues,
  int *status,
  FILE *in,
  int cn_d)
{
  int i, j;

  string_locate_in_file_line(in, status, "   rodrigues:passive");
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fputs("cannot find the vertex field\n", stderr);
    return;
  }

  for (i = 0; i < cn_d; i++)
  {
    for (j = 0; j < 3; j++)
    {
      rodrigues[i][j] = double_file_scan(in);
      if (errno)
      {
        cmc_error_message_position_in_code(__FILE__, __LINE__);
        fprintf(stderr,
          "cannot scan a[%s%d%s]: %s\n",
          color_variable,
          i,
          color_none,
          strerror(errno));
        return;
      }
    }
  }
}

void mesh_generate_diffusivity_metal_get_coord_0(double *vertex_data,
  const mesh *m,
  int v_id)
{
  int i;
  for (i = 0; i < m->dim; i++)
  {
    vertex_data[i] = m->coord[v_id * m->dim + i];
  }
}

double mesh_generate_diffusivity_metal_get_coord_0_i(const mesh *m,
  int v_id,
  int i)
{
  return m->coord[v_id * m->dim + i];
}

// get vertex number of poly
int mesh_generate_diffusivity_metal_get_cfn_3_0(const mesh *m,
  int p_id)
{
  jagged1 m_cf_d_0_i;
  jagged2 m_cf_d_0;

  mesh_cf_part2(&m_cf_d_0, m, m->dim, 0);
  jagged2_part1(&m_cf_d_0_i, &m_cf_d_0, p_id);

  return m_cf_d_0_i.a0;
}

int mesh_generate_diffusivity_metal_get_cfn_3_2(const mesh *m,
  int p_id)
{
  jagged1 m_cf_d_0_i;
  jagged2 m_cf_d_0;

  mesh_cf_part2(&m_cf_d_0, m, m->dim, 2);
  jagged2_part1(&m_cf_d_0_i, &m_cf_d_0, p_id);

  return m_cf_d_0_i.a0;
}

int mesh_generate_diffusivity_metal_get_cfn_2_1(const mesh *m,
  int f_id)
{
  jagged1 m_cf_d_0_i;
  jagged2 m_cf_d_0;

  mesh_cf_part2(&m_cf_d_0, m, 2, 1);
  jagged2_part1(&m_cf_d_0_i, &m_cf_d_0, f_id);
  return m_cf_d_0_i.a0;
}

void mesh_generate_diffusivity_metal_get_cf_3_0(int *cf_3_0,
  const mesh *m,
  int p_id)
{
  jagged1 m_cf_d_0_i;
  jagged2 m_cf_d_0;

  mesh_cf_part2(&m_cf_d_0, m, m->dim, 0);
  jagged2_part1(&m_cf_d_0_i, &m_cf_d_0, p_id);
  for (int j = 0; j < m_cf_d_0_i.a0; j++)
  {
    cf_3_0[j] = jagged1_part1(&m_cf_d_0_i, j);
  }
}

void mesh_generate_diffusivity_metal_get_cf_3_2(int *cf_3_0,
  const mesh *m,
  int p_id)
{
  jagged1 m_cf_d_0_i;
  jagged2 m_cf_d_0;

  mesh_cf_part2(&m_cf_d_0, m, m->dim, 2);
  jagged2_part1(&m_cf_d_0_i, &m_cf_d_0, p_id);
  for (int j = 0; j < m_cf_d_0_i.a0; j++)
  {
    cf_3_0[j] = jagged1_part1(&m_cf_d_0_i, j);
  }
}

void mesh_generate_diffusivity_metal_get_cf_2_1(int *cf_2_1,
  const mesh *m,
  int f_id)
{
  jagged1 m_cf_d_0_i;
  jagged2 m_cf_d_0;

  mesh_cf_part2(&m_cf_d_0, m, 2, 1);
  jagged2_part1(&m_cf_d_0_i, &m_cf_d_0, f_id);
  for (int j = 0; j < m_cf_d_0_i.a0; j++)
  {
    cf_2_1[j] = jagged1_part1(&m_cf_d_0_i, j);
  }
}

void mesh_generate_diffusivity_metal_get_center_coord_3(
  double *center_coord,
  int *status,
  const mesh *m,
  int p_id)
{
  int i, j, cfn_3_0;
  int *vertex_ids = NULL;
  double *coord = NULL;

  cmc_memory_allocate(
    (void **)&coord, status, sizeof(double) * m->dim);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(double) * m->dim, "coord");
    return;
  }

  memset(coord, 0, sizeof(double) * m->dim);

  cfn_3_0 = mesh_generate_diffusivity_metal_get_cfn_3_0(m, p_id);
  cmc_memory_allocate(
    (void **)&vertex_ids, status, sizeof(int) * cfn_3_0);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_malloc(sizeof(int) * cfn_3_0, "cfn_3_0");
    free(coord);
    return;
  }

  mesh_generate_diffusivity_metal_get_cf_3_0(vertex_ids, m, p_id);

  for (i = 0; i < cfn_3_0; i++)
  {
    for (j = 0; j < m->dim; j++)
    {
      coord[j] += mesh_generate_diffusivity_metal_get_coord_0_i(
        m, vertex_ids[i], j);
    }
  }

  for (i = 0; i < m->dim; i++)
  {
    center_coord[i] = coord[i] / cfn_3_0;
  }

  cmc_memory_free(coord);
  cmc_memory_free(vertex_ids);
}

void mesh_generate_diffusivity_metal_get_max_height(double *H,
  int *status,
  const mesh *m)
{
  int i, cfn_3_0;
  int *vertex_ids = NULL;
  // temporarily save coordinates - xyz
  double vertex_xyz[3] = {0.0};
  double max_y = 0.0;

  for (i = 0; i < m->cn[3]; i++)
  {
    // number of vertices of current selected polyhedron
    cfn_3_0 = mesh_generate_diffusivity_metal_get_cfn_3_0(m, i);
    // ids of vertices of current selected polyhedron
    cmc_memory_allocate(
      (void **)&vertex_ids, status, sizeof(int) * cfn_3_0);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      cmc_error_message_malloc(sizeof(int) * cfn_3_0, "vertex_ids");
      *H = 0.0;
      return;
    }

    mesh_generate_diffusivity_metal_get_cf_3_0(vertex_ids, m, i);
    for (int j = 0; j < cfn_3_0; j++)
    {
      mesh_generate_diffusivity_metal_get_coord_0(
        vertex_xyz, m, vertex_ids[j]);

      if (vertex_xyz[1] > max_y)
        max_y = vertex_xyz[1];
    }

    cmc_memory_free(vertex_ids);
  }

  *H = max_y;
}

void mesh_generate_diffusivity_metal_get_height(double *hi_a,
  int *status,
  const mesh *m)
{
  int i, cn_d;
  double *crystal_center_coord = NULL;

  cn_d = m->cn[m->dim];
  cmc_memory_allocate(
    (void **)&crystal_center_coord, status, sizeof(double) * 3);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("crystal_center_coord");
    return;
  }

  for (i = 0; i < cn_d; i++)
  {
    mesh_generate_diffusivity_metal_get_center_coord_3(
      crystal_center_coord, status, m, i);
    if (*status)
    {
      cmc_error_message_position_in_code(__FILE__, __LINE__);
      fprintf(stdout,
        "error in function : %s\n",
        "mesh_generate_diffusivity_metal_get_center_coord_3");
      cmc_memory_free(crystal_center_coord);
      return;
    }

    hi_a[i] = crystal_center_coord[1];
  }

  cmc_memory_free(crystal_center_coord);
}

void mesh_generate_diffusivity_metal_calculate_crystal_tensor(
  double **tensor,
  int *status,
  const mesh *m,
  double D_0,
  int Q_1,
  int Q_2,
  double T)
{
  int i, cn_d;
  double H, x, y, z;
  double *hi_a = NULL;

  cn_d = m->cn[m->dim];

  mesh_generate_diffusivity_metal_get_max_height(&H, status, m);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stdout,
      "error in function : %s\n",
      "mesh_generate_diffusivity_metal_get_max_height");
    return;
  }

  cmc_memory_allocate((void **)&hi_a, status, sizeof(double) * cn_d);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    cmc_error_message_memory_allocate("hi_a");
    return;
  }

  mesh_generate_diffusivity_metal_get_height(hi_a, status, m);
  if (*status)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stdout,
      "error in function : %s\n",
      "mesh_generate_diffusivity_metal_get_height");
    return;
  }

  const double ideal_gas_constant = 8.314;
  for (i = 0; i < cn_d; i++)
  {
    if (i < cn_d / 2)
    {
      x = D_0 * exp(-1 * Q_1 / ideal_gas_constant / T);
    }
    else
    {
      x = D_0 * exp(-1 * Q_2 / ideal_gas_constant / T);
    }

    y = x;
    z = x;
    tensor[i][0] = x;
    tensor[i][1] = y;
    tensor[i][2] = z;
  }

  cmc_memory_free(hi_a);
}

void mesh_generate_diffusivity_metal_calculate_rodrigues_tensor(
  double **tensor,
  int *status,
  const mesh *m,
  double **rodrigues)
{
  int i, j, cn_d;
  double rx, ry, rz, s, d;
  double values[9] = {0.0};

  cn_d = m->cn[m->dim];

  for (i = 0; i < cn_d; i++)
  {
    rx = rodrigues[i][0];
    ry = rodrigues[i][1];
    rz = rodrigues[i][2];
    s = pow(rx, 2) + pow(ry, 2) + pow(rz, 2);
    d = 1 + s;

    values[0] = 1 + s - 2 * (pow(ry, 2) + pow(rz, 2));
    values[1] = 2 * (rx * ry - rz);
    values[2] = 2 * (rx * rz + ry);
    values[3] = 2 * (rx * ry + rz);
    values[4] = 1 + s - 2 * (pow(rx, 2) + pow(rz, 2));
    values[5] = 2 * (ry * rz - rx);
    values[6] = 2 * (rx * rz - ry);
    values[7] = 2 * (ry * rz + rx);
    values[8] = 1 + s - 2 * (pow(rx, 2) + pow(ry, 2));

    for (j = 0; j < 9; j++)
    {
      values[j] /= d;
    }

    memcpy(tensor[i], values, sizeof(double) * 9);
  }
}

void mesh_generate_diffusivity_metal_calculate_crystal_diffusivity(
  double **diffusivity,
  int cn_d,
  double **crystal_tensor,
  double **rodrigues_tensor)
{
  int i, p, q, row, col;
  double rgt[9] = {0.0};
  double dg_t[9] = {0.0};
  double tmp[9] = {0.0};

  for (i = 0; i < cn_d; i++)
  {
    /* transpose rodrigues_tensor, named rgt */
    for (p = 0; p < 9; p++)
    {
      row = p % 3;
      col = p / 3;
      rgt[p] = rodrigues_tensor[i][row * 3 + col];
    }

    /* dg_t = rodrigues_tensor */
    memcpy(dg_t, rodrigues_tensor[i], sizeof(double) * 9);
    /* dg_t = dg_t * crystal_tensor. */
    for (p = 0; p < 9; p++)
    {
      row = p % 3;
      col = p / 3;
      dg_t[p] = dg_t[p] * crystal_tensor[i][col];
    }
    /* tmp = dg_t */
    memcpy(tmp, dg_t, sizeof(double) * 9);
    /* dg_t = tmp * rgt. */
    for (p = 0; p < 9; p++)
    {
      row = p % 3;
      col = p / 3;
      dg_t[row * 3 + col] = 0;
      for (q = 0; q < 3; q++)
      {
        dg_t[row * 3 + col] += tmp[row * 3 + q] * rgt[q * 3 + col];
      }
    }

    for (p = 0; p < 9; p++)
    {
      diffusivity[i][p] = dg_t[p];
    }
  }
}
