.PHONY: txt_mesh_brick_2d_10 txt_mesh_brick_2d_10_clean

_txt_mesh_brick_2d_10 := \
  build/$(MODE)/txt/mesh/brick_2d_10/data.txt\
  build/$(MODE)/txt/mesh/brick_2d_10/vol.txt\
  build/$(MODE)/txt/mesh/brick_2d_10/forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_10/forman_cbd.txt\
  build/$(MODE)/txt/mesh/brick_2d_10/forman_vol.txt\
  build/$(MODE)/txt/mesh/brick_2d_10/forman_metric.txt\
  build/$(MODE)/txt/mesh/brick_2d_10/forman_inner.txt\
  build/$(MODE)/txt/mesh/brick_2d_10/forman_cbd_star.txt\
  build/$(MODE)/txt/mesh/brick_2d_10/forman_laplacian.txt\
  build/$(MODE)/txt/mesh/brick_2d_10/forman_hodge_coeff.txt\
  build/$(MODE)/txt/mesh/brick_2d_10/forman_hodge.txt\
  build/$(MODE)/txt/mesh/brick_2d_10/forman_node_curvature.txt\
  build/$(MODE)/txt/mesh/brick_2d_10/forman_metric_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_10/forman_inner_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_10/forman_cbd_star_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_10/forman_laplacian_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_10/forman_hodge_corrected.txt\

build/$(MODE)/txt/mesh/brick_2d_10: | build/$(MODE)/txt/mesh
	mkdir -p $@

build/$(MODE)/txt/mesh/brick_2d_10/data.txt:\
  build/$(MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(MODE)/txt/mesh/brick_2d_10
	$(INTERPRETER) $< 2 10 > $@

build/$(MODE)/txt/mesh/brick_2d_10/vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_10/data.txt\
  | build/$(MODE)/txt/mesh/brick_2d_10
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_10/forman.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_10/data.txt\
  | build/$(MODE)/txt/mesh/brick_2d_10
	$(INTERPRETER) $< --raw $(word 2, $^) --standard --raw > $@

build/$(MODE)/txt/mesh/brick_2d_10/forman_cbd.txt:\
  build/$(MODE)/bin/mesh_coboundary$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_10/forman.txt\
  | build/$(MODE)/txt/mesh/brick_2d_10
	$(INTERPRETER) $< --raw < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_10/forman_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_10/forman.txt\
  | build/$(MODE)/txt/mesh/brick_2d_10
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_10/forman_metric.txt:\
  build/$(MODE)/bin/mesh_qc_metric$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_10/forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_10/forman_vol.txt\
  | build/$(MODE)/txt/mesh/brick_2d_10
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/brick_2d_10/forman_inner.txt:\
  build/$(MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_10/forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_10/forman_vol.txt\
  | build/$(MODE)/txt/mesh/brick_2d_10
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/brick_2d_10/forman_cbd_star.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_10/forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_10/forman_inner.txt\
  | build/$(MODE)/txt/mesh/brick_2d_10
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/brick_2d_10/forman_laplacian.txt:\
  build/$(MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_10/forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_10/forman_cbd_star.txt\
  | build/$(MODE)/txt/mesh/brick_2d_10
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/brick_2d_10/forman_hodge_coeff.txt:\
  build/$(MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_10/forman.txt\
  | build/$(MODE)/txt/mesh/brick_2d_10
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_10/forman_hodge.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_10/forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_10/forman_inner.txt\
  build/$(MODE)/txt/mesh/brick_2d_10/forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh/brick_2d_10
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/brick_2d_10/forman_node_curvature.txt:\
  build/$(MODE)/bin/mesh_node_curvature$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_10/forman.txt\
  | build/$(MODE)/txt/mesh/brick_2d_10
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_10/forman_metric_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_metric_corrected$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_10/forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_10/forman_vol.txt\
  build/$(MODE)/txt/mesh/brick_2d_10/forman_node_curvature.txt\
  | build/$(MODE)/txt/mesh/brick_2d_10
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/brick_2d_10/forman_inner_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_inner$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_10/forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_10/forman_vol.txt\
  build/$(MODE)/txt/mesh/brick_2d_10/forman_metric_corrected.txt\
  | build/$(MODE)/txt/mesh/brick_2d_10
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/brick_2d_10/forman_cbd_star_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_10/forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_10/forman_inner_corrected.txt\
  | build/$(MODE)/txt/mesh/brick_2d_10
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/brick_2d_10/forman_laplacian_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_10/forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_10/forman_cbd_star_corrected.txt\
  | build/$(MODE)/txt/mesh/brick_2d_10
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/brick_2d_10/forman_hodge_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_10/forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_10/forman_inner_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_10/forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh/brick_2d_10
	$(INTERPRETER) $^ > $@

txt_mesh_brick_2d_10: $(_txt_mesh_brick_2d_10)

txt_mesh_brick_2d_10_clean:
	-$(RM) $(_txt_mesh_brick_2d_10)

txt_mesh_brick_2d_10_distclean:
	-$(RM) -r build/$(MODE)/txt/mesh/brick_2d_10
