.PHONY: txt_mesh_brick_2d_2 txt_mesh_brick_2d_2_clean

_txt_mesh_brick_2d_2 := \
  build/$(MODE)/txt/mesh/brick_2d_2.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_vol.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_boundary_hyperfaces.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_0_cells.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_nodes_dirichlet.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_nodes_neumann.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_nodes_neumann_normals.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_nodes_neumann_neighbors.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_nodes_neumann_vector_matrices.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_nodes_neumann_coefficients.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_boundary.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_cbd.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_vol.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_metric.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_inner.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_cbd_star.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_laplacian.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_neumann_modified_laplacian.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge_coeff.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_node_curvature.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_metric_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_inner_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_cbd_star_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_laplacian_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_laplacian_corrected_matrix_form.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge_corrected_matrix_form.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge_codifferential_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge_codifferential_corrected_matrix_form.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge_laplacian_corrected.txt\

build/$(MODE)/txt/mesh/brick_2d_2.txt:\
  build/$(MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< 2 2 > $@

build/$(MODE)/txt/mesh/brick_2d_2_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< --raw $(word 2, $^) --standard --raw > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_boundary_hyperfaces.txt:\
  build/$(MODE)/bin/mesh_boundary_hyperfaces$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_0_cells.txt:\
  build/$(MODE)/bin/mesh_boundary_lower_subfaces$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_nodes_dirichlet.txt:\
  build/$(MODE)/bin/mesh_boundary_nodes_from_constraint_dirichlet$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_nodes_neumann.txt:\
  build/$(MODE)/bin/mesh_boundary_nodes_from_constraint_neumann$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_nodes_neumann_normals.txt:\
  build/$(MODE)/bin/mesh_boundary_node_normal$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_nodes_neumann_neighbors.txt:\
  build/$(MODE)/bin/mesh_neighboring_nodes$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_nodes_neumann_vector_matrices.txt:\
  build/$(MODE)/bin/mesh_boundary_node_vectors_matrix$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_nodes_neumann_coefficients.txt:\
  build/$(MODE)/bin/mesh_boundary_neumann_coefficients$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_boundary.txt:\
  build/$(MODE)/bin/mesh_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< --raw < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_cbd.txt:\
  build/$(MODE)/bin/mesh_coboundary$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< --raw < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_metric.txt:\
  build/$(MODE)/bin/mesh_qc_metric$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_inner.txt:\
  build/$(MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_cbd_star.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_inner.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_laplacian.txt:\
  build/$(MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_cbd_star.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_neumann_modified_laplacian.txt:\
  build/$(MODE)/bin/mesh_qc_set_neumann_rows$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_laplacian.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< --raw $(word 2, $^) --raw $(word 3, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge_coeff.txt:\
  build/$(MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_inner.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_node_curvature.txt:\
  build/$(MODE)/bin/mesh_node_curvature$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_metric_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_metric_corrected$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_vol.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_node_curvature.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_inner_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_inner$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_vol.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_metric_corrected.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_cbd_star_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_inner_corrected.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_laplacian_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_cbd_star_corrected.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_laplacian_corrected_matrix_form.txt:\
  build/$(MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_laplacian_corrected.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< --matrix-form-curly -list 3 < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_inner_corrected.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge_corrected_matrix_form.txt:\
  build/$(MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge_corrected.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< --matrix-form-curly -list 3 < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge_codifferential_corrected.txt:\
  build/$(MODE)/bin/mesh_qc_hodge_codifferential$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge_corrected.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge_codifferential_corrected_matrix_form.txt:\
  build/$(MODE)/bin/matrix_sparse_file_print$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge_codifferential_corrected.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< --matrix-form-curly -list 2 < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge_laplacian_corrected.txt:\
  build/$(MODE)/bin/matrix_sparse_laplacian$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_cbd.txt\
  build/$(MODE)/txt/mesh/brick_2d_2_forman_hodge_codifferential_corrected.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< 2 --raw $(word 2, $^) --raw $(word 3, $^) --raw > $@

txt_mesh_brick_2d_2: $(_txt_mesh_brick_2d_2)

txt_mesh_brick_2d_2_clean:
	-$(RM) $(_txt_mesh_brick_2d_2)
