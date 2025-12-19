.PHONY: txt_graphics txt_graphics_clean txt_graphics_distclean

build/$(MODE)/txt/graphics: | build/$(MODE)/txt
	mkdir -p $@

_txt_graphics := build/$(MODE)/txt/graphics/frame.txt

build/$(MODE)/txt/graphics/frame.txt: build/$(MODE)/bin/frame\
  | build/$(MODE)/txt/graphics
	$(INTERPRETER) $< > $@

txt_graphics: bin_graphics $(_txt_graphics)

txt_graphics_clean:
	-$(RM) $(_txt_graphics)

txt_graphics_distclean:
	-$(RM) -r build/$(MODE)/txt/graphics
