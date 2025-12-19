.PHONY: gtk_filled_window gtk_filled_window_clean gtk_filled_window_distclean

build/$(MODE)/gtk/filled_window: | build/$(MODE)/gtk
	mkdir -p $@

_gtk_filled_window :=\
  build/$(MODE)/gtk/filled_window/rainbow_100.log\

build/$(MODE)/gtk/filled_window/rainbow_100.log:\
  build/$(MODE)/bin/cmc_graphics_filled_window$(.EXE)\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_filled_window$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_gtk_animation$(.OBJ)\
  | build/$(MODE)/gtk/filled_window\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $<\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_filled_window\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_gtk_animation\
  --title=filled_window\
  --close-automatically=$(CLOSE_AUTOMATICALLY)\
  --timelapse=$(TIMELAPSE)\
  --output=$@

gtk_filled_window: $(_gtk_filled_window)

gtk_filled_window_clean:
	-$(RM) $(_gtk_filled_window)

gtk_filled_window_distclean:
	-$(RM) -r build/$(MODE)/gtk/filled_window
