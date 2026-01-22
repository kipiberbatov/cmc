.PHONY: txt_mesh_two_triangles txt_mesh_two_triangles_clean

_txt_mesh_two_triangles := \
  build/$(MODE)/txt/mesh/two_triangles/vol.txt\
  build/$(MODE)/txt/mesh/two_triangles/forman.txt\
  build/$(MODE)/txt/mesh/two_triangles/forman_vol.txt\
  build/$(MODE)/txt/mesh/two_triangles/forman_metric.txt\
  build/$(MODE)/txt/mesh/two_triangles/forman_inner.txt\
  build/$(MODE)/txt/mesh/two_triangles/forman_cbd_star.txt\
  build/$(MODE)/txt/mesh/two_triangles/forman_laplacian.txt\
  build/$(MODE)/txt/mesh/two_triangles/forman_hodge_coeff.txt\
  build/$(MODE)/txt/mesh/two_triangles/forman_hodge.txt\
  build/$(MODE)/txt/mesh/two_triangles/forman_node_curvature.txt\
  build/$(MODE)/txt/mesh/two_triangles/forman_metric_corrected.txt\
  build/$(MODE)/txt/mesh/two_triangles/forman_inner_corrected.txt\
  build/$(MODE)/txt/mesh/two_triangles/forman_cbd_star_corrected.txt\
  build/$(MODE)/txt/mesh/two_triangles/forman_laplacian_corrected.txt\
  build/$(MODE)/txt/mesh/two_triangles/forman_laplacian_corrected_matrix_form.txt\
  build/$(MODE)/txt/mesh/two_triangles/forman_laplacian_corrected_symmetric.txt\
  build/$(MODE)/txt/mesh/two_triangles/forman_laplacian_corrected_symmetric_matrix_form.txt\
  build/$(MODE)/txt/mesh/two_triangles/forman_hodge_corrected.txt\
  build/$(MODE)/txt/mesh/two_triangles/forman_laplace_equation_non_grid.txt\

build/$(MODE)/txt/mesh/two_triangles: | build/$(MODE)/txt/mesh
	mkdir -p $@

build/$(MODE)/txt/mesh/two_triangles/vol.txt:\
  build/$(MODE)/bin/mesh_measure$(.EXE)\
  data/mesh/two_triangles.txt\
  | build/$(MODE)/txt/mesh/two_triangles
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/two_triangles/forman.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  data/mesh/two_triangles.txt\
  | build/$(MODE)/txt/mesh/two_triangles
	$(INTERPRETER) $< --raw $(word 2, $^) --standard --raw > $@

build/$(MODE)/txt/mesh/two_triangles/forman_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/two_triangles/forman.txt\
  | build/$(MODE)/txt/mesh/two_triangles
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/two_triangles/forman_metric.txt:\
  build/$(MODE)/bin/mesh_qc_metric$(.EXE)\
  build/$(MODE)/txt/mesh/two_triangles/forman.txt\
  build/$(MODE)/txt/mesh/two_triangles/forman_vol.txt\
  | build/$(MODE)/txt/mesh/two_triangles
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/two_triangles/forman_inner.txt:\
  build/$(MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(MODE)/txt/mesh/two_triangles/forman.txt\
  build/$(MODE)/txt/mesh/two_triangles/forman_vol.txt\
  | build/$(MODE)/txt/mesh/two_triangles
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/two_triangles/forman_cbd_star.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/two_triangles/forman.txt\
  build/$(MODE)/txt/mesh/two_triangles/forman_inner.txt\
  | build/$(MODE)/txt/mesh/two_triangles
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/two_triangles/forman_laplacian.txt:\
  build/$(MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/two_triangles/forman.txt\
  build/$(MODE)/txt/mesh/two_triangles/forman_cbd_star.txt\
  | build/$(MODE)/txt/mesh/two_triangles
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/two_triangles/forman_hodge_coeff.txt:\
  build/$(MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(MODE)/txt/mesh/two_triangles/forman.txt\
  | build/$(MODE)/txt/mesh/two_triangles
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/two_triangles/forman_hodge.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/two_triangles/forman.txt\
  build/$(MODE)/txt/mesh/two_triangles/forman_inner.txt\
  build/$(MODE)/txt/mesh/two_triangles/forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh/two_triangles
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/two_triangles/forman_node_curvature.txt:\
  build/$(MODE)/bin/mesh_node_curvature$(.EXE)\
  build/$(MODE)/txt/mesh/two_triangles/forman.txt\
  | build/$(MODE)/txt/mesh/two_triangles
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/two_triangles/forman_metric_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_metric_corrected$(.EXE)\
  build/$(MODE)/txt/mesh/two_triangles/forman.txt\
  build/$(MODE)/txt/mesh/two_triangles/forman_vol.txt\
  build/$(MODE)/txt/mesh/two_triangles/forman_node_curvature.txt\
  | build/$(MODE)/txt/mesh/two_triangles
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/two_triangles/forman_inner_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_inner$(.EXE)\
  build/$(MODE)/txt/mesh/two_triangles/forman.txt\
  build/$(MODE)/txt/mesh/two_triangles/forman_vol.txt\
  build/$(MODE)/txt/mesh/two_triangles/forman_metric_corrected.txt\
  | build/$(MODE)/txt/mesh/two_triangles
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/two_triangles/forman_cbd_star_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/two_triangles/forman.txt\
  build/$(MODE)/txt/mesh/two_triangles/forman_inner_corrected.txt\
  | build/$(MODE)/txt/mesh/two_triangles
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/two_triangles/forman_laplacian_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/two_triangles/forman.txt\
  build/$(MODE)/txt/mesh/two_triangles/forman_cbd_star_corrected.txt\
  | build/$(MODE)/txt/mesh/two_triangles
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/two_triangles/forman_laplacian_corrected_matrix_form.txt:\
  build/$(MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(MODE)/txt/mesh/two_triangles/forman_laplacian_corrected.txt\
  | build/$(MODE)/txt/mesh/two_triangles
	$(INTERPRETER) $< --matrix-form-curly -list 3 < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/two_triangles/forman_laplacian_corrected_symmetric.txt:\
  build/$(MODE)/bin/matrix_sparse_laplacian_symmetric$(.EXE)\
  build/$(MODE)/txt/mesh/two_triangles/forman_laplacian_corrected.txt\
  build/$(MODE)/txt/mesh/two_triangles/forman_inner_corrected.txt\
  | build/$(MODE)/txt/mesh/two_triangles
	$(INTERPRETER) $< 2 $(word 2, $^) --raw $(word 3, $^) --raw --raw > $@

build/$(MODE)/txt/mesh/two_triangles/forman_laplacian_corrected_symmetric_matrix_form.txt:\
  build/$(MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(MODE)/txt/mesh/two_triangles/forman_laplacian_corrected_symmetric.txt\
  | build/$(MODE)/txt/mesh/two_triangles
	$(INTERPRETER) $< --matrix-form-curly -list 3 < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/two_triangles/forman_hodge_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/two_triangles/forman.txt\
  build/$(MODE)/txt/mesh/two_triangles/forman_inner_corrected.txt\
  build/$(MODE)/txt/mesh/two_triangles/forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh/two_triangles
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/two_triangles/forman_laplace_equation_non_grid.txt:\
  build/$(MODE)/bin/mesh_qc_laplace_equation_solve_non_grid$(.EXE)\
  build/$(MODE)/txt/mesh/two_triangles/forman.txt\
  build/$(MODE)/txt/mesh/two_triangles/forman_laplacian_corrected_symmetric.txt\
  build/$(MODE)/txt/mesh/two_triangles/forman_inner_corrected.txt\
  | build/$(MODE)/txt/mesh/two_triangles
	$(INTERPRETER) $< $(word 2, $^) --raw $(word 3, $^) --raw $(word 4, $^) --raw\
	> $@ --raw

txt_mesh_two_triangles: $(_txt_mesh_two_triangles)

txt_mesh_two_triangles_clean:
	-$(RM) $(_txt_mesh_two_triangles)

txt_mesh_two_triangles_distclean:
	-$(RM) -r build/$(MODE)/txt/mesh/two_triangles
