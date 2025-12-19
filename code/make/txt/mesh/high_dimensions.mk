.PHONY: txt_mesh_high_dimensions txt_mesh_high_dimensions_clean

# dimensions 8, 9, 10
_txt_mesh_high_dimensions :=\
  build/$(MODE)/txt/mesh/brick_8d_1.txt\
  build/$(MODE)/txt/mesh/brick_8d_2.txt\
  build/$(MODE)/txt/mesh/brick_9d_1.txt\
  build/$(MODE)/txt/mesh/brick_9d_2.txt\
  build/$(MODE)/txt/mesh/brick_10d_1.txt\
  build/$(MODE)/txt/mesh/brick_8d_1_forman.txt\

build/$(MODE)/txt/mesh/brick_8d_1.txt:\
  build/$(MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< 8 1 > $@

build/$(MODE)/txt/mesh/brick_8d_2.txt:\
  build/$(MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< 8 2 > $@

build/$(MODE)/txt/mesh/brick_9d_1.txt:\
  build/$(MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< 9 1 > $@

build/$(MODE)/txt/mesh/brick_9d_2.txt:\
  build/$(MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< 9 2 > $@

build/$(MODE)/txt/mesh/brick_10d_1.txt:\
  build/$(MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< 10 1 > $@

build/$(MODE)/txt/mesh/brick_8d_1_forman.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/brick_8d_1.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< --raw $(word 2, $^) --standard --raw > $@

txt_mesh_high_dimensions: $(_txt_mesh_high_dimensions)

txt_mesh_high_dimensions_clean:
	-$(RM) $(_txt_mesh_high_dimensions)
