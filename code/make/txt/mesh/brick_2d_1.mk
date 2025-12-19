.PHONY: txt_mesh_brick_2d_1 txt_mesh_brick_2d_1_clean

_txt_mesh_brick_2d_1 := \
  build/$(MODE)/txt/mesh/brick_2d_1.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_vol.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_boundary.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_cbd.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_vol.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_metric.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_inner.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_cbd_star.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_laplacian.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_laplacian_matrix_form.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_coeff.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_matrix_form.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_codifferential.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_codifferential_matrix_form.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_laplacian.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_laplacian_matrix_form.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_node_curvature.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_metric_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_inner_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_cbd_star_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_laplacian_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_displacement.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_elasticity_cbd_star_1_1_1.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_elasticity_cbd_star_2_1_1.txt\
  # build/$(MODE)/txt/mesh/brick_2d_1_forman_elastcity_laplacian_1_1_1.txt\

build/$(MODE)/txt/mesh/brick_2d_1.txt:\
  build/$(MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< 2 1 > $@

build/$(MODE)/txt/mesh/brick_2d_1_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< --raw $(word 2, $^) --standard --raw > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_boundary.txt:\
  build/$(MODE)/bin/mesh_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< --raw < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_cbd.txt:\
  build/$(MODE)/bin/mesh_coboundary$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< --raw < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_metric.txt:\
  build/$(MODE)/bin/mesh_qc_metric$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_inner.txt:\
  build/$(MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_cbd_star.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_inner.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_laplacian.txt:\
  build/$(MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_cbd_star.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_laplacian_matrix_form.txt:\
  build/$(MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_laplacian.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< --matrix-form-curly -list 3 < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_coeff.txt:\
  build/$(MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_inner.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_matrix_form.txt:\
  build/$(MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< --matrix-form-curly -list 3 < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_codifferential.txt:\
  build/$(MODE)/bin/mesh_qc_hodge_codifferential$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_codifferential_matrix_form.txt:\
  build/$(MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_codifferential.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< --matrix-form-curly -list 2 < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_laplacian.txt:\
  build/$(MODE)/bin/matrix_sparse_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_cbd.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_codifferential.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< 2 --raw $(word 2, $^) --raw $(word 3, $^) --raw > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_laplacian_matrix_form.txt:\
  build/$(MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_laplacian.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< --matrix-form-curly -list 3 < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_node_curvature.txt:\
  build/$(MODE)/bin/mesh_node_curvature$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_metric_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_metric_corrected$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_vol.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_node_curvature.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_inner_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_inner$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_vol.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_metric_corrected.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_cbd_star_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_inner_corrected.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_laplacian_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_cbd_star_corrected.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_inner_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_displacement.txt:\
  build/$(MODE)/bin/mesh_displacement$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_elasticity_cbd_star_1_1_1.txt:\
  build/$(MODE)/bin/mesh_qc_elasticity_coboundary_star_1$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_inner_corrected.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< 1 1 $(wordlist 2, $(words $^), $^) > $@

build/$(MODE)/txt/mesh/brick_2d_1_forman_elasticity_cbd_star_2_1_1.txt:\
  build/$(MODE)/bin/mesh_qc_elasticity_coboundary_star_2$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_1_forman_inner_corrected.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< 1 $(wordlist 2, $(words $^), $^) > $@

# build/$(MODE)/txt/mesh/brick_2d_1_forman_elastcity_laplacian_1_1_1.txt:\
#   build/$(MODE)/bin/mesh_qc_laplacian$(.EXE)\
#   build/$(MODE)/txt/mesh/brick_2d_1_forman.txt\
#   build/$(MODE)/txt/mesh/brick_2d_1_forman_elasticity_cbd_star_1_1_1.txt\
#   build/$(MODE)/txt/mesh/brick_2d_1_forman_elasticity_cbd_star_2_1_1.txt\
  | build/$(MODE)/txt/mesh
#       $^ > $@

txt_mesh_brick_2d_1: $(_txt_mesh_brick_2d_1)

txt_mesh_brick_2d_1_clean:
	-$(RM) $(_txt_mesh_brick_2d_1)
