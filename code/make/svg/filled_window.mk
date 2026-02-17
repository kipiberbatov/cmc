.PHONY: svg_filled_window svg_filled_window_clean svg_filled_window_distclean

build/$(MODE)/svg/filled_window: | build/$(MODE)/svg
	mkdir -p $@

_svg_filled_window :=\
  build/$(MODE)/svg/filled_window/rainbow_100.svg\

build/$(MODE)/svg/filled_window/rainbow_100.svg:\
  build/$(MODE)/bin/cmc_graphics_filled_window$(.EXE)\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_filled_window$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_animation_svg$(.OBJ)\
  | build/$(MODE)/svg/filled_window\
    build/$(MODE)/lib/plugins/libcairo_graphics$(.DLL)\
    build/$(MODE)/lib/plugins/libcairo_animation$(.DLL)
	$(INTERPRETER) $<\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_filled_window\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_animation_svg\
  --output=$@

svg_filled_window: $(_svg_filled_window)

svg_filled_window_clean:
	-$(RM) $(_svg_filled_window)

svg_filled_window_distclean:
	-$(RM) -r build/$(MODE)/svg/filled_window
