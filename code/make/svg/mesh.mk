.PHONY: svg_mesh svg_mesh_clean svg_mesh_distclean

build/$(MODE)/svg/mesh: | build/$(MODE)/svg
	mkdir -p $@

_svg_mesh :=\
  build/$(MODE)/svg/mesh/brick_2d_1_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/brick_2d_1_forman_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/brick_2d_2_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/brick_2d_2_forman_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/brick_2d_4_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/brick_2d_5_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/brick_2d_5_forman_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/brick_2d_10_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/brick_2d_10_forman_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/rectangle_20_15_brick_5_3_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/rectangle_20_15_brick_5_3_forman_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/parallelogram_20_15_degrees_45_grid_5_3_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/parallelogram_20_15_degrees_45_grid_5_3_forman_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/square_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/square_2_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/square_4_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/square_8_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/pentagon_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/pentagon_forman_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/two_triangles_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/two_triangles_forman_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/triangle_and_square_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/triangle_and_square_forman_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/2d_10_grains_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/2d_10_grains_forman_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/disk_polar_4_3_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/disk_polar_4_3_forman_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/disk_polar_18_10_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/disk_polar_18_10_forman_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/hemisphere_polar_4_3_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/hemisphere_polar_4_3_forman_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/hemisphere_polar_6_6_edge_skeleton.svg\
  build/$(MODE)/svg/mesh/hemisphere_polar_6_6_forman_edge_skeleton.svg\

build/$(MODE)/svg/mesh/brick_2d_1_edge_skeleton.svg:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/brick_2d_1_forman_edge_skeleton.svg:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/brick_2d_2_edge_skeleton.svg:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/brick_2d_2_forman_edge_skeleton.svg:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/brick_2d_4_edge_skeleton.svg:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_4.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/brick_2d_5_edge_skeleton.svg:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_5.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/brick_2d_5_forman_edge_skeleton.svg:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_5_forman.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/brick_2d_10_edge_skeleton.svg:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_10.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/brick_2d_10_forman_edge_skeleton.svg:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_10_forman.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/rectangle_20_15_brick_5_3_edge_skeleton.svg:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/rectangle_20_15_brick_5_3_forman_edge_skeleton.svg:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3_forman.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/parallelogram_20_15_degrees_45_grid_5_3_edge_skeleton.svg:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/parallelogram_20_15_degrees_45_grid_5_3.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $< \
  --mesh=$(word 2, $^)\
  --height=250\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/parallelogram_20_15_degrees_45_grid_5_3_forman_edge_skeleton.svg:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/parallelogram_20_15_degrees_45_grid_5_3_forman.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $< \
  --mesh=$(word 2, $^)\
  --height=250\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/square_edge_skeleton.svg:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_skeleton$(.EXE)\
  data/mesh/square.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/square_2_edge_skeleton.svg:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/square_2.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/square_4_edge_skeleton.svg:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/square_4.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/square_8_edge_skeleton.svg:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/square_8.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/pentagon_edge_skeleton.svg:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_skeleton$(.EXE)\
  data/mesh/pentagon.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/pentagon_forman_edge_skeleton.svg:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/pentagon_forman.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/two_triangles_edge_skeleton.svg:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_skeleton$(.EXE)\
  data/mesh/two_triangles.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/two_triangles_forman_edge_skeleton.svg:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/two_triangles_forman.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/triangle_and_square_edge_skeleton.svg:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_skeleton$(.EXE)\
  data/mesh/triangle_and_square.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/triangle_and_square_forman_edge_skeleton.svg:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/triangle_and_square_forman.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/2d_10_grains_edge_skeleton.svg:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_skeleton$(.EXE)\
  data/mesh/2d_10_grains.tess\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $< \
  --mesh-format=tess\
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/2d_10_grains_forman_edge_skeleton.svg:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/disk_polar_4_3_edge_skeleton.svg:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_4_3.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_skeleton_polar$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_skeleton_polar\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/disk_polar_4_3_forman_edge_skeleton.svg:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_4_3_forman.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_skeleton_polar_forman$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_skeleton_polar_forman\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/disk_polar_18_10_edge_skeleton.svg:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_18_10.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_skeleton_polar$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_skeleton_polar\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/disk_polar_18_10_forman_edge_skeleton.svg:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_18_10_forman.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_skeleton_polar_forman$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_skeleton_polar_forman\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/hemisphere_polar_4_3_edge_skeleton.svg:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/hemisphere_polar_4_3.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_skeleton_polar$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_skeleton_polar\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/hemisphere_polar_4_3_forman_edge_skeleton.svg:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/hemisphere_polar_4_3_forman.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_skeleton_polar_forman$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_skeleton_polar_forman\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/hemisphere_polar_6_6_edge_skeleton.svg:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_skeleton_polar$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_skeleton_polar\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_svg_animation\
  --output=$@

build/$(MODE)/svg/mesh/hemisphere_polar_6_6_forman_edge_skeleton.svg:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_skeleton$(.EXE)\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6_forman.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_skeleton_polar_forman$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_svg_animation$(.OBJ)\
  | build/$(MODE)/svg/mesh\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $< \
  --mesh=$(word 2, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_skeleton_polar_forman\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_svg_animation\
  --output=$@

svg_mesh: $(_svg_mesh)

svg_mesh_clean:
	-$(RM) $(_svg_mesh)

svg_mesh_distclean:
	-$(RM) -r build/$(MODE)/svg/mesh
