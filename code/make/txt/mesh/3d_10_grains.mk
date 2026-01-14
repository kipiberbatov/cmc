.PHONY: txt_mesh_3d_10_grains txt_mesh_3d_10_grains_clean

_txt_mesh_3d_10_grains :=\
  build/$(MODE)/txt/mesh/3d_10_grains.txt\
  build/$(MODE)/txt/mesh/3d_10_grains_forman.txt\

build/$(MODE)/txt/mesh/3d_10_grains.txt:\
  build/$(MODE)/bin/mesh_and_boundary_file_scan$(.EXE)\
  data/mesh/3d_10_grains.tess\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< --mesh-format=tess $(word 2, $^) > $@

build/$(MODE)/txt/mesh/3d_10_grains_forman.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/3d_10_grains.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< --raw $(word 2, $^) --standard --raw > $@

txt_mesh_3d_10_grains: $(_txt_mesh_3d_10_grains)

txt_mesh_3d_10_grains_clean:
	-$(RM) $(_txt_mesh_3d_10_grains)
