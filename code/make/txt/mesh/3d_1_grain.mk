.PHONY: txt_mesh_3d_1_grain txt_mesh_3d_1_grain_clean

_txt_mesh_3d_1_grain :=\
  build/$(MODE)/txt/mesh/3d_1_grain.txt\
  build/$(MODE)/txt/mesh/3d_1_grain_check_boundary_products.txt\
  build/$(MODE)/txt/mesh/3d_1_grain_vol.txt\
  build/$(MODE)/txt/mesh/3d_1_grain_forman.txt\
  build/$(MODE)/txt/mesh/3d_1_grain_forman_check_boundary_products.txt\
  build/$(MODE)/txt/mesh/3d_1_grain_forman_vol.txt\

build/$(MODE)/txt/mesh/3d_1_grain.txt:\
  build/$(MODE)/bin/mesh_and_boundary_file_scan$(.EXE)\
  data/mesh/3d_1_grain.tess\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< --mesh-format=tess $(word 2, $^) > $@

build/$(MODE)/txt/mesh/3d_1_grain_check_boundary_products.txt:\
  build/$(MODE)/bin/mesh_boundary_chain_complex_check$(.EXE)\
  build/$(MODE)/txt/mesh/3d_1_grain.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/3d_1_grain_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/3d_1_grain.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/3d_1_grain_forman.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/3d_1_grain.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< --raw $(word 2, $^) --standard --raw > $@

build/$(MODE)/txt/mesh/3d_1_grain_forman_check_boundary_products.txt:\
  build/$(MODE)/bin/mesh_boundary_chain_complex_check$(.EXE)\
  build/$(MODE)/txt/mesh/3d_1_grain_forman.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/3d_1_grain_forman_vol.txt:\
  build/$(MODE)/bin/mesh_qc_vol$(.EXE)\
  build/$(MODE)/txt/mesh/3d_1_grain_forman.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< < $(word 2, $^) > $@

txt_mesh_3d_1_grain: $(_txt_mesh_3d_1_grain)

txt_mesh_3d_1_grain_clean:
	-$(RM) $(_txt_mesh_3d_1_grain)
