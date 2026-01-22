.PHONY: txt_mesh_high_dimensions txt_mesh_high_dimensions_clean

# dimensions 8, 9, 10
_txt_mesh_high_dimensions :=\
  build/$(MODE)/txt/mesh/brick_high_dimensions/8d_1.txt\
  build/$(MODE)/txt/mesh/brick_high_dimensions/8d_2.txt\
  build/$(MODE)/txt/mesh/brick_high_dimensions/9d_1.txt\
  build/$(MODE)/txt/mesh/brick_high_dimensions/9d_2.txt\
  build/$(MODE)/txt/mesh/brick_high_dimensions/10d_1.txt\
  build/$(MODE)/txt/mesh/brick_high_dimensions/8d_1_forman.txt\

build/$(MODE)/txt/mesh/brick_high_dimensions: | build/$(MODE)/txt/mesh
	mkdir -p $@

build/$(MODE)/txt/mesh/brick_high_dimensions/8d_1.txt:\
  build/$(MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(MODE)/txt/mesh/brick_high_dimensions
	$(INTERPRETER) $< 8 1 > $@

build/$(MODE)/txt/mesh/brick_high_dimensions/8d_2.txt:\
  build/$(MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(MODE)/txt/mesh/brick_high_dimensions
	$(INTERPRETER) $< 8 2 > $@

build/$(MODE)/txt/mesh/brick_high_dimensions/9d_1.txt:\
  build/$(MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(MODE)/txt/mesh/brick_high_dimensions
	$(INTERPRETER) $< 9 1 > $@

build/$(MODE)/txt/mesh/brick_high_dimensions/9d_2.txt:\
  build/$(MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(MODE)/txt/mesh/brick_high_dimensions
	$(INTERPRETER) $< 9 2 > $@

build/$(MODE)/txt/mesh/brick_high_dimensions/10d_1.txt:\
  build/$(MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(MODE)/txt/mesh/brick_high_dimensions
	$(INTERPRETER) $< 10 1 > $@

build/$(MODE)/txt/mesh/brick_high_dimensions/8d_1_forman.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/brick_high_dimensions/8d_1.txt\
  | build/$(MODE)/txt/mesh/brick_high_dimensions
	$(INTERPRETER) $< --raw $(word 2, $^) --standard --raw > $@

txt_mesh_high_dimensions: $(_txt_mesh_high_dimensions)

txt_mesh_high_dimensions_clean:
	-$(RM) $(_txt_mesh_high_dimensions)

txt_mesh_high_dimensions_distclean:
	-$(RM) -r build/$(MODE)/txt/mesh/brick_high_dimensions
