.PHONY: txt_mesh_tessfile1 txt_mesh_tessfile1_clean

_txt_mesh_tessfile1 :=\
  build/$(MODE)/txt/mesh/tessfile1.txt\
  build/$(MODE)/txt/mesh/tessfile1_kappa.txt\
#   build/$(MODE)/txt/mesh/tessfile1_forman.txt\

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

# build/$(MODE)/txt/mesh/tessfile1_forman.txt:\
#   build/$(MODE)/bin/forman_boundary$(.EXE)\
#   build/$(MODE)/txt/mesh/tessfile1.txt\
#   | build/$(MODE)/txt/mesh
# 	$(INTERPRETER) $< --raw $(word 2, $^) --standard --raw > $@

txt_mesh_tessfile1: $(_txt_mesh_tessfile1)

txt_mesh_tessfile1_clean:
	-$(RM) $(_txt_mesh_tessfile1)
