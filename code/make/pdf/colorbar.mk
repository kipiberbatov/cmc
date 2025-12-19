.PHONY: pdf_colorbar pdf_colorbar_clean pdf_colorbar_distclean

build/$(MODE)/pdf/colorbar: | build/$(MODE)/pdf
	mkdir -p $@

_pdf_colorbar :=\
  build/$(MODE)/pdf/colorbar/rainbow_100_horizontal_500_50.pdf\
  build/$(MODE)/pdf/colorbar/rainbow_100_vertical_50_500.pdf\

build/$(MODE)/pdf/colorbar/rainbow_100_horizontal_500_50.pdf:\
  build/$(MODE)/bin/cmc_graphics_colorbar$(.EXE)\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_colorbar$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/colorbar\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $<\
  --total-colors=100\
  --direction=horizontal\
  --width=500\
  --height=50\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_colorbar\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_pdf_animation\
  --output=$@

build/$(MODE)/pdf/colorbar/rainbow_100_vertical_50_500.pdf:\
  build/$(MODE)/bin/cmc_graphics_colorbar$(.EXE)\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_colorbar$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/colorbar\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $<\
  --total-colors=100\
  --direction=vertical\
  --width=50\
  --height=500\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_colorbar\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_pdf_animation\
  --output=$@

pdf_colorbar: $(_pdf_colorbar)

pdf_colorbar_clean:
	-$(RM) $(_pdf_colorbar)

pdf_colorbar_distclean:
	-$(RM) -r build/$(MODE)/pdf/colorbar
