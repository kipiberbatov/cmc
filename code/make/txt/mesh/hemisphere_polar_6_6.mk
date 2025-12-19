.PHONY: txt_mesh_hemisphere_polar_6_6 txt_mesh_hemisphere_polar_6_6_clean

_txt_mesh_hemisphere_polar_6_6 :=\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6.txt\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6_forman.txt\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6_forman_cbd.txt\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6_forman_vol.txt\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6_forman_inner.txt\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6_forman_cbd_star.txt\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6_forman_hodge_coeff.txt\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6_forman_hodge.txt\

build/$(MODE)/txt/mesh/hemisphere_polar_6_6.txt:\
  build/$(MODE)/bin/mesh_hemisphere_polar$(.EXE) | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< 6 6 > $@

build/$(MODE)/txt/mesh/hemisphere_polar_6_6_forman.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< --raw $(word 2, $^) --polar --raw > $@

build/$(MODE)/txt/mesh/hemisphere_polar_6_6_forman_cbd.txt:\
  build/$(MODE)/bin/mesh_coboundary$(.EXE)\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6_forman.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< --raw < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/hemisphere_polar_6_6_forman_vol.txt:\
  build/$(MODE)/bin/mesh_measures$(.EXE)\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6_forman.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --mesh-measures-function=hemisphere-forman\
  > $@

build/$(MODE)/txt/mesh/hemisphere_polar_6_6_forman_inner.txt:\
  build/$(MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6_forman.txt\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6_forman_vol.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/hemisphere_polar_6_6_forman_cbd_star.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6_forman.txt\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6_forman_inner.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/hemisphere_polar_6_6_forman_hodge_coeff.txt:\
  build/$(MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6_forman.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/hemisphere_polar_6_6_forman_hodge.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6_forman.txt\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6_forman_inner.txt\
  build/$(MODE)/txt/mesh/hemisphere_polar_6_6_forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $^ > $@

txt_mesh_hemisphere_polar_6_6: $(_txt_mesh_hemisphere_polar_6_6)

txt_mesh_hemisphere_polar_6_6_clean:
	-$(RM) $(_txt_mesh_hemisphere_polar_6_6)
