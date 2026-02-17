.PHONY: pdf_filled_window pdf_filled_window_clean pdf_filled_window_distclean

build/$(MODE)/pdf/filled_window: | build/$(MODE)/pdf
	mkdir -p $@

_pdf_filled_window :=\
  build/$(MODE)/pdf/filled_window/rainbow_100.pdf\

build/$(MODE)/pdf/filled_window/rainbow_100.pdf:\
  build/$(MODE)/bin/cmc_graphics_filled_window$(.EXE)\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_filled_window$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_animation_pdf$(.OBJ)\
  | build/$(MODE)/pdf/filled_window\
    build/$(MODE)/lib/plugins/libcairo_graphics$(.DLL)\
    build/$(MODE)/lib/plugins/libcairo_animation$(.DLL)
	$(INTERPRETER) $<\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_filled_window\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_animation_pdf\
  --output=$@

pdf_filled_window: $(_pdf_filled_window)

pdf_filled_window_clean:
	-$(RM) $(_pdf_filled_window)

pdf_filled_window_distclean:
	-$(RM) -r build/$(MODE)/pdf/filled_window
