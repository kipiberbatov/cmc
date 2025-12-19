.PHONY: pdf_filled_window pdf_filled_window_clean pdf_filled_window_distclean

build/$(MODE)/pdf/filled_window: | build/$(MODE)/pdf
	mkdir -p $@

_pdf_filled_window :=\
  build/$(MODE)/pdf/filled_window/rainbow_100.pdf\

build/$(MODE)/pdf/filled_window/rainbow_100.pdf:\
  build/$(MODE)/bin/cmc_graphics_filled_window$(.EXE)\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_filled_window$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/filled_window\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $<\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_filled_window\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_pdf_animation\
  --output=$@

pdf_filled_window: $(_pdf_filled_window)

pdf_filled_window_clean:
	-$(RM) $(_pdf_filled_window)

pdf_filled_window_distclean:
	-$(RM) -r build/$(MODE)/pdf/filled_window
