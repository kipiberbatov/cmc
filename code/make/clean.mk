################################### cleaning ###################################
# array
.PHONY: obj_array_clean
obj_array_clean:
	-$(RM) $(_obj_src_array) $(_obj_main_array)

.PHONY: lib_array_clean
lib_array_clean:
	-$(RM) build/$(MODE)/lib/src/libarray$(.LIB)

.PHONY: bin_array_clean
bin_array_clean:
	-$(RM) $(_bin_array)

.PHONY: array_clean
array_clean: obj_array_clean

.PHONY: array_distclean
array_distclean: array_clean lib_array_clean bin_array_clean txt_array_clean

# algebra
.PHONY: obj_algebra_clean
obj_algebra_clean:
	-$(RM) $(_obj_src_algebra) $(_obj_main_algebra)

.PHONY: lib_algebra_clean
lib_algebra_clean:
	-$(RM) build/$(MODE)/lib/src/libalgebra$(.LIB)

.PHONY: bin_algebra_clean
bin_algebra_clean:
	-$(RM) $(_bin_algebra)

.PHONY: algebra_clean
algebra_clean: obj_algebra_clean

.PHONY: algebra_distclean
algebra_distclean: algebra_clean lib_algebra_clean bin_algebra_clean\
  txt_algebra_clean

# region
.PHONY: obj_region_clean
obj_region_clean:
	-$(RM) $(_obj_src_region) $(_obj_main_region)

.PHONY: lib_region_clean
lib_region_clean:
	-$(RM) build/$(MODE)/lib/src/libregion$(.LIB)

.PHONY: bin_region_clean
bin_region_clean:
	-$(RM) $(_bin_region)

.PHONY: region_clean
region_clean: obj_region_clean

.PHONY: region_distclean
region_distclean: region_clean lib_region_clean bin_region_clean\
  txt_region_clean

# mesh
.PHONY: obj_mesh_clean
obj_mesh_clean:
	-$(RM) $(_obj_src_mesh) $(_obj_main_mesh)

.PHONY: lib_mesh_clean
lib_mesh_clean:
	-$(RM) build/$(MODE)/lib/src/libmesh$(.LIB)

.PHONY: bin_mesh_clean
bin_mesh_clean:
	-$(RM) $(_bin_mesh)

.PHONY: mesh_clean
mesh_clean: obj_mesh_clean

.PHONY: mesh_distclean
mesh_distclean: mesh_clean lib_mesh_clean bin_mesh_clean txt_mesh_clean

# diffusion
.PHONY: obj_diffusion_clean
obj_diffusion_clean:
	-$(RM) $(_obj_src_diffusion) $(_obj_main_diffusion)\
	       $(_obj_plugins_diffusion)

.PHONY: lib_diffusion_clean
lib_diffusion_clean:
	-$(RM) build/$(MODE)/lib/src/libdiffusion$(.LIB)\
	       build/$(MODE)/lib/plugins/libdiffusion$(.DLL)

.PHONY: bin_diffusion_clean
bin_diffusion_clean:
	-$(RM) $(_bin_diffusion)

.PHONY: diffusion_clean
diffusion_clean: obj_diffusion_clean

.PHONY: diffusion_distclean
diffusion_distclean: diffusion_clean lib_diffusion_clean bin_diffusion_clean\
  txt_diffusion_clean

# graphics
.PHONY: obj_graphics_clean
obj_graphics_clean:
	-$(RM) $(_obj_plugins_graphics)

.PHONY: lib_graphics_clean
lib_graphics_clean:
	-$(RM) build/$(MODE)/lib/src/libgraphics$(.LIB)

.PHONY: bin_graphics_clean
bin_graphics_clean:
	-$(RM) $(_bin_graphics)

.PHONY: graphics_clean
graphics_clean: obj_graphics_clean

.PHONY: graphics_distclean
graphics_distclean: graphics_clean lib_graphics_clean bin_graphics_clean\
  txt_graphics_clean

# gtk_animation
.PHONY: obj_gtk_animation_clean
obj_gtk_animation_clean:
	-$(RM) $(_obj_src_gtk_animation)

.PHONY: lib_gtk_animation_clean
lib_gtk_animation_clean:
	-$(RM) build/$(MODE)/lib/plugins/libgtk_animation$(.DLL)

.PHONY: animation_clean
animation_clean: obj_gtk_animation_clean

.PHONY: gtk_animation_distclean
gtk_animation_distclean: gtk_animation_clean lib_gtk_animation_clean

# cairo_animation
.PHONY: obj_cairo_animation_clean
obj_cairo_animation_clean:
	-$(RM) $(_obj_src_cairo_animation)

.PHONY: lib_cairo_animation_clean
lib_cairo_animation_clean:
	-$(RM) build/$(MODE)/lib/plugins/libcairo_animation$(.DLL)

.PHONY: animation_clean
animation_clean: obj_cairo_animation_clean

.PHONY: cairo_animation_distclean
cairo_animation_distclean: cairo_animation_clean lib_cairo_animation_clean

# cairo_graphics
.PHONY: obj_cairo_graphics_clean
obj_cairo_graphics_clean:
	-$(RM) $(_obj_plugins_cairo_graphics)

.PHONY: lib_cairo_graphics_clean
lib_cairo_graphics_clean:
	-$(RM) build/$(MODE)/lib/plugins/libcairo_graphics$(.DLL)

.PHONY: cairo_graphics_clean
cairo_graphics_clean: obj_cairo_graphics_clean

.PHONY: cairo_graphics_distclean
cairo_graphics_distclean: cairo_graphics_clean lib_cairo_graphics_clean

# all
.PHONY: obj_clean
obj_clean:
	-$(RM) -r build/$(MODE)/obj

.PHONY: obj_src_clean
obj_src_clean:
	-$(RM) -r build/$(MODE)/obj/src

.PHONY: obj_main_clean
obj_main_clean:
	-$(RM) -r build/$(MODE)/obj/main

.PHONY: obj_plugins_clean
obj_plugins_clean:
	-$(RM) -r build/$(MODE)/obj/plugins

.PHONY: lib_clean
lib_clean:
	-$(RM) -r build/$(MODE)/lib

.PHONY: lib_src_clean
lib_src_clean:
	-$(RM) -r build/$(MODE)/lib/src

.PHONY: lib_plugins_clean
lib_plugins_clean:
	-$(RM) -r build/$(MODE)/lib/plugins

.PHONY: bin_clean
bin_clean:
	-$(RM) -r build/$(MODE)/bin

.PHONY: clean
clean: obj_clean
