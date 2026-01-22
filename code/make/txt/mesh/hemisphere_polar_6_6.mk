.PHONY: txt_mesh_hemisphere_polar_6_6 txt_mesh_hemisphere_polar_6_6_clean

_txt_mesh_hemisphere_polar_6_6 :=\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6/data.txt\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6/forman.txt\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6/forman_cbd.txt\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6/forman_vol.txt\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6/forman_inner.txt\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6/forman_cbd_star.txt\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6/forman_hodge_coeff.txt\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6/forman_hodge.txt\

build/$(MODE)/txt/mesh/hemisphere_polar_6_6: | build/$(MODE)/txt/mesh
	mkdir -p $@

build/$(MODE)/txt/mesh/hemisphere_polar_6_6/data.txt:\
  build/$(MODE)/bin/mesh_hemisphere_polar$(.EXE)\
  | build/$(MODE)/txt/mesh/hemisphere_polar_6_6
	$(INTERPRETER) $< 6 6 > $@

build/$(MODE)/txt/mesh/hemisphere_polar_6_6/forman.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6/data.txt\
  | build/$(MODE)/txt/mesh/hemisphere_polar_6_6
	$(INTERPRETER) $< --raw $(word 2, $^) --polar --raw > $@

build/$(MODE)/txt/mesh/hemisphere_polar_6_6/forman_cbd.txt:\
  build/$(MODE)/bin/mesh_coboundary$(.EXE)\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6/forman.txt\
  | build/$(MODE)/txt/mesh/hemisphere_polar_6_6
	$(INTERPRETER) $< --raw < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/hemisphere_polar_6_6/forman_vol.txt:\
  build/$(MODE)/bin/mesh_measures$(.EXE)\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6/forman.txt\
  | build/$(MODE)/txt/mesh/hemisphere_polar_6_6
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --mesh-measures-function=hemisphere-forman\
  > $@

build/$(MODE)/txt/mesh/hemisphere_polar_6_6/forman_inner.txt:\
  build/$(MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6/forman.txt\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6/forman_vol.txt\
  | build/$(MODE)/txt/mesh/hemisphere_polar_6_6
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/hemisphere_polar_6_6/forman_cbd_star.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6/forman.txt\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6/forman_inner.txt\
  | build/$(MODE)/txt/mesh/hemisphere_polar_6_6
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/hemisphere_polar_6_6/forman_hodge_coeff.txt:\
  build/$(MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6/forman.txt\
  | build/$(MODE)/txt/mesh/hemisphere_polar_6_6
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/hemisphere_polar_6_6/forman_hodge.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6/forman.txt\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6/forman_inner.txt\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6/forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh/hemisphere_polar_6_6
	$(INTERPRETER) $^ > $@

txt_mesh_hemisphere_polar_6_6: $(_txt_mesh_hemisphere_polar_6_6)

txt_mesh_hemisphere_polar_6_6_clean:
	-$(RM) $(_txt_mesh_hemisphere_polar_6_6)

txt_mesh_hemisphere_polar_6_6_distclean:
	-$(RM) -r build/$(MODE)/txt/mesh/hemisphere_polar_6_6
