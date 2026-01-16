.PHONY: txt_mesh_sandstone_3062_grains txt_mesh_sandstone_3062_grains_clean

_txt_mesh_sandstone_3062_grains :=\
  build/$(MODE)/txt/mesh/sandstone_3062_grains.txt\
  build/$(MODE)/txt/mesh/sandstone_3062_grains_kappa.txt\
  build/$(MODE)/txt/mesh/sandstone_3062_grains_forman.txt\
  build/$(MODE)/txt/mesh/sandstone_3062_grains_forman_cbd.txt\
  build/$(MODE)/txt/mesh/sandstone_3062_grains_forman_vol.txt\
  # build/$(MODE)/txt/mesh/sandstone_3062_grains_forman_inner.txt\
  # build/$(MODE)/txt/mesh/sandstone_3062_grains_forman_cbd_star.txt\
  # build/$(MODE)/txt/mesh/sandstone_3062_grains_forman_hodge_coeff.txt\
  # build/$(MODE)/txt/mesh/sandstone_3062_grains_forman_hodge.txt\

assets/mesh/sandstone_3062_grains.tess: | assets/mesh
	curl https://zenodo.org/records/18248963/files/sandstone_3062_grains.tess > $@

assets/mesh/sandstone_3062_grains.stface: | assets/mesh
	curl https://zenodo.org/records/18248963/files/sandstone_3062_grains.stface > $@

assets/mesh/sandstone_3062_grains.stcell: | assets/mesh
	curl https://zenodo.org/records/18248963/files/sandstone_3062_grains.stcell > $@

assets/mesh/sandstone_3062_grains_vpore.csv: | assets/mesh
	curl https://zenodo.org/records/18248963/files/sandstone_3062_grains_vpore.csv > $@

assets/mesh/sandstone_3062_grains_fpore.csv: | assets/mesh
	curl https://zenodo.org/records/18248963/files/sandstone_3062_grains_fpore.csv > $@

assets/mesh: | assets
	mkdir -p $@

assets:
	mkdir -p $@

build/$(MODE)/txt/mesh/sandstone_3062_grains.txt:\
  build/$(MODE)/bin/mesh_and_boundary_file_scan$(.EXE)\
  assets/mesh/sandstone_3062_grains.tess\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< --mesh-format=tess $(word 2, $^) > $@

build/$(MODE)/txt/mesh/sandstone_3062_grains_kappa.txt:\
  build/$(MODE)/bin/mesh_generate_3d_kappa$(.EXE)\
  build/$(MODE)/txt/mesh/sandstone_3062_grains.txt\
  assets/mesh/sandstone_3062_grains.stface\
  assets/mesh/sandstone_3062_grains.stcell\
  assets/mesh/sandstone_3062_grains_vpore.csv\
  assets/mesh/sandstone_3062_grains_fpore.csv\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< --raw $(word 2, $^) $(word 3, $^) $(word 4, $^) $(word 5, $^) $(word 6, $^) 0.0651 > $@

build/$(MODE)/txt/mesh/sandstone_3062_grains_forman.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/sandstone_3062_grains.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< --raw $(word 2, $^) --standard --raw > $@

build/$(MODE)/txt/mesh/sandstone_3062_grains_forman_cbd.txt:\
  build/$(MODE)/bin/mesh_coboundary$(.EXE)\
  build/$(MODE)/txt/mesh/sandstone_3062_grains_forman.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< --raw < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/sandstone_3062_grains_forman_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/sandstone_3062_grains_forman.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/sandstone_3062_grains_forman_inner.txt:\
  build/$(MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(MODE)/txt/mesh/sandstone_3062_grains_forman.txt\
  build/$(MODE)/txt/mesh/sandstone_3062_grains_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/sandstone_3062_grains_forman_cbd_star.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/sandstone_3062_grains_forman.txt\
  build/$(MODE)/txt/mesh/sandstone_3062_grains_forman_inner.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/sandstone_3062_grains_forman_hodge_coeff.txt:\
  build/$(MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(MODE)/txt/mesh/sandstone_3062_grains_forman.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/sandstone_3062_grains_forman_hodge.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/sandstone_3062_grains_forman.txt\
  build/$(MODE)/txt/mesh/sandstone_3062_grains_forman_inner.txt\
  build/$(MODE)/txt/mesh/sandstone_3062_grains_forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

txt_mesh_sandstone_3062_grains: $(_txt_mesh_sandstone_3062_grains)

txt_mesh_sandstone_3062_grains_clean:
	-$(RM) $(_txt_mesh_sandstone_3062_grains)
