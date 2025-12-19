.PHONY: txt_mesh_triangle_and_square txt_mesh_triangle_and_square_clean

_txt_mesh_triangle_and_square := \
  build/$(MODE)/txt/mesh/triangle_and_square_vol.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_vol.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_metric.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_inner.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_cbd_star.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_laplacian.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_hodge_coeff.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_hodge.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_node_curvature.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_metric_corrected.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_inner_corrected.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_cbd_star_corrected.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_laplacian_corrected.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_hodge_corrected.txt\

build/$(MODE)/txt/mesh/triangle_and_square_vol.txt:\
  build/$(MODE)/bin/mesh_measure$(.EXE)\
  data/mesh/triangle_and_square.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/triangle_and_square_forman.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  data/mesh/triangle_and_square.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< --raw $(word 2, $^) --standard --raw > $@

build/$(MODE)/txt/mesh/triangle_and_square_forman_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/triangle_and_square_forman.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/triangle_and_square_forman_metric.txt:\
  build/$(MODE)/bin/mesh_qc_metric$(.EXE)\
  build/$(MODE)/txt/mesh/triangle_and_square_forman.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/triangle_and_square_forman_inner.txt:\
  build/$(MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(MODE)/txt/mesh/triangle_and_square_forman.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/triangle_and_square_forman_cbd_star.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/triangle_and_square_forman.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_inner.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/triangle_and_square_forman_laplacian.txt:\
  build/$(MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/triangle_and_square_forman.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_cbd_star.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/triangle_and_square_forman_hodge_coeff.txt:\
  build/$(MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(MODE)/txt/mesh/triangle_and_square_forman.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/triangle_and_square_forman_hodge.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/triangle_and_square_forman.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_inner.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/triangle_and_square_forman_node_curvature.txt:\
  build/$(MODE)/bin/mesh_node_curvature$(.EXE)\
  build/$(MODE)/txt/mesh/triangle_and_square_forman.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/triangle_and_square_forman_metric_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_metric_corrected$(.EXE)\
  build/$(MODE)/txt/mesh/triangle_and_square_forman.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_vol.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_node_curvature.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/triangle_and_square_forman_inner_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_inner$(.EXE)\
  build/$(MODE)/txt/mesh/triangle_and_square_forman.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_vol.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_metric_corrected.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/triangle_and_square_forman_cbd_star_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/triangle_and_square_forman.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_inner_corrected.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/triangle_and_square_forman_laplacian_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/triangle_and_square_forman.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_cbd_star_corrected.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/triangle_and_square_forman_hodge_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/triangle_and_square_forman.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_inner_corrected.txt\
  build/$(MODE)/txt/mesh/triangle_and_square_forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

txt_mesh_triangle_and_square: $(_txt_mesh_triangle_and_square)

txt_mesh_triangle_and_square_clean:
	-$(RM) $(_txt_mesh_triangle_and_square)
