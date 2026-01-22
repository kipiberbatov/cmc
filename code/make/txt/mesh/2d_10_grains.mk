.PHONY: txt_mesh_2d_10_grains txt_mesh_2d_10_grains_clean

_txt_mesh_2d_10_grains :=\
  build/$(MODE)/txt/mesh/2d_10_grains/data.txt\
  build/$(MODE)/txt/mesh/2d_10_grains/forman.txt\
  build/$(MODE)/txt/mesh/2d_10_grains/forman_cbd.txt\
  build/$(MODE)/txt/mesh/2d_10_grains/forman_vol.txt\
  build/$(MODE)/txt/mesh/2d_10_grains/forman_inner.txt\
  build/$(MODE)/txt/mesh/2d_10_grains/forman_cbd_star.txt\
  build/$(MODE)/txt/mesh/2d_10_grains/forman_hodge_coeff.txt\
  build/$(MODE)/txt/mesh/2d_10_grains/forman_hodge.txt\

build/$(MODE)/txt/mesh/2d_10_grains: | build/$(MODE)/txt/mesh
	mkdir -p $@

build/$(MODE)/txt/mesh/2d_10_grains/data.txt:\
  build/$(MODE)/bin/mesh_and_boundary_file_scan$(.EXE)\
  data/mesh/2d_10_grains.tess\
  | build/$(MODE)/txt/mesh/2d_10_grains
	$(INTERPRETER) $< --mesh-format=tess $(word 2, $^) > $@

build/$(MODE)/txt/mesh/2d_10_grains/forman.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains/data.txt\
  | build/$(MODE)/txt/mesh/2d_10_grains
	$(INTERPRETER) $< --raw $(word 2, $^) --standard --raw > $@

build/$(MODE)/txt/mesh/2d_10_grains/forman_cbd.txt:\
  build/$(MODE)/bin/mesh_coboundary$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains/forman.txt\
  | build/$(MODE)/txt/mesh/2d_10_grains
	$(INTERPRETER) $< --raw < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/2d_10_grains/forman_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains/forman.txt\
  | build/$(MODE)/txt/mesh/2d_10_grains
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/2d_10_grains/forman_inner.txt:\
  build/$(MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains/forman.txt\
  build/$(MODE)/txt/mesh/2d_10_grains/forman_vol.txt\
  | build/$(MODE)/txt/mesh/2d_10_grains
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/2d_10_grains/forman_cbd_star.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains/forman.txt\
  build/$(MODE)/txt/mesh/2d_10_grains/forman_inner.txt\
  | build/$(MODE)/txt/mesh/2d_10_grains
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/2d_10_grains/forman_hodge_coeff.txt:\
  build/$(MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains/forman.txt\
  | build/$(MODE)/txt/mesh/2d_10_grains
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/2d_10_grains/forman_hodge.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains/forman.txt\
  build/$(MODE)/txt/mesh/2d_10_grains/forman_inner.txt\
  build/$(MODE)/txt/mesh/2d_10_grains/forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh/2d_10_grains
	$(INTERPRETER) $^ > $@

txt_mesh_2d_10_grains: $(_txt_mesh_2d_10_grains)

txt_mesh_2d_10_grains_clean:
	-$(RM) $(_txt_mesh_2d_10_grains)

txt_mesh_2d_10_grains_distclean:
	-$(RM) -r build/$(MODE)/txt/mesh/2d_10_grains
