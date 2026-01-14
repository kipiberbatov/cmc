.PHONY: txt_mesh_tessfile1 txt_mesh_tessfile1_clean

_txt_mesh_tessfile1 :=\
  build/$(MODE)/txt/mesh/tessfile1.txt\
  build/$(MODE)/txt/mesh/tessfile1_kappa.txt\
  build/$(MODE)/txt/mesh/tessfile1_forman.txt\
  build/$(MODE)/txt/mesh/tessfile1_forman_cbd.txt\
  build/$(MODE)/txt/mesh/tessfile1_forman_vol.txt\
  build/$(MODE)/txt/mesh/tessfile1_forman_inner.txt\
  build/$(MODE)/txt/mesh/tessfile1_forman_cbd_star.txt\
  build/$(MODE)/txt/mesh/tessfile1_forman_hodge_coeff.txt\
  build/$(MODE)/txt/mesh/tessfile1_forman_hodge.txt\

build/$(MODE)/txt/mesh/tessfile1.txt:\
  build/$(MODE)/bin/mesh_and_boundary_file_scan$(.EXE)\
  data/mesh/tessfile1.tess\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< --mesh-format=tess $(word 2, $^) > $@

build/$(MODE)/txt/mesh/tessfile1_kappa.txt:\
  build/$(MODE)/bin/mesh_generate_3d_kappa$(.EXE)\
  build/$(MODE)/txt/mesh/tessfile1.txt\
  | build/$(MODE)/txt/mesh
	$< --raw $(word 2, $^) data/mesh 0.0651

build/$(MODE)/txt/mesh/tessfile1_forman.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/tessfile1.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< --raw $(word 2, $^) --standard --raw > $@

build/$(MODE)/txt/mesh/tessfile1_forman_cbd.txt:\
  build/$(MODE)/bin/mesh_coboundary$(.EXE)\
  build/$(MODE)/txt/mesh/tessfile1_forman.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< --raw < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/tessfile1_forman_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/tessfile1_forman.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/tessfile1_forman_inner.txt:\
  build/$(MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(MODE)/txt/mesh/tessfile1_forman.txt\
  build/$(MODE)/txt/mesh/tessfile1_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/tessfile1_forman_cbd_star.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/tessfile1_forman.txt\
  build/$(MODE)/txt/mesh/tessfile1_forman_inner.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/tessfile1_forman_hodge_coeff.txt:\
  build/$(MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(MODE)/txt/mesh/tessfile1_forman.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/tessfile1_forman_hodge.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/tessfile1_forman.txt\
  build/$(MODE)/txt/mesh/tessfile1_forman_inner.txt\
  build/$(MODE)/txt/mesh/tessfile1_forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

txt_mesh_tessfile1: $(_txt_mesh_tessfile1)

txt_mesh_tessfile1_clean:
	-$(RM) $(_txt_mesh_tessfile1)

