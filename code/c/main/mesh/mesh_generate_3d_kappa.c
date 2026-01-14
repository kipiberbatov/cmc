#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <libgen.h>
#include <time.h>
#include <math.h>
#include "int.h"
#include "double_array2.h"

#include "cmc_error_message.h"
#include "double_array.h"
#include "mesh.h"

/*
stcell: 3-cells' volumes
stcell: 2-cells' areas
vpore: voluminous pore
fpore: flat/expansive pore
vpore.csv: voluminous pore volumes
fpore.csv: flat/expansive pore volumes and cumulative probabities
a: porosity
b: porosity of voluminous pores
c: porosity of flat/expansive pores
thickness: array with a size equal to the number of 2-cells
thickness_edge: array with a size equal to the number of 1-cells
kappa1: local conductivity from 1-cell to 0-cell
kappa2: local conductivity from 2-cell to 1-cell
kappa3: local conductivity from 3-cell to 2-cell
*/

/* log output */
#if 1
#define ENABLE_LOG
#endif
/* function declaration */
double *load_stcell(int n, const char *m_name);
double *load_stface(int n, const char *m_name);
double *load_vpore(int *n, const char *m_name);
double **load_fpore(int *n, const char *m_name);
int polyhedron_get_i_number_by_x_id(const mesh *m, int i, int x_id);
int polyhedron_get_face_number_by_id(const mesh *m, int p_id);   // Get the number of faces of a polygedron
int polyhedron_get_edge_number_by_id(const mesh *m, int p_id);   // Get the number of edges of a polygedron
int polyhedron_get_vertex_number_by_id(const mesh *m, int p_id); // Get the number of nodes of a polygedron
int face_get_edge_number_by_id(const mesh *m, int f_id);         // Get the number of edges of a face
void polyhedron_get_i_ids_by_x_id(int *ids, const mesh *m, int i, int x_id);
void polyhedron_get_face_ids(int *face_ids, const mesh *m, int p_id);
void polyhedron_get_edge_ids(int *edge_ids, const mesh *m, int p_id);
void polyhedron_get_vertex_ids(int *vertex_ids, const mesh *m, int p_id);
int face_get_vertex_number_by_face_id(const mesh *m, int f_id);
void face_get_vertex_ids_by_face_id(int *vertex_ids, const mesh *m, int f_id);
int edge_get_vertex_number_by_edge_id(const mesh *m, int e_id);
void edge_get_vertex_ids_by_edge_id(int *vertex_ids, const mesh *m, int e_id);
void vertex_get_data(double *vertex_data, const mesh *m, int v_id);
double vertex_get_data_i(const mesh *m, int v_id, int i);
void polyhedron_get_center_coord_by_id(double *center_coord, const mesh *m, int p_id);
void face_get_center_coord_by_id(double *center_coord, const mesh *m, int f_id);
void edge_get_center_coord_by_id(double *center_coord, const mesh *m, int e_id);
double vertex_get_distance(const mesh *m, double *coord_1, double *coord_2);
double polyhedron_to_face_distance_by_id(const mesh *m, int p_id, int f_id);
double polyhedron_to_edge_distance_by_id(const mesh *m, int p_id, int e_id);
double polyhedron_get_model_volume(const mesh *m);
void double_array_file_print_raw_new_line(FILE *out, int n, const double *a);
char *get_file_name(const char *filePath);
char *get_file_directory(const char *filePath);
int mesh_generate_3d_kappa(const mesh *m, double a, const char *output_filepath, const char *data_dirpath);
void traverse_vpore_volume(int *polyhedron_ids, int *face_ids_used, int *curr_face_id, const mesh *m, double *vpore_volumes, double *stcell_volumes, int vpore_size);
void traverse_fpore_volume_and_calculate(double *thickness, double *thickness_edge, double *fpore_used, double *fpore_volume_used, int *fpore_used_sum, int *face_ids_used, int *curr_face_id, const mesh *m, double **fpore, int fpore_size, double *stface_data, double a, double b, double module_volumes, FILE *log_out);
void get_total_edge_number(int *face_total_edges, const mesh *m);
// void replace_thickness_edge_by_thickness(double *thickness_edge, int *face_total_edges, const mesh *m, double *thickness);
void calculate_thickness_by_vpore(double *thickness, const mesh *m, int vpore_size, int *polyhedron_ids);
void calculate_thickness_edge_by_vpore(double *thickness_edge, const mesh *m, int vpore_size, int *polyhedron_ids);
void calculate_kappa1(double *kappa1, const mesh *m, double *thickness_edge);
void calculate_kappa2(double *kappa2, int *kappa2_n, const mesh *m, double *thickness, int face_total_edges);
void calculate_kappa3(double *kappa3, int *kappa3_n, const mesh *m, double *stface_data, int vpore_size, int *polyhedron_ids);
void calculate_kappa(double *kappa, const mesh *m, double *kappa1, double *kappa2, double *kappa3, int edge_total_vertexs, int face_total_edges, int polyhedron_total_faces);
/*----------------------------------------------------------------------------------------------------------------------------
                                                 main
----------------------------------------------------------------------------------------------------------------------------*/
int main(int argc, char **argv)
{
  char *m_format, *m_name, *data_dirpath;
  FILE *m_file;
  matrix_sparse **m_bd;
  mesh *m;
  double a;

  if (argc != 5)
  {
    cmc_error_message_position_in_code(__FILE__, __LINE__);
    fprintf(stderr,
            "number of command line arguments should be 4; instead it is %d\n", argc);
    errno = EINVAL;
    goto end;
  }

  m_format = argv[1];
  m_name = argv[2];
  data_dirpath = argv[3];
  a = atof(argv[4]);

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

  fclose(m_file);

  mesh_generate_3d_kappa(m, a, m_name, data_dirpath);

m_free:
  mesh_free(m);
  return 0;
end:
  return errno;
}
/*----------------------------------------------------------------------------------------------------------------------------
                                                 src
----------------------------------------------------------------------------------------------------------------------------*/
int mesh_generate_3d_kappa(const mesh *m, double a, const char *output_filepath, const char *input_dirpath)
{
  char *output_dirpath = get_file_directory(output_filepath);
  char *output_filename = get_file_name(output_filepath);
  if (!output_filename)
  {
    return -1;
  }

  /* log output begin */
  // input files fpore(flat pores' volumes and cumulative probabilities) vpore(voluminous pores' volumes) stcell(3-cells' volumes) stface(2-cells' surface areas)
  char fpore_file_path[1024] = {0};
  char vpore_file_path[1024] = {0};
  char stcell_file_path[1024] = {0};
  char stface_file_path[1024] = {0};

  // file path
  strcat(fpore_file_path, input_dirpath);
  strcat(vpore_file_path, input_dirpath);
  strcat(stcell_file_path, input_dirpath);
  strcat(stface_file_path, input_dirpath);

  strcat(fpore_file_path, "/");
  strcat(vpore_file_path, "/");
  strcat(stcell_file_path, "/");
  strcat(stface_file_path, "/");

  // filename
  strcat(fpore_file_path, output_filename);
  strcat(vpore_file_path, output_filename);
  strcat(stcell_file_path, output_filename);
  strcat(stface_file_path, output_filename);

  // file type
  strcat(fpore_file_path, "_fpore.csv");
  strcat(vpore_file_path, "_vpore.csv");
  strcat(stcell_file_path, ".stcell");
  strcat(stface_file_path, ".stface");

  // output files, log,used_fpore,thickness_fpore, thickness_end, thickness_edge_fpore, thickness_edge_end, kappa
  char log_file_path[1024] = {0};
  char used_fpore_file_path[1024] = {0};
  char thickness_fpore_file_path[1024] = {0};
  char thickness_edge_fpore_file_path[1024] = {0};
  char thickness_end_path[1024] = {0};
  char thickness_edge_end_path[1024] = {0};
  char kappa_path[1024] = {0};

  // output path
  strcat(log_file_path, output_dirpath);
  strcat(used_fpore_file_path, output_dirpath);
  strcat(thickness_fpore_file_path, output_dirpath);
  strcat(thickness_edge_fpore_file_path, output_dirpath);
  strcat(thickness_end_path, output_dirpath);
  strcat(thickness_edge_end_path, output_dirpath);
  strcat(kappa_path, output_dirpath);

  strcat(log_file_path, "/");
  strcat(used_fpore_file_path, "/");
  strcat(thickness_fpore_file_path, "/");
  strcat(thickness_edge_fpore_file_path, "/");
  strcat(thickness_end_path, "/");
  strcat(thickness_edge_end_path, "/");
  strcat(kappa_path, "/");

  // output filename
  strcat(log_file_path, output_filename);
  strcat(used_fpore_file_path, output_filename);
  strcat(thickness_fpore_file_path, output_filename);
  strcat(thickness_edge_fpore_file_path, output_filename);
  strcat(thickness_end_path, output_filename);
  strcat(thickness_edge_end_path, output_filename);
  strcat(kappa_path, output_filename);

  // output filetype
  strcat(log_file_path, "_log.txt");
  strcat(used_fpore_file_path, "_used_fpore.txt");
  strcat(thickness_fpore_file_path, "_thickness_fpore.txt");
  strcat(thickness_edge_fpore_file_path, "_thickness_edge_fpore.txt");
  strcat(thickness_end_path, "_thickness_end.txt");
  strcat(thickness_edge_end_path, "_thickness_edge_end.txt");
  strcat(kappa_path, "_kappa.txt");

  free(output_dirpath);
  free(output_filename);

  if (m == NULL)
  {
    return 1;
  }

#ifdef ENABLE_LOG
  FILE *log_out = fopen(log_file_path, "w");
  FILE *fpore_used_out = fopen(used_fpore_file_path, "w");
  FILE *thickness_fpore_out = fopen(thickness_fpore_file_path, "w");
  FILE *thickness_edge_fpore_out = fopen(thickness_edge_fpore_file_path, "w");
  FILE *thickness_end_out = fopen(thickness_end_path, "w");
  FILE *thickness_edge_end_out = fopen(thickness_edge_end_path, "w");
#endif
  FILE *kappa_file = fopen(kappa_path, "w");

  /* output log end */

  /* 1.Create thickness array, array's size = number of faces = cn[2], initial = 0 */
  double *thickness = (double *)malloc(sizeof(double) * m->cn[2]);
  memset(thickness, 0, sizeof(double) * m->cn[2]);

  /* 2.Read v_pore volumes，denoted as vpore_volumes，its size denoted as vpore_size */
  int vpore_size = 0;
  double *vpore_volumes = load_vpore(&vpore_size, vpore_file_path);

  /* Print vpore volumes and size*/
#ifdef ENABLE_LOG
  fprintf(log_out, "vpore_volumes size : %d\n", vpore_size);
  double_array_file_print(log_out, vpore_size, vpore_volumes, "--raw");
#endif

  /* 3.Read f_pore volumes and cdf，denoted as fpore_volumes & fpore_rates，size denoted as fpore_size */
  int fpore_size = 0;
  double **fpore = load_fpore(&fpore_size, fpore_file_path);

  /* Print fpore size, volume, cdf */
#ifdef ENABLE_LOG
  fprintf(log_out, "fpore_volumes size : %d\n", fpore_size);

  /* fpore[0] : fpore_volumes */
  double_array_file_print(log_out, fpore_size, fpore[0], "--raw");
  /* fpore[1] : fpore_rates */
  double_array_file_print(log_out, fpore_size, fpore[1], "--raw");
#endif

  /* 4.Read stcell，denoted as stcell_volumes */
  double *stcell_volumes = load_stcell(m->cn[3], stcell_file_path);

  /* Print stcell_volumes */
#ifdef ENABLE_LOG
  fprintf(log_out, "stcell_volumes : ");
  double_array_file_print(log_out, m->cn[3], stcell_volumes, "--raw");
#endif

  /* 5.Go through all vpore_volumes, current selected denoted as vpore_v */
  int *polyhedron_ids = (int *)malloc(sizeof(int) * vpore_size);
  int *face_ids_used = (int *)malloc(sizeof(int) * m->cn[2]);
  int curr_face_id = 0;
  memset(face_ids_used, 0, m->cn[2]);

  /* 6.Compare vpore volume and 3-cell volume, find the closest one for each vpore. */
  traverse_vpore_volume(polyhedron_ids, face_ids_used, &curr_face_id, m, vpore_volumes, stcell_volumes, vpore_size);

  calculate_thickness_by_vpore(thickness, m, vpore_size, polyhedron_ids);

#ifdef ENABLE_LOG
  fprintf(log_out, "vpore_use_face_ids : ");
  int_array_file_print(log_out, curr_face_id, face_ids_used, "--raw");
  fprintf(log_out, "polyhedron_ids : ");
  int_array_file_print(log_out, vpore_size, polyhedron_ids, "--raw");
#endif

  /* 7.porosity = a、vpore‘s porosity = b */
  double volumes = double_array_total_sum(vpore_size, vpore_volumes);
  double module_volumes = polyhedron_get_model_volume(m);
  // double a=0.0651;
  double b = volumes / module_volumes;

  /* print module volume & b */
#ifdef ENABLE_LOG
  fprintf(log_out, "vpore volumes : %lf, vpore module volumes : %lf\n", volumes, module_volumes);
  fprintf(log_out, "b=%lf\n", b);
#endif

  double *fpore_used = (double *)malloc(sizeof(double) * fpore_size);
  double *fpore_volume_used = (double *)malloc(sizeof(double) * fpore_size);
  double *stface_data = load_stface(m->cn[2], stface_file_path);
  int fpore_used_sum;

  double *thickness_edge = (double *)malloc(sizeof(double) * m->cn[1]);
#ifdef ENABLE_LOG
  fprintf(log_out, "thickness_edge size : %d\n", m->cn[1]);
#endif
  memset(thickness_edge, 0, sizeof(double) * m->cn[1]);

  /* calculate thickness_edge by vpore */
  /* 8. Select fpore volume by  generating a random number from 0 to 1 and using this number to map cdf to volume.*/
  calculate_thickness_edge_by_vpore(thickness_edge, m, vpore_size, polyhedron_ids);

  traverse_fpore_volume_and_calculate(thickness, thickness_edge, fpore_used, fpore_volume_used, &fpore_used_sum, face_ids_used, &curr_face_id, m, fpore, fpore_size, stface_data, a, b, module_volumes, log_out);

#ifdef ENABLE_LOG
  double_array_file_print_raw_new_line(thickness_fpore_out, m->cn[2], thickness);
  double_array_file_print_raw_new_line(thickness_edge_fpore_out, m->cn[1], thickness_edge);

  for (int i = 0; i < fpore_used_sum; i++)
  {
    fprintf(fpore_used_out, "%g,%g\n", fpore_volume_used[i], fpore_used[i]);
  }
#endif

  int face_total_edges;
  get_total_edge_number(&face_total_edges, m);
  // replace_thickness_edge_by_thickness(thickness_edge, &face_total_edges, m, thickness);

#ifdef ENABLE_LOG
  double_array_file_print_raw_new_line(thickness_end_out, m->cn[2], thickness);
  double_array_file_print_raw_new_line(thickness_edge_end_out, m->cn[1], thickness_edge);
#endif

  /* kappa1, size is m->cn[1] * 2 */
  int kappa1_size = m->cn[1] * 2;
  double *kappa1 = (double *)malloc(sizeof(double) * kappa1_size);
  calculate_kappa1(kappa1, m, thickness_edge);

  /* kappa2 */
  int kappa2_n;
  double *kappa2 = (double *)malloc(sizeof(double) * face_total_edges);
  memset(kappa2, 0, sizeof(double) * face_total_edges);
  calculate_kappa2(kappa2, &kappa2_n, m, thickness, face_total_edges);

  /* kappa3 */
  int polyhedron_total_faces = 0;
  /* polyhedron_total_faces */
  for (int i = 0; i < m->cn[3]; i++)
  {
    polyhedron_total_faces += polyhedron_get_face_number_by_id(m, i);
  }
  int kappa3_n;
  double *kappa3 = (double *)malloc(sizeof(double) * polyhedron_total_faces);
  memset(kappa3, 0, sizeof(double) * polyhedron_total_faces);
  calculate_kappa3(kappa3, &kappa3_n, m, stface_data, vpore_size, polyhedron_ids);

  /* kappa */
  int kappa_size = m->cn[1] * 2 + face_total_edges + polyhedron_total_faces;
  double *kappa = (double *)malloc(sizeof(double) * kappa_size);
  memset(kappa, 0, sizeof(double) * kappa_size);
  calculate_kappa(kappa, m, kappa1, kappa2, kappa3, m->cn[1] * 2, face_total_edges, polyhedron_total_faces);

  /* print to file */
  double_array_file_print(kappa_file, kappa_size, kappa, "--raw");

#ifdef ENABLE_LOG

  fprintf(log_out, "kappa1 : ");
  double_array_file_print(log_out, kappa1_size, kappa1, "--raw");
  fprintf(log_out, "kappa2 : ");
  double_array_file_print(log_out, kappa2_n, kappa2, "--raw");
  fprintf(log_out, "kappa3 : ");
  double_array_file_print(log_out, kappa3_n, kappa3, "--raw");

  fclose(log_out);
  fclose(fpore_used_out);
  fclose(thickness_fpore_out);
  fclose(thickness_edge_fpore_out);
  fclose(thickness_end_out);
  fclose(thickness_edge_end_out);
#endif
  fclose(kappa_file);

  free(kappa);
  free(kappa3);
  free(kappa2);
  // free(kappa1);

  free(fpore_volume_used);
  free(fpore_used);
  free(stface_data);
  free(stcell_volumes);
  free(face_ids_used);
  free(polyhedron_ids);

  free(thickness);
  free(thickness_edge);

  free(vpore_volumes);
  double_array2_free(fpore, 2);

  return 0;
}

static double double_file_scan(FILE *in)
{
  int correct;
  double a;

  correct = fscanf(in, "%lf", &a);
  if (correct <= 0)
  {
    // color_error_position(__FILE__, __LINE__);
    if (correct == 0)
      fputs("input is not a valid 64-bit floating point number: %s\n", stderr);
    else
    {
      // fputs("there is no number to scan\n", stderr);
    }

    errno = EINVAL;
    return -1;
  }
  return a;
}

static void string_file_scan(FILE *in, char *s, int n)
{
  int c, i = 0;

  while (i < n - 1)
  {
    c = fgetc(in);
    if (c == EOF)
    {
      s[i] = '\0';
      return;
    }
    s[i] = c;
    ++i;
  }
  s[n - 1] = '\0';
}

double *load_stcell(int n, const char *m_name)
{
  double *stcell_volumes = (double *)malloc(sizeof(double) * n);
  FILE *in;
  in = fopen(m_name, "r");

  for (int i = 0; i < n; i++)
  {
    stcell_volumes[i] = double_file_scan(in);
  }

  fclose(in);

  return stcell_volumes;
}

double *load_stface(int n, const char *m_name)
{
  double *stface = (double *)malloc(sizeof(double) * n);
  FILE *in;
  in = fopen(m_name, "r");

  for (int i = 0; i < n; i++)
  {
    stface[i] = double_file_scan(in);
  }

  fclose(in);

  return stface;
}

double *load_vpore(int *n, const char *m_name)
{
  *n = 0;
  int size = 100;
  double *vpore_volumes = (double *)malloc(sizeof(double) * 100);
  FILE *in;
  in = fopen(m_name, "r");

  while (1)
  {
    double volume = double_file_scan(in);
    if (volume == -1)
    {
      break;
    }

    if (*n >= size)
    {
      double *tmp = (double *)malloc(sizeof(double) * size);
      for (int i = 0; i < size; i++)
      {
        tmp[i] = vpore_volumes[i];
      }
      free(vpore_volumes);
      vpore_volumes = (double *)malloc(sizeof(double) * (size + 100));

      for (int i = 0; i < size; i++)
      {
        vpore_volumes[i] = tmp[i];
      }

      size += 100;

      free(tmp);
    }

    vpore_volumes[*n] = volume;
    (*n)++;
  }

  double *tmp = (double *)malloc(sizeof(double) * (*n));
  for (int i = 0; i < *n; i++)
  {
    tmp[i] = vpore_volumes[i];
  }

  free(vpore_volumes);
  vpore_volumes = (double *)malloc(sizeof(double) * (*n));

  for (int i = 0; i < *n; i++)
  {
    vpore_volumes[i] = tmp[i];
  }

  free(tmp);

  fclose(in);

  return vpore_volumes;
}

double **load_fpore(int *n, const char *m_name)
{
  *n = 0;
  int size = 100;
  double *vpore_volumes = (double *)malloc(sizeof(double) * 100);
  double *vpore_rates = (double *)malloc(sizeof(double) * 100);
  FILE *in;
  in = fopen(m_name, "r");

  while (1)
  {
    double volume = double_file_scan(in);

    if (volume == -1)
    {
      break;
    }

    char str[2];
    string_file_scan(in, str, 2);
    double rate = double_file_scan(in);

    string_file_scan(in, str, 2);
    int count = int_file_scan(in);

    if (*n >= size)
    {
      /* resize begin */
      double *tmp = (double *)malloc(sizeof(double) * size);
      double *tmp1 = (double *)malloc(sizeof(double) * size);
      for (int i = 0; i < size; i++)
      {
        tmp[i] = vpore_volumes[i];
        tmp1[i] = vpore_rates[i];
      }

      free(vpore_volumes);
      vpore_volumes = (double *)malloc(sizeof(double) * (size + 100));
      vpore_rates = (double *)malloc(sizeof(double) * (size + 100));

      for (int i = 0; i < size; i++)
      {
        vpore_volumes[i] = tmp[i];
        vpore_rates[i] = tmp1[i];
      }

      size += 100;

      free(tmp);
      free(tmp1);
      /* resize end */
    }

    vpore_volumes[*n] = volume;
    vpore_rates[*n] = rate;
    (*n)++;
  }

  /* copy begin */
  double *tmp = (double *)malloc(sizeof(double) * (*n));
  double *tmp1 = (double *)malloc(sizeof(double) * (*n));
  for (int i = 0; i < *n; i++)
  {
    tmp[i] = vpore_volumes[i];
    tmp1[i] = vpore_rates[i];
  }

  free(vpore_volumes);
  free(vpore_rates);
  vpore_volumes = (double *)malloc(sizeof(double) * (*n));
  vpore_rates = (double *)malloc(sizeof(double) * (*n));

  for (int i = 0; i < *n; i++)
  {
    vpore_volumes[i] = tmp[i];
    vpore_rates[i] = tmp1[i];
  }

  free(tmp);
  free(tmp1);
  /* copy end */

  double **vpore = (double **)malloc(sizeof(double *) * 2);
  vpore[0] = vpore_volumes;
  vpore[1] = vpore_rates;

  fclose(in);

  return vpore;
}

int polyhedron_get_i_number_by_x_id(const mesh *m, int i, int x_id)
{
  int m_cn_d;
  jagged1 m_cf_d_0_i;
  jagged2 m_cf_d_0;

  m_cn_d = m->cn[m->dim];
  mesh_cf_part2(&m_cf_d_0, m, m->dim, i);

  jagged2_part1(&m_cf_d_0_i, &m_cf_d_0, x_id);
  return m_cf_d_0_i.a0;
}

// get face number of poly
int polyhedron_get_face_number_by_id(const mesh *m, int p_id)
{
  return polyhedron_get_i_number_by_x_id(m, 2, p_id);
}

// get edge number of poly
int polyhedron_get_edge_number_by_id(const mesh *m, int p_id)
{
  return polyhedron_get_i_number_by_x_id(m, 1, p_id);
}

// get vertex number of poly
int polyhedron_get_vertex_number_by_id(const mesh *m, int p_id)
{
  return polyhedron_get_i_number_by_x_id(m, 0, p_id);
}

// get edge number of face
int face_get_edge_number_by_id(const mesh *m, int f_id)
{
  int m_cn_d;
  jagged1 m_cf_d_0_i;
  jagged2 m_cf_d_0;

  m_cn_d = m->cn[2];
  mesh_cf_part2(&m_cf_d_0, m, 2, 1);

  jagged2_part1(&m_cf_d_0_i, &m_cf_d_0, f_id);
  return m_cf_d_0_i.a0;
}

// x -> face、edge, i -> 0(polyhedron_to_vertex)、1(polyhedron_to_edge)、2(polyhedron_to_face)
void polyhedron_get_i_ids_by_x_id(int *ids, const mesh *m, int i, int x_id)
{
  int m_cn_d;
  jagged1 m_cf_d_0_i;
  jagged2 m_cf_d_0;

  m_cn_d = m->cn[m->dim];
  mesh_cf_part2(&m_cf_d_0, m, m->dim, i);

  jagged2_part1(&m_cf_d_0_i, &m_cf_d_0, x_id);
  for (int j = 0; j < m_cf_d_0_i.a0; j++)
  {
    ids[j] = jagged1_part1(&m_cf_d_0_i, j);
  }
}

void polyhedron_get_face_ids(int *face_ids, const mesh *m, int p_id)
{
  polyhedron_get_i_ids_by_x_id(face_ids, m, 2, p_id);
}

void polyhedron_get_edge_ids(int *edge_ids, const mesh *m, int p_id)
{
  polyhedron_get_i_ids_by_x_id(edge_ids, m, 1, p_id);
}

void polyhedron_get_vertex_ids(int *vertex_ids, const mesh *m, int p_id)
{
  polyhedron_get_i_ids_by_x_id(vertex_ids, m, 0, p_id);
}

int face_get_vertex_number_by_face_id(const mesh *m, int f_id)
{
  int m_cn_d;
  jagged1 m_cf_d_0_i;
  jagged2 m_cf_d_0;

  m_cn_d = m->cn[2];
  mesh_cf_part2(&m_cf_d_0, m, 2, 0);

  jagged2_part1(&m_cf_d_0_i, &m_cf_d_0, f_id);
  return m_cf_d_0_i.a0;
}

void face_get_edge_ids_by_face_id(int *edge_ids, const mesh *m, int f_id)
{
  int m_cn_d;
  jagged1 m_cf_d_0_i;
  jagged2 m_cf_d_0;

  m_cn_d = m->cn[2];
  mesh_cf_part2(&m_cf_d_0, m, 2, 1);

  jagged2_part1(&m_cf_d_0_i, &m_cf_d_0, f_id);
  for (int j = 0; j < m_cf_d_0_i.a0; j++)
  {
    edge_ids[j] = jagged1_part1(&m_cf_d_0_i, j);
  }
}

void face_get_vertex_ids_by_face_id(int *vertex_ids, const mesh *m, int f_id)
{
  int m_cn_d;
  jagged1 m_cf_d_0_i;
  jagged2 m_cf_d_0;

  m_cn_d = m->cn[2];
  mesh_cf_part2(&m_cf_d_0, m, 2, 0);

  jagged2_part1(&m_cf_d_0_i, &m_cf_d_0, f_id);
  for (int j = 0; j < m_cf_d_0_i.a0; j++)
  {
    vertex_ids[j] = jagged1_part1(&m_cf_d_0_i, j);
  }
}

int edge_get_vertex_number_by_edge_id(const mesh *m, int e_id)
{
  int m_cn_d;
  jagged1 m_cf_d_0_i;
  jagged2 m_cf_d_0;

  m_cn_d = m->cn[2];
  mesh_cf_part2(&m_cf_d_0, m, 1, 0);

  jagged2_part1(&m_cf_d_0_i, &m_cf_d_0, e_id);
  return m_cf_d_0_i.a0;
}

void edge_get_vertex_ids_by_edge_id(int *vertex_ids, const mesh *m, int e_id)
{
  int m_cn_d;
  jagged1 m_cf_d_0_i;
  jagged2 m_cf_d_0;

  m_cn_d = m->cn[1];
  mesh_cf_part2(&m_cf_d_0, m, 1, 0);

  jagged2_part1(&m_cf_d_0_i, &m_cf_d_0, e_id);
  for (int j = 0; j < m_cf_d_0_i.a0; j++)
  {
    vertex_ids[j] = jagged1_part1(&m_cf_d_0_i, j);
  }
}

void vertex_get_data(double *vertex_data, const mesh *m, int v_id)
{
  for (int i = 0; i < m->dim; i++)
  {
    vertex_data[i] = m->coord[v_id * m->dim + i];
  }
}

double vertex_get_data_i(const mesh *m, int v_id, int i)
{
  return m->coord[v_id * m->dim + i];
}

void polyhedron_get_center_coord_by_id(double *center_coord, const mesh *m, int p_id)
{
  double *coord = (double *)malloc(sizeof(double) * m->dim);
  memset(coord, 0, sizeof(double) * m->dim);

  int vertex_number = polyhedron_get_vertex_number_by_id(m, p_id);
  int *vertex_ids = (int *)malloc(sizeof(int) * vertex_number);
  polyhedron_get_vertex_ids(vertex_ids, m, p_id);

  for (int i = 0; i < vertex_number; i++)
  {
    for (int j = 0; j < m->dim; j++)
    {
      coord[j] += vertex_get_data_i(m, vertex_ids[i], j);
    }
  }

  for (int i = 0; i < m->dim; i++)
  {
    center_coord[i] = coord[i] / vertex_number;
  }

  free(coord);
  free(vertex_ids);
}

void face_get_center_coord_by_id(double *center_coord, const mesh *m, int f_id)
{
  double *coord = (double *)malloc(sizeof(double) * m->dim);
  memset(coord, 0, sizeof(double) * m->dim);

  int vertex_number = face_get_vertex_number_by_face_id(m, f_id);
  int *vertex_ids = (int *)malloc(sizeof(int) * vertex_number);
  face_get_vertex_ids_by_face_id(vertex_ids, m, f_id);

  for (int i = 0; i < vertex_number; i++)
  {
    for (int j = 0; j < m->dim; j++)
      coord[j] += vertex_get_data_i(m, vertex_ids[i], j);
  }

  for (int i = 0; i < m->dim; i++)
  {
    center_coord[i] = coord[i] / vertex_number;
  }

  free(coord);
  free(vertex_ids);
}

void edge_get_center_coord_by_id(double *center_coord, const mesh *m, int e_id)
{
  double *coord = (double *)malloc(sizeof(double) * m->dim);
  memset(coord, 0, sizeof(double) * m->dim);

  int vertex_number = edge_get_vertex_number_by_edge_id(m, e_id);
  int *vertex_ids = (int *)malloc(sizeof(int) * vertex_number);
  edge_get_vertex_ids_by_edge_id(vertex_ids, m, e_id);

  for (int i = 0; i < vertex_number; i++)
  {
    for (int j = 0; j < m->dim; j++)
      coord[j] += vertex_get_data_i(m, vertex_ids[i], j);
  }

  for (int i = 0; i < m->dim; i++)
  {
    center_coord[i] = coord[i] / vertex_number;
  }

  free(coord);
  free(vertex_ids);
}

double vertex_get_distance(const mesh *m, double *coord_1, double *coord_2)
{
  double distance = 0.0;
  if (m->dim < 2 || m->dim > 3)
  {
    return distance;
  }

  if (m->dim == 2)
  {
    double x1 = coord_1[0];
    double y1 = coord_1[1];
    double x2 = coord_2[0];
    double y2 = coord_2[1];
    distance = sqrt((pow(x1 - x2, 2) + pow(y1 - y2, 2)));
  }
  else
  {
    double x1 = coord_1[0];
    double y1 = coord_1[1];
    double z1 = coord_1[2];
    double x2 = coord_2[0];
    double y2 = coord_2[1];
    double z2 = coord_2[2];
    distance = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2) + pow(z1 - z2, 2));
  }

  return distance;
}

double polyhedron_to_face_distance_by_id(const mesh *m, int p_id, int f_id)
{
  double *polyhedron_center_coord = (double *)malloc(sizeof(double) * m->dim);
  double *face_center_coord = (double *)malloc(sizeof(double) * m->dim);

  polyhedron_get_center_coord_by_id(polyhedron_center_coord, m, p_id);
  face_get_center_coord_by_id(face_center_coord, m, f_id);

  double distance = vertex_get_distance(m, polyhedron_center_coord, face_center_coord);

  free(polyhedron_center_coord);
  free(face_center_coord);

  return distance;
}

double polyhedron_to_edge_distance_by_id(const mesh *m, int p_id, int e_id)
{
  double *polyhedron_center_coord = (double *)malloc(sizeof(double) * m->dim);
  double *edge_center_coord = (double *)malloc(sizeof(double) * m->dim);

  polyhedron_get_center_coord_by_id(polyhedron_center_coord, m, p_id);
  edge_get_center_coord_by_id(edge_center_coord, m, p_id);

  double distance = vertex_get_distance(m, polyhedron_center_coord, edge_center_coord);

  free(polyhedron_center_coord);
  free(edge_center_coord);

  return distance;
}

/* calculate module volume */
double polyhedron_get_model_volume(const mesh *m)
{
  // temporarily save coordinates - xyz
  double *vertex_xyz = (double *)malloc(sizeof(double) * 3);

  double max_x = 0.0, max_y = 0.0, max_z = 0.0;

  for (int i = 0; i < m->cn[3]; i++)
  {
    // number of vertices of current selected polyhedron
    int vertex_number = polyhedron_get_vertex_number_by_id(m, i);
    // ids of vertices of current selected polyhedron
    int *vertex_ids = (int *)malloc(sizeof(int) * vertex_number);
    polyhedron_get_vertex_ids(vertex_ids, m, i);
    for (int j = 0; j < vertex_number; j++)
    {
      vertex_get_data(vertex_xyz, m, vertex_ids[j]);
      // double_array_file_print(stdout,3,vertex_xyz,"--raw");
      if (vertex_xyz[0] > max_x)
        max_x = vertex_xyz[0];

      if (vertex_xyz[1] > max_y)
        max_y = vertex_xyz[1];

      if (vertex_xyz[2] > max_z)
        max_z = vertex_xyz[2];
    }

    free(vertex_ids);
  }

  free(vertex_xyz);

  return max_x * max_y * max_z;
}

/* double print new line */
void double_array_file_print_raw_new_line(FILE *out, int n, const double *a)
{
  for (int i = 0; i < n - 1; ++i)
    fprintf(out, "%d %g\n", i, a[i]);
}

char *get_file_name(const char *filePath)
{
  const char *fileName = strrchr(filePath, '/');
  const char *fileNameEnd = strrchr(filePath, '.');
  if (fileName)
  {
    fileName++;
  }
  else
  {
    fileName = filePath;
  }

  if (!fileNameEnd)
  {
    fileNameEnd = filePath;
  }

  if (fileNameEnd - fileName <= 0)
  {
    return NULL;
  }

  char *filename = (char *)malloc(sizeof(char) * (fileNameEnd - fileName + 1));
  memset(filename, 0, sizeof(char) * (fileNameEnd - fileName + 1));
  memcpy(filename, fileName, sizeof(char) * (fileNameEnd - fileName));

  return filename;
}

char *get_file_directory(const char *filePath)
{
  const char *fileName = strrchr(filePath, '/');
  if (!fileName)
  {
    fileName = filePath;
  }

  char *dirpath = (char *)malloc(sizeof(char) * (fileName - filePath + 1));
  memset(dirpath, 0, sizeof(char) * (fileName - filePath + 1));
  memcpy(dirpath, filePath, sizeof(char) * (fileName - filePath));

  return dirpath;
}

void traverse_vpore_volume(int *polyhedron_ids, int *face_ids_used, int *curr_face_id, const mesh *m, double *vpore_volumes, double *stcell_volumes, int vpore_size)
{
  double *vpore_diffs = (double *)malloc(sizeof(double) * vpore_size);
  for (int i = 0; i < vpore_size; i++)
  {
    polyhedron_ids[i] = -1;
    vpore_diffs[i] = 0.00;
  }

  /* Compare selected vpore_v and all stcell_volumes,find out closest stcell_volume, save this stcell_volume's id */
  for (int i = 0; i < vpore_size; i++)
  {
    for (int j = 0; j < m->cn[3]; j++)
    {
      double diff = vpore_volumes[i] - stcell_volumes[j];
      if (polyhedron_ids[i] == -1 || fabs(diff) < fabs(vpore_diffs[i]))
      {
        polyhedron_ids[i] = j;
        vpore_diffs[i] = diff;
      }
    }

    int polyhedron_id = polyhedron_ids[i];

    int face_number = polyhedron_get_face_number_by_id(m, polyhedron_id);
    int *face_ids = (int *)malloc(sizeof(int) * face_number);
    polyhedron_get_face_ids(face_ids, m, polyhedron_id);

    for (int j = 0; j < face_number; j++)
    {
      int is_same = 0;
      for (int k = 0; k < *curr_face_id; k++)
      {
        if (face_ids[j] == face_ids_used[k])
        {
          is_same = 1;
          break;
        }
      }
      if (is_same)
      {
        continue;
      }
      face_ids_used[(*curr_face_id)++] = face_ids[j];
    }

    free(face_ids);
  }

  free(vpore_diffs);
}

void get_special_fpore_volume(double *fpore_volume, double random_fpore_i, int fpore_size, int scale, double **fpore)
{
  for (int j = 0; j < fpore_size; j++)
  {
    if (random_fpore_i == fpore[1][j])
    {
      *fpore_volume = fpore[0][j];
    }
    else if (random_fpore_i > fpore[1][j])
    {
      continue;
    }
    else if (random_fpore_i < fpore[1][j])
    {
      double last_volume = fpore[0][0];
      double last_rate = 1.0 / scale;
      if (j != 0)
      {
        last_volume = fpore[0][j - 1];
        last_rate = fpore[1][j - 1];
      }
      else
      {
        continue;
      }

      *fpore_volume = ((random_fpore_i - last_rate) / (fpore[1][j] - last_rate)) * (fpore[0][j] - last_volume) + last_volume;
      // fpore_volume=last_volume;
      break;
    }
  }
}

void get_special_fpore_face(int *select_face_id, int *face_ids_used, int *curr_face_id, const mesh *m, double fpore_volume, double **fpore, double *stface_data)
{
  double upper_limit = (M_PI / 4) * pow((20 * fpore_volume / M_PI), 2 / 3.0);
  double lower_limit = (M_PI / 4) * pow((5 * fpore_volume / M_PI), 2 / 3.0);

  // #ifdef ENABLE_LOG
  //   fprintf(log_out, "fpore_volume : %lf , fpore_rate : %lf ,", fpore_volume, random_fpore_i);
  //   fprintf(log_out, "upper_limit : %lf,lower_limit : %lf\n", upper_limit, lower_limit);
  // #endif

  // if (min_lower_limit == 0.0 || lower_limit < min_lower_limit)
  //   min_lower_limit = lower_limit;

  // if (max_upper_limit == 0.0 || upper_limit > max_upper_limit)
  //   max_upper_limit = upper_limit;

  *select_face_id = -1;
  int rand_count = 0;
  for (int j = 0;;)
  {
    rand_count++;
    if (j >= m->cn[2])
    {
      *select_face_id = -1;
      break;
    }
    else if (rand_count > 400)
    {
      j++;
    }
    else if (rand_count == 400)
    {
      j = 0;
    }
    else
    {
      j = rand() % m->cn[2];
    }

    int is_same = 0;
    for (int k = 0; k < *curr_face_id; k++)
    {
      if (j == face_ids_used[k])
      {
        if (*curr_face_id < m->cn[2])
          is_same = 1;
        break;
      }
    }

    if (is_same || stface_data[j] < lower_limit || stface_data[j] > upper_limit)
    {
      *select_face_id = -1;
      continue;
    }

    *select_face_id = j;
    face_ids_used[(*curr_face_id)++] = j;
    rand_count = 0;
    break;
  }
}

void traverse_fpore_volume_and_calculate(double *thickness, double *thickness_edge, double *fpore_used, double *fpore_volume_used, int *fpore_used_sum, int *face_ids_used, int *curr_face_id, const mesh *m, double **fpore, int fpore_size, double *stface_data, double a, double b, double module_volumes, FILE *log_out)
{
  double volumes = 0.0;
  srand(time(NULL));

  *fpore_used_sum = 0;
  double c = 0;

  for (; c + b < a;)
  {
    int scale = 1 / ((1 - 0.3) / (fpore_size + 0.4));
    double random_fpore_i = (rand() % scale) / (scale * 1.0);
    double fpore_volume = 0.0;

    if (random_fpore_i >= 1)
    {
      continue;
    }

    get_special_fpore_volume(&fpore_volume, random_fpore_i, fpore_size, scale, fpore);

    int is_same_fpore = 0;

    for (int j = 0; j < *fpore_used_sum; j++)
    {
      if (random_fpore_i == fpore_used[j])
      {
        is_same_fpore = 1;
        break;
      }
    }
    if (is_same_fpore)
      continue;

    int select_face_id;

    get_special_fpore_face(&select_face_id, face_ids_used, curr_face_id, m, fpore_volume, fpore, stface_data);

    if (select_face_id == -1)
      continue;

    volumes += fpore_volume;

    if (select_face_id < m->cn[2])
    {
      double value = fpore_volume / stface_data[select_face_id];
      if (thickness[select_face_id] == 0 || value > thickness[select_face_id])
      {
        thickness[select_face_id] = value;
      }

      int edge_number = face_get_edge_number_by_id(m, select_face_id);
      int *edge_ids = (int *)malloc(sizeof(int) * edge_number);
      face_get_edge_ids_by_face_id(edge_ids, m, select_face_id);

      for (int j = 0; j < edge_number; j++)
      {
        if (thickness_edge[edge_ids[j]] == 0 || thickness_edge[edge_ids[j]] < thickness[select_face_id])
          thickness_edge[edge_ids[j]] = thickness[select_face_id];
      }

      free(edge_ids);

      c = volumes / module_volumes;
      fpore_used[*fpore_used_sum] = random_fpore_i;
      fpore_volume_used[(*fpore_used_sum)++] = fpore_volume;
    }
  }

#ifdef ENABLE_LOG
  fprintf(log_out, "vpore_fpore_use_face_ids : ");
  int_array_file_print(log_out, *curr_face_id, face_ids_used, "--raw");

  // fprintf(log_out, "max_upper_limit : %lf, min_lower_limit : %lf\n", max_upper_limit, min_lower_limit);
  fprintf(log_out, "go through %d 个fpore\n", *fpore_used_sum);
  fprintf(log_out, "c=%lf\n", c);
#endif
}

void replace_thickness_edge_by_thickness(double *thickness_edge, int *face_total_edges, const mesh *m, double *thickness)
{
  *face_total_edges = 0;
  for (int i = 0; i < m->cn[2]; i++)
  {
    int edge_number = face_get_edge_number_by_id(m, i);
    int *edge_ids = (int *)malloc(sizeof(int) * edge_number);
    face_get_edge_ids_by_face_id(edge_ids, m, i);

    for (int j = 0; j < edge_number; j++)
    {
      if (thickness_edge[edge_ids[j]] == 0 || thickness_edge[edge_ids[j]] < thickness[i])
        thickness_edge[edge_ids[j]] = thickness[i];
    }
    *face_total_edges += edge_number;

    free(edge_ids);
  }
}

void get_total_edge_number(int *face_total_edges, const mesh *m)
{
  *face_total_edges = 0;
  for (int i = 0; i < m->cn[2]; i++)
  {
    int edge_number = face_get_edge_number_by_id(m, i);

    *face_total_edges += edge_number;
  }
}

void calculate_thickness_by_vpore(double *thickness, const mesh *m, int vpore_size, int *polyhedron_ids)
{
  for (int i = 0; i < vpore_size; i++)
  {
    int polyhedron_id = polyhedron_ids[i];

    int face_number = polyhedron_get_face_number_by_id(m, polyhedron_id);
    int *face_ids = (int *)malloc(sizeof(int) * face_number);
    polyhedron_get_face_ids(face_ids, m, polyhedron_id);

    for (int k = 0; k < face_number; k++)
    {
      double value = polyhedron_to_face_distance_by_id(m, polyhedron_id, face_ids[k]);
      if (thickness[face_ids[k]] == 0 || value > thickness[face_ids[k]])
      {
        thickness[face_ids[k]] = value;
      }
    }

    free(face_ids);
  }
}

void calculate_thickness_edge_by_vpore(double *thickness_edge, const mesh *m, int vpore_size, int *polyhedron_ids)
{
  for (int i = 0; i < vpore_size; i++)
  {
    int polyhedron_id = polyhedron_ids[i];

    int edge_number = polyhedron_get_edge_number_by_id(m, polyhedron_id);
    int *edge_ids = (int *)malloc(sizeof(int) * edge_number);
    polyhedron_get_edge_ids(edge_ids, m, polyhedron_id);

    for (int k = 0; k < edge_number; k++)
    {
      double value = polyhedron_to_edge_distance_by_id(m, polyhedron_id, edge_ids[k]);
      if (thickness_edge[edge_ids[k]] == 0 || value > thickness_edge[edge_ids[k]])
      {
        thickness_edge[edge_ids[k]] = value;
      }
    }

    free(edge_ids);
  }
}

void calculate_kappa1(double *kappa1, const mesh *m, double *thickness_edge)
{
  for (int i = 0; i < m->cn[1]; i++)
  {
    if (thickness_edge[i] != 0)
    {

      kappa1[2 * i - 1] = pow(thickness_edge[i] / 2, 2) / (8 * pow(10, -3));
      kappa1[2 * i] = pow(thickness_edge[i] / 2, 2) / (8 * pow(10, -3));
    }
    else
    {
      kappa1[2 * i - 1] = 1e-10;
      kappa1[2 * i] = 1e-10;
    }
  }
}

void calculate_kappa2(double *kappa2, int *kappa2_n, const mesh *m, double *thickness, int face_total_edges)
{
  int kappa2_index = 0;
  *kappa2_n = 0;
  for (int i = 0; i < m->cn[2]; i++)
  {
    int edge_number = face_get_edge_number_by_id(m, i);

    *kappa2_n += edge_number;

    for (int j = kappa2_index; j < *kappa2_n; j++)
    {
      kappa2[j] = pow(thickness[i], 2) / (12 * pow(10, -3));
    }

    kappa2_index += edge_number;
  }
}

void calculate_kappa3(double *kappa3, int *kappa3_n, const mesh *m, double *stface_data, int vpore_size, int *polyhedron_ids)
{
  int kappa3_index = 0;
  *kappa3_n = 0;

  for (int i = 0; i < m->cn[3]; i++)
  {
    int face_number = polyhedron_get_face_number_by_id(m, i);
    *kappa3_n += face_number;

    /* check whether selected */
    int is_found = 0;
    for (int j = 0; j < vpore_size; j++)
    {
      if (i == polyhedron_ids[j])
      {
        is_found = 1;
        break;
      }
    }

    /* if not selected */
    if (!is_found)
    {
      for (int k = kappa3_index; k < *kappa3_n; k++)
      {
        kappa3[k] = 1e-10;
      }
      kappa3_index += face_number;
      continue;
    }

    int *face_ids = (int *)malloc(sizeof(int) * face_number);
    polyhedron_get_face_ids(face_ids, m, i);
    /* if selected */
    for (int k = kappa3_index; k < *kappa3_n; k++)
    {
      kappa3[k] = (stface_data[face_ids[k - kappa3_index]] / M_PI) / (8 * pow(10, -3));
    }
    kappa3_index += face_number;
    free(face_ids);
  }
}

void calculate_kappa(double *kappa, const mesh *m, double *kappa1, double *kappa2, double *kappa3, int edge_total_vertexs, int face_total_edges, int polyhedron_total_faces)
{
  int kappa_i = 0;
  for (int i = 0; i < edge_total_vertexs; i++)
  {
    if (kappa1[i] == 0.0)
    {
      kappa[kappa_i++] = 1e-10;
    }
    else
    {
      kappa[kappa_i++] = kappa1[i];
    }
  }

  for (int i = 0; i < face_total_edges; i++)
  {
    if (kappa2[i] == 0.0)
    {
      kappa[kappa_i++] = 1e-10;
    }
    else
    {
      kappa[kappa_i++] = kappa2[i];
    }
  }

  for (int i = 0; i < polyhedron_total_faces; i++)
  {
    if (kappa3[i] == 0.0)
    {
      kappa[kappa_i++] = 1e-10;
    }
    else
    {
      kappa[kappa_i++] = kappa3[i];
    }
  }
}