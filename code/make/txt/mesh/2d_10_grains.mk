.PHONY: txt_mesh_2d_10_grains txt_mesh_2d_10_grains_clean

_txt_mesh_2d_10_grains :=\
  build/$(MODE)/txt/mesh/2d_10_grains.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_cbd.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_vol.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_inner.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_cbd_star.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_hodge_coeff.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_hodge.txt\

build/$(MODE)/txt/mesh/2d_10_grains.txt:\
  build/$(MODE)/bin/mesh_and_boundary_file_scan$(.EXE)\
  data/mesh/2d_10_grains.tess\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< --mesh-format=tess $(word 2, $^) > $@

build/$(MODE)/txt/mesh/2d_10_grains_forman.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< --raw $(word 2, $^) --standard --raw > $@

build/$(MODE)/txt/mesh/2d_10_grains_forman_cbd.txt:\
  build/$(MODE)/bin/mesh_coboundary$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< --raw < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/2d_10_grains_forman_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/2d_10_grains_forman_inner.txt:\
  build/$(MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/2d_10_grains_forman_cbd_star.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_inner.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/2d_10_grains_forman_hodge_coeff.txt:\
  build/$(MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/2d_10_grains_forman_hodge.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_inner.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

txt_mesh_2d_10_grains: $(_txt_mesh_2d_10_grains)

txt_mesh_2d_10_grains_clean:
	-$(RM) $(_txt_mesh_2d_10_grains)
