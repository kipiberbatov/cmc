.PHONY: txt_region txt_region_clean txt_region_distclean

build/$(MODE)/txt/region: | build/$(MODE)/txt
	mkdir -p $@

_txt_region :=\
  build/$(MODE)/txt/region/simplex_2d_0_measure_and_centroid.txt\
  build/$(MODE)/txt/region/quasi_cube_2d_0_measure_and_centroid.txt\

build/$(MODE)/txt/region/simplex_2d_0_measure_and_centroid.txt:\
  build/$(MODE)/bin/simplex$(.EXE)\
  data/region/simplex_2d_0.txt | build/$(MODE)/txt/region
	$(INTERPRETER) $< < $(word 2, $^) > $@

build/$(MODE)/txt/region/quasi_cube_2d_0_measure_and_centroid.txt:\
  build/$(MODE)/bin/quasi_cube$(.EXE)\
  data/region/quasi_cube_2d_0.txt | build/$(MODE)/txt/region
	$(INTERPRETER) $< < $(word 2, $^) > $@

txt_region: bin_region $(_txt_region)

txt_region_clean:
	-$(RM) $(_txt_region)

txt_region_distclean:
	-$(RM) -r build/$(MODE)/txt/region
