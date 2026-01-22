.PHONY: txt_mesh_rectangle_20_15_brick_5_3\
	txt_mesh_rectangle_20_15_brick_5_3_clean

_txt_mesh_rectangle_20_15_brick_5_3 :=\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/data.txt\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman.txt\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman_cbd.txt\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman_vol.txt\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman_inner.txt\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman_cbd_star.txt\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman_hodge_coeff.txt\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman_hodge.txt\

build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3: | build/$(MODE)/txt/mesh
	mkdir -p $@

build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/data.txt:\
  build/$(MODE)/bin/mesh_brick$(.EXE) | build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3
	$(INTERPRETER) $< 2 20 15 5 3 > $@

build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman.txt:\
  build/$(MODE)/bin/forman_boundary$(.EXE)\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/data.txt\
  | build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3
	$(INTERPRETER) $< --raw $(word 2, $^) --standard --raw > $@

build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman_cbd.txt:\
  build/$(MODE)/bin/mesh_coboundary$(.EXE)\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman.txt\
  | build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3
	$(INTERPRETER) $< --raw < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman_vol.txt:\
  build/$(MODE)/bin/mesh_measures$(.EXE)\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman.txt\
  | build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  > $@

build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman_inner.txt:\
  build/$(MODE)/bin/mesh_qc_inner_direct$(.EXE)\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman.txt\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman_vol.txt\
  | build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman_cbd_star.txt:\
  build/$(MODE)/bin/mesh_qc_coboundary_star$(.EXE)\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman.txt\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman_inner.txt\
  | build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3
	$(INTERPRETER) $^ > $@

build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman_hodge_coeff.txt:\
  build/$(MODE)/bin/mesh_qc_hodge_coeff$(.EXE)\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman.txt\
  | build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman_hodge.txt:\
  build/$(MODE)/bin/mesh_qc_hodge$(.EXE)\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman.txt\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman_inner.txt\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman_hodge_coeff.txt\
  | build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3
	$(INTERPRETER) $^ > $@

txt_mesh_rectangle_20_15_brick_5_3: $(_txt_mesh_rectangle_20_15_brick_5_3)

txt_mesh_rectangle_20_15_brick_5_3_clean:
	-$(RM) $(_txt_mesh_rectangle_20_15_brick_5_3)

txt_mesh_rectangle_20_15_brick_5_3_distclean:
	-$(RM) -r build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3
