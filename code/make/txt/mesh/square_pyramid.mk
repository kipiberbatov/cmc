.PHONY: txt_mesh_square_pyramid txt_mesh_square_pyramid_clean

_txt_mesh_square_pyramid := \
  build/$(MODE)/txt/mesh/square_pyramid_forman.txt\

build/$(MODE)/txt/mesh/square_pyramid_forman.txt:\
  build/$(MODE)/bin/forman$(.EXE)\
  data/mesh/square_pyramid.txt\
  | build/$(MODE)/txt/mesh
	$(INTERPRETER) $< --raw $(word 2, $^) --standard --raw > $@

txt_mesh_square_pyramid: $(_txt_mesh_square_pyramid)

txt_mesh_square_pyramid_clean:
	-$(RM) $(_txt_mesh_square_pyramid)
