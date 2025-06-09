#ifndef _cmc_graphics_mesh_2d_1_cochain_sequence_h
#define _cmc_graphics_mesh_2d_1_cochain_sequence_h

struct mesh;

/* used in conjunction with cmc_animation_generic_data */
struct cmc_graphics_mesh_2d_1_cochain_sequence
{
  struct mesh * m;
  double * values;
  double * coordinates;
  double * boundary_1;
  double line_width;
  double min_value;
  double max_value;
};

struct cmc_graphics_mesh_2d_1_cochain_sequence_draw_functions;

void cmc_graphics_mesh_2d_1_cochain_sequence_draw_values(
  void * canvas,
  int * status,
  const struct cmc_graphics_mesh_2d_1_cochain_sequence * cochain_sequence,
  const struct cmc_graphics_mesh_2d_1_cochain_sequence_draw_functions *
    functions,
  int i,
  int total_colors);

void cmc_graphics_mesh_2d_1_cochain_sequence_draw_values_polar_forman(
  void * canvas,
  int * status,
  const struct cmc_graphics_mesh_2d_1_cochain_sequence * cochain_sequence,
  const struct cmc_graphics_mesh_2d_1_cochain_sequence_draw_functions *
    functions,
  int i,
  int total_colors);

void cmc_graphics_mesh_2d_1_cochain_sequence_draw_values_diks_polar_forman(
  void * canvas,
  int * status,
  const struct cmc_graphics_mesh_2d_1_cochain_sequence * cochain_sequence,
  const struct cmc_graphics_mesh_2d_1_cochain_sequence_draw_functions *
    functions,
  int i,
  int total_colors);

struct cmc_animation;

void cmc_graphics_mesh_2d_1_cochain_sequence_draw_snapshot(
  void * canvas,
  int * status,
  const struct cmc_animation * animation);

#endif /* _cmc_graphics_mesh_2d_1_cochain_sequence_h */
