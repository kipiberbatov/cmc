.PHONY: txt_mesh_brick_4d_2 txt_mesh_brick_4d_2_clean

_txt_mesh_brick_4d_2 :=\
  build/$(MODE)/txt/mesh/brick_4d_2.txt\
  build/$(MODE)/txt/mesh/brick_4d_2_forman.txt

build/$(MODE)/txt/mesh/brick_4d_2.txt:\
  build/$(MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< 4 2 > $@

build/$(MODE)/txt/mesh/brick_4d_2_forman.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/brick_4d_2.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< --raw $(word 2, $^) --standard --raw > $@

txt_mesh_brick_4d_2: $(_txt_mesh_brick_4d_2)

txt_mesh_brick_4d_2_clean:
	-$(RM) $(_txt_mesh_brick_4d_2)
