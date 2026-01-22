.PHONY: txt_mesh_disk_polar_18_10 txt_mesh_disk_polar_18_10_clean

_txt_mesh_disk_polar_18_10 :=\
  build/$(MODE)/txt/mesh/disk_polar_18_10/data.txt\
  build/$(MODE)/txt/mesh/disk_polar_18_10/forman.txt\
  build/$(MODE)/txt/mesh/disk_polar_18_10/forman_cbd.txt\
  build/$(MODE)/txt/mesh/disk_polar_18_10/forman_vol.txt\
  build/$(MODE)/txt/mesh/disk_polar_18_10/forman_inner.txt\
  build/$(MODE)/txt/mesh/disk_polar_18_10/forman_cbd_star.txt\
  build/$(MODE)/txt/mesh/disk_polar_18_10/forman_hodge_coeff.txt\
  build/$(MODE)/txt/mesh/disk_polar_18_10/forman_hodge.txt\

build/$(MODE)/txt/mesh/disk_polar_18_10: | build/$(MODE)/txt/mesh
	mkdir -p $@

build/$(MODE)/txt/mesh/disk_polar_18_10/data.txt:\
  build/$(MODE)/bin/mesh_disk_polar$(.EXE)\
  | build/$(MODE)/txt/mesh/disk_polar_18_10
	$(INTERPRETER) $< 18 10 > $@

build/$(MODE)/txt/mesh/disk_polar_18_10/forman.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_18_10/data.txt\
  | build/$(MODE)/txt/mesh/disk_polar_18_10
	$(INTERPRETER) $< --raw $(word 2, $^) --polar --raw > $@

build/$(MODE)/txt/mesh/disk_polar_18_10/forman_cbd.txt:\
  build/$(MODE)/bin/mesh_coboundary$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_18_10/forman.txt\
  | build/$(MODE)/txt/mesh/disk_polar_18_10
	$(INTERPRETER) $< --raw < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/disk_polar_18_10/forman_vol.txt:\
  build/$(MODE)/bin/mesh_measures$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_18_10/forman.txt\
  | build/$(MODE)/txt/mesh/disk_polar_18_10
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --mesh-measures-function=polar-forman\
  > $@

build/$(MODE)/txt/mesh/disk_polar_18_10/forman_inner.txt:\
  build/$(MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_18_10/forman.txt\
  build/$(MODE)/txt/mesh/disk_polar_18_10/forman_vol.txt\
  | build/$(MODE)/txt/mesh/disk_polar_18_10
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/disk_polar_18_10/forman_cbd_star.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_18_10/forman.txt\
  build/$(MODE)/txt/mesh/disk_polar_18_10/forman_inner.txt\
  | build/$(MODE)/txt/mesh/disk_polar_18_10
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/disk_polar_18_10/forman_hodge_coeff.txt:\
  build/$(MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_18_10/forman.txt\
  | build/$(MODE)/txt/mesh/disk_polar_18_10
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/disk_polar_18_10/forman_hodge.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_18_10/forman.txt\
  build/$(MODE)/txt/mesh/disk_polar_18_10/forman_inner.txt\
  build/$(MODE)/txt/mesh/disk_polar_18_10/forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh/disk_polar_18_10
	$(INTERPRETER) $^ > $@

txt_mesh_disk_polar_18_10: $(_txt_mesh_disk_polar_18_10)

txt_mesh_disk_polar_18_10_clean:
	-$(RM) $(_txt_mesh_disk_polar_18_10)

txt_mesh_disk_polar_18_10_distclean:
	-$(RM) -r build/$(MODE)/txt/mesh/disk_polar_18_10
