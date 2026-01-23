.PHONY: txt txt_clean txt_distclean

build/$(MODE)/txt: | build/$(MODE)
	mkdir -p $@

include code/make/txt/array.mk
include code/make/txt/algebra.mk
include code/make/txt/region.mk
include code/make/txt/mesh.mk
include code/make/txt/diffusion.mk
include code/make/txt/graphics.mk

_txt :=\
  $(_txt_array)\
  $(_txt_algebra)\
  $(_txt_region)\
  $(_txt_mesh)\
  $(_txt_diffusion)\
  $(_txt_graphics)\

txt: $(_txt)

txt_clean:
	-$(RM) $(_txt)

txt_distclean:
	-$(RM) -r build/$(MODE)/txt
