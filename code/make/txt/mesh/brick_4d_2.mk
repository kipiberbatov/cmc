.PHONY: txt_mesh_brick_4d_2 txt_mesh_brick_4d_2_clean

_txt_mesh_brick_4d_2 :=\
  build/$(MODE)/txt/mesh/brick_4d_2/data.txt\
  build/$(MODE)/txt/mesh/brick_4d_2/forman.txt

build/$(MODE)/txt/mesh/brick_4d_2: | build/$(MODE)/txt/mesh
	mkdir -p $@

build/$(MODE)/txt/mesh/brick_4d_2/data.txt:\
  build/$(MODE)/bin/mesh_brick_regular$(.EXE)\
  | build/$(MODE)/txt/mesh/brick_4d_2
	$(INTERPRETER) $< 4 2 > $@

build/$(MODE)/txt/mesh/brick_4d_2/forman.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/brick_4d_2/data.txt\
  | build/$(MODE)/txt/mesh/brick_4d_2
	$(INTERPRETER) $< --raw $(word 2, $^) --standard --raw > $@

txt_mesh_brick_4d_2: $(_txt_mesh_brick_4d_2)

txt_mesh_brick_4d_2_clean:
	-$(RM) $(_txt_mesh_brick_4d_2)

txt_mesh_brick_4d_2_distclean:
	-$(RM) -r build/$(MODE)/txt/mesh/brick_4d_2
