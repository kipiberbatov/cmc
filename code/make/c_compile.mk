############### general preprocessor, compiler and linker flags ################
CPPFLAGS := -MMD -MP
CFLAGS := -O2 -Wall -Wfatal-errors -Werror -fPIC
LDLIBS := -lm

######################### OS-dependent file extensions #########################
# Windows extensions are fine but the project cannot be built on Windows
ifeq ($(OS), Windows_NT)
  .EXE := .exe
  .DLL := .dll
  .LIB := .lib
  .OBJ := .obj
  .DEP := .d
else
  .EXE :=
  .LIB := .a
  .OBJ := .o
  .DEP := .d
  UNAME_S := $(shell uname -s)
  ifeq ($(UNAME_S), Linux)
    .DLL := .so
  endif
  ifeq ($(UNAME_S), Darwin)
    .DLL := .dylib
  endif
endif

###################### modules, plugins and dependencies #######################
MODULES := array algebra region mesh diffusion graphics
PLUGINS := diffusion animation canvas
# array:
# algebra: array
# region: array
# mesh: region algebra
# diffusion: mesh
# graphics: mesh (dynamically on plugins/diffusion, and hence, on diffusion)

# plugins/diffusion: mesh (+ diffusion headers)
# canvas: [Cairo] (+ animation headers)
# animation: graphics Cairo GTK3

############################ names of source files #############################
_src_array := $(wildcard code/c/src/array/*.c)
_src_algebra := $(wildcard code/c/src/algebra/*.c)
_src_region := $(wildcard code/c/src/region/*.c)
_src_mesh := $(wildcard code/c/src/mesh/*.c)
_src_diffusion := $(wildcard code/c/src/diffusion/*.c)
_src_graphics := $(wildcard code/c/src/graphics/*.c)

############################# names of main files ##############################
_main_array := $(wildcard code/c/main/array/*.c)
_main_algebra := $(wildcard code/c/main/algebra/*.c)
_main_region := $(wildcard code/c/main/region/*.c)
_main_mesh := $(wildcard code/c/main/mesh/*.c)
_main_diffusion := $(wildcard code/c/main/diffusion/*.c)
_main_graphics := $(wildcard code/c/main/graphics/*.c)

############################ names of plugin files #############################
_plugins_diffusion := $(wildcard code/c/plugins/diffusion/*.c)
_plugins_animation := $(wildcard code/c/plugins/animation/*.c)
_plugins_canvas := $(wildcard code/c/plugins/canvas/*.c)

######################### names of source object files #########################
_obj_src_array := $(patsubst code/c/src/array/%.c,\
  build/$(MODE)/obj/src/%$(.OBJ), $(_src_array))

_obj_src_algebra := $(patsubst code/c/src/algebra/%.c,\
  build/$(MODE)/obj/src/%$(.OBJ), $(_src_algebra))

_obj_src_region := $(patsubst code/c/src/region/%.c,\
  build/$(MODE)/obj/src/%$(.OBJ), $(_src_region))

_obj_src_mesh := $(patsubst code/c/src/mesh/%.c,\
  build/$(MODE)/obj/src/%$(.OBJ), $(_src_mesh))

_obj_src_diffusion := $(patsubst code/c/src/diffusion/%.c,\
  build/$(MODE)/obj/src/%$(.OBJ), $(_src_diffusion))

_obj_src_graphics := $(patsubst code/c/src/graphics/%.c,\
  build/$(MODE)/obj/src/%$(.OBJ), $(_src_graphics))

########################## names of main object files ##########################
_obj_main_array := $(patsubst code/c/main/array/%.c,\
  build/$(MODE)/obj/main/%$(.OBJ), $(_main_array))

_obj_main_algebra := $(patsubst code/c/main/algebra/%.c,\
  build/$(MODE)/obj/main/%$(.OBJ), $(_main_algebra))

_obj_main_region := $(patsubst code/c/main/region/%.c,\
  build/$(MODE)/obj/main/%$(.OBJ), $(_main_region))

_obj_main_mesh := $(patsubst code/c/main/mesh/%.c,\
  build/$(MODE)/obj/main/%$(.OBJ), $(_main_mesh))

_obj_main_diffusion := $(patsubst code/c/main/diffusion/%.c,\
  build/$(MODE)/obj/main/%$(.OBJ), $(_main_diffusion))

_obj_main_graphics := $(patsubst code/c/main/graphics/%.c,\
  build/$(MODE)/obj/main/%$(.OBJ), $(_main_graphics))

######################### names of plugin object files #########################
_obj_plugins_diffusion := $(patsubst code/c/plugins/diffusion/%.c,\
  build/$(MODE)/obj/plugins/%$(.OBJ), $(_plugins_diffusion))

_obj_plugins_animation := $(patsubst code/c/plugins/animation/%.c,\
  build/$(MODE)/obj/plugins/%$(.OBJ), $(_plugins_animation))

_obj_plugins_canvas := $(patsubst code/c/plugins/canvas/%.c,\
  build/$(MODE)/obj/plugins/%$(.OBJ), $(_plugins_canvas))

########################## names of executable files ###########################
_bin_array := $(patsubst code/c/main/array/%.c,\
  build/$(MODE)/bin/%$(.EXE), $(_main_array))

_bin_algebra := $(patsubst code/c/main/algebra/%.c,\
  build/$(MODE)/bin/%$(.EXE), $(_main_algebra))

_bin_region := $(patsubst code/c/main/region/%.c,\
  build/$(MODE)/bin/%$(.EXE), $(_main_region))

_bin_mesh := $(patsubst code/c/main/mesh/%.c,\
  build/$(MODE)/bin/%$(.EXE), $(_main_mesh))

_bin_diffusion := $(patsubst code/c/main/diffusion/%.c,\
  build/$(MODE)/bin/%$(.EXE), $(_main_diffusion))

_bin_graphics := $(patsubst code/c/main/graphics/%.c,\
  build/$(MODE)/bin/%$(.EXE), $(_main_graphics))

################# include directories for compiling main files #################
_include_main_array := -iquote code/c/include/array
_include_main_algebra := $(_include_main_array) -iquote code/c/include/algebra
_include_main_region := $(_include_main_array) -iquote code/c/include/region
_include_main_mesh := $(_include_main_algebra)\
  -iquote code/c/include/region -iquote code/c/include/mesh
_include_main_diffusion := $(_include_main_mesh)\
  -iquote code/c/include/diffusion
_include_main_graphics := $(_include_main_mesh) -iquote code/c/include/graphics

################ include directories for compiling source files ################
_include_src_array := $(_include_main_array) -iquote code/c/src/array
_include_src_algebra := $(_include_main_algebra) -iquote code/c/src/algebra
_include_src_region := $(_include_main_region) -iquote code/c/src/region
_include_src_mesh := $(_include_main_mesh) -iquote code/c/src/mesh
_include_src_diffusion := $(_include_main_diffusion)\
  -iquote code/c/src/diffusion
_include_src_graphics := $(_include_main_graphics) -iquote code/c/src/graphics

################ include directories for compiling plugin files ################
_include_plugins_diffusion := $(_include_main_diffusion)
_include_plugins_animation := $(_include_main_graphics)\
  -iquote code/c/plugins/animation
_include_plugins_canvas := $(_include_main_graphics)\
  -iquote code/c/include/animation -iquote code/c/plugins/canvas

############################# library dependencies #############################
_libs_src_array := build/$(MODE)/lib/src/libarray$(.LIB)
_libs_src_algebra := build/$(MODE)/lib/src/libalgebra$(.LIB) $(_libs_src_array)
_libs_src_region := build/$(MODE)/lib/src/libregion$(.LIB) $(_libs_src_array)
_libs_src_mesh := build/$(MODE)/lib/src/libmesh$(.LIB)\
  build/$(MODE)/lib/src/libregion$(.LIB) $(_libs_src_algebra)
_libs_src_diffusion := build/$(MODE)/lib/src/libdiffusion$(.LIB)\
  $(_libs_src_mesh)
_libs_src_graphics := build/$(MODE)/lib/src/libgraphics$(.LIB) $(_libs_src_mesh)

############################# object file targets ##############################
.PHONY: obj obj_src obj_main obj_plugins
obj: obj_src obj_main obj_plugins

# object files from source files
.PHONY: $(patsubst %, obj_src_%, $(MODULES))
obj_src: $(patsubst %, obj_src_%, $(MODULES))
obj_src_array: $(_obj_src_array)
obj_src_algebra: $(_obj_src_algebra)
obj_src_region: $(_obj_src_region)
obj_src_mesh: $(_obj_src_mesh)
obj_src_diffusion: $(_obj_src_diffusion)
obj_src_graphics: $(_obj_src_graphics)


# object files from main files
.PHONY: $(patsubst %, obj_main_%, $(MODULES))
obj_main: $(patsubst %, obj_main_%, $(MODULES))
obj_main_array: $(_obj_main_array)
obj_main_algebra: $(_obj_main_algebra)
obj_main_region: $(_obj_main_region)
obj_main_mesh: $(_obj_main_mesh)
obj_main_diffusion: $(_obj_main_diffusion)
obj_main_graphics: $(_obj_main_graphics)

# object files from plugin files
.PHONY: $(patsubst %, obj_plugins_%, $(PLUGINS))
obj_plugins: $(patsubst %, obj_plugins_%, $(PLUGINS))
obj_plugins_diffusion: $(_obj_plugins_diffusion)
obj_plugins_animation: $(_obj_plugins_animation)
obj_plugins_canvas: $(_obj_plugins_canvas)

############################### library targets ################################
.PHONY: lib lib_src lib_plugins
lib: lib_src lib_plugins

# (static) libraries for source files
.PHONY: $(patsubst %, lib_src_%, $(MODULES))
lib_src: obj_src $(patsubst %, lib_src_%, $(MODULES))
lib_src_array: build/$(MODE)/lib/src/libarray$(.LIB)
lib_src_algebra: build/$(MODE)/lib/src/libalgebra$(.LIB)
lib_src_region: build/$(MODE)/lib/src/libregion$(.LIB)
lib_src_mesh: build/$(MODE)/lib/src/libmesh$(.LIB)
lib_src_diffusion: build/$(MODE)/lib/src/libdiffusion$(.LIB)
lib_src_graphics: build/$(MODE)/lib/src/libgraphics$(.LIB)

# dynamic libraries for plugins
.PHONY: $(patsubst %, lib_plugins_%, $(PLUGINS))
lib_plugins: obj_plugins $(patsubst %, lib_plugins_%, $(PLUGINS))
lib_plugins_diffusion: build/$(MODE)/lib/plugins/libdiffusion$(.DLL)
lib_plugins_animation: build/$(MODE)/lib/plugins/libanimation$(.DLL)
lib_plugins_canvas: build/$(MODE)/lib/plugins/libcanvas$(.DLL)

############################## executable targets ##############################
.PHONY: $(patsubst %, bin_%, $(MODULES))
bin: obj_main lib_src $(patsubst %, bin_%, $(MODULES))
bin_array: $(_bin_array)
bin_algebra: $(_bin_algebra)
bin_region: $(_bin_region)
bin_mesh: $(_bin_mesh)
bin_diffusion: $(_bin_diffusion)
bin_graphics: $(_bin_graphics)

#################### targets by modules -- called on demand ####################
.PHONY: $(MODULES) $(PLUGINS)
array: $(patsubst %, %_array, obj_src obj_main lib_src bin txt)
algebra: $(patsubst %, %_algebra, obj_src obj_main lib_src bin txt)
region: $(patsubst %, %_region, obj_src obj_main lib_src bin txt)
mesh: $(patsubst %, %_mesh, obj_src obj_main lib_src bin txt)
diffusion: $(patsubst %, %_diffusion, obj_src obj_main lib_src bin txt)
graphics: $(patsubst %, %_graphics, obj_src obj_main lib_src bin txt)

diffusion: obj_plugins_diffusion lib_plugins_diffusion
animation: obj_plugins_animation lib_plugins_animation
canvas: obj_plugins_canvas lib_plugins_canvas

######################### preprocessing and compiling ##########################
build/$(MODE)/obj: | build/$(MODE)
	mkdir -p $@

build/$(MODE)/dep: | build/$(MODE)
	mkdir -p $@

# compiling source files
build/$(MODE)/obj/src: | build/$(MODE)/obj
	mkdir -p $@

build/$(MODE)/dep/src: | build/$(MODE)/dep
	mkdir -p $@

# (1): object file
define dependencies
$(patsubst build/$(MODE)/obj/%$(.OBJ),build/$(MODE)/dep/%$(.DEP),$(1))
endef

# $(1): $@ (object file)
# $(2): $< (source file)
# $(3): headers
define compile
$(CC) -o $(1) $(CPPFLAGS) -MF $(call dependencies,$(1)) $(CFLAGS) $(3) -c $(2)
endef

$(_obj_src_array): build/$(MODE)/obj/src/%$(.OBJ): code/c/src/array/%.c\
  | build/$(MODE)/obj/src build/$(MODE)/dep/src
	$(call compile,$@,$<,$(_include_src_array))

$(_obj_src_algebra): build/$(MODE)/obj/src/%$(.OBJ): code/c/src/algebra/%.c\
    | build/$(MODE)/obj/src build/$(MODE)/dep/src
	$(call compile,$@,$<,$(_include_src_algebra))

$(_obj_src_region): build/$(MODE)/obj/src/%$(.OBJ): code/c/src/region/%.c\
    | build/$(MODE)/obj/src build/$(MODE)/dep/src
	$(call compile,$@,$<,$(_include_src_region))

$(_obj_src_mesh): build/$(MODE)/obj/src/%$(.OBJ): code/c/src/mesh/%.c\
    | build/$(MODE)/obj/src build/$(MODE)/dep/src
	$(call compile,$@,$<,$(_include_src_mesh))

$(_obj_src_diffusion): build/$(MODE)/obj/src/%$(.OBJ):\
  code/c/src/diffusion/%.c | build/$(MODE)/obj/src build/$(MODE)/dep/src
	$(call compile,$@,$<,$(_include_src_diffusion))

$(_obj_src_graphics): build/$(MODE)/obj/src/%$(.OBJ): code/c/src/graphics/%.c\
    | build/$(MODE)/obj/src build/$(MODE)/dep/src
	$(call compile,$@,$<,$(_include_src_graphics))

# include header dependencies for object files from code/c/src
-include build/$(MODE)/dep/src/*$(.DEP)

# compiling main files
build/$(MODE)/obj/main: | build/$(MODE)/obj
	mkdir -p $@

build/$(MODE)/dep/main: | build/$(MODE)/dep
	mkdir -p $@

$(_obj_main_array): build/$(MODE)/obj/main/%$(.OBJ): code/c/main/array/%.c\
  | build/$(MODE)/obj/main build/$(MODE)/dep/main
	$(call compile,$@,$<,$(_include_main_array))

$(_obj_main_algebra): build/$(MODE)/obj/main/%$(.OBJ):\
   code/c/main/algebra/%.c | build/$(MODE)/obj/main build/$(MODE)/dep/main
	$(call compile,$@,$<,$(_include_main_algebra))

$(_obj_main_region): build/$(MODE)/obj/main/%$(.OBJ):\
   code/c/main/region/%.c | build/$(MODE)/obj/main build/$(MODE)/dep/main
	$(call compile,$@,$<,$(_include_main_region))

$(_obj_main_graphics): build/$(MODE)/obj/main/%$(.OBJ):\
   code/c/main/graphics/%.c | build/$(MODE)/obj/main build/$(MODE)/dep/main
	$(call compile,$@,$<,$(_include_main_graphics))

$(_obj_main_mesh): build/$(MODE)/obj/main/%$(.OBJ): code/c/main/mesh/%.c\
  | build/$(MODE)/obj/main build/$(MODE)/dep/main
	$(call compile,$@,$<,$(_include_main_mesh))

$(_obj_main_diffusion): build/$(MODE)/obj/main/%$(.OBJ):\
  code/c/main/diffusion/%.c | build/$(MODE)/obj/main build/$(MODE)/dep/main
	$(call compile,$@,$<,$(_include_main_diffusion))

# include header dependencies for object files from code/c/main
-include build/$(MODE)/dep/main/*$(.DEP)

# compiling plugin files
build/$(MODE)/obj/plugins: | build/$(MODE)/obj
	mkdir -p $@

build/$(MODE)/dep/plugins: | build/$(MODE)/dep
	mkdir -p $@

$(_obj_plugins_diffusion): build/$(MODE)/obj/plugins/%$(.OBJ):\
  code/c/plugins/diffusion/%.c | build/$(MODE)/obj/plugins\
  build/$(MODE)/dep/plugins
	$(call compile,$@,$<,$(_include_plugins_diffusion))

$(_obj_plugins_animation): build/$(MODE)/obj/plugins/%$(.OBJ):\
  code/c/plugins/animation/%.c | build/$(MODE)/obj/plugins\
                                 build/$(MODE)/dep/plugins
	$(call compile,$@,$<,$(_include_plugins_animation)\
		             $(shell pkg-config --cflags gtk+-3.0))

$(_obj_plugins_canvas): build/$(MODE)/obj/plugins/%$(.OBJ):\
  code/c/plugins/canvas/%.c | build/$(MODE)/obj/plugins\
                              build/$(MODE)/dep/plugins
	$(call compile,$@,$<,$(_include_plugins_canvas) \
		             $(shell pkg-config --cflags cairo))

# include header dependencies for object files from code/c/plugins
-include build/$(MODE)/dep/plugins/*$(.DEP)

############################## creating libraries ##############################
build/$(MODE)/lib: | build/$(MODE)
	mkdir -p $@

# (static) libraries for source files
build/$(MODE)/lib/src: | build/$(MODE)/lib
	mkdir -p $@

ARFLAGS := rs

build/$(MODE)/lib/src/libarray$(.LIB): $(_obj_src_array) | build/$(MODE)/lib/src
	$(AR) $(ARFLAGS) $@ $^

build/$(MODE)/lib/src/libalgebra$(.LIB): $(_obj_src_algebra)\
  | build/$(MODE)/lib/src
	$(AR) $(ARFLAGS) $@ $^

build/$(MODE)/lib/src/libregion$(.LIB): $(_obj_src_region)\
  | build/$(MODE)/lib/src
	$(AR) $(ARFLAGS) $@ $^

build/$(MODE)/lib/src/libmesh$(.LIB): $(_obj_src_mesh) | build/$(MODE)/lib/src
	$(AR) $(ARFLAGS) $@ $^

build/$(MODE)/lib/src/libdiffusion$(.LIB): $(_obj_src_diffusion)\
  | build/$(MODE)/lib/src
	$(AR) $(ARFLAGS) $@ $^

build/$(MODE)/lib/src/libgraphics$(.LIB): $(_obj_src_graphics)\
  | build/$(MODE)/lib/src
	$(AR) $(ARFLAGS) $@ $^

# dynamic libraries for plugins
build/$(MODE)/lib/plugins: | build/$(MODE)/lib
	mkdir -p $@

build/$(MODE)/lib/plugins/libdiffusion$(.DLL): $(_obj_plugins_diffusion)\
  build/$(MODE)/obj/src/boundary_scalar_field_discretize$(.OBJ)\
  build/$(MODE)/obj/src/boundary_pseudoscalar_field_discretize$(.OBJ)\
  build/$(MODE)/obj/src/de_rham_0$(.OBJ)\
  build/$(MODE)/obj/src/de_rham_top_dimension$(.OBJ)\
  build/$(MODE)/obj/src/de_rham_2_hemisphere_polar_forman$(.OBJ)\
  build/$(MODE)/obj/src/de_rham_2_hemisphere_polar_forman_gauss_1$(.OBJ)\
  build/$(MODE)/obj/src/de_rham_2_hemisphere_polar_forman_gauss_2$(.OBJ)\
  build/$(MODE)/obj/src/de_rham_2_hemisphere_polar_forman_generic$(.OBJ)\
  build/$(MODE)/obj/src/de_rham_boundary_0$(.OBJ)\
  build/$(MODE)/obj/src/de_rham_nonzero$(.OBJ)\
  build/$(MODE)/obj/src/de_rham_sequence_0$(.OBJ)\
  build/$(MODE)/obj/src/cmc_rectangle_numerical_integration_average_value_gauss_1$(.OBJ)\
  build/$(MODE)/obj/src/cmc_rectangle_numerical_integration_average_value_gauss_2$(.OBJ)\
  build/$(MODE)/obj/src/int_array_total_sum$(.OBJ)\
  build/$(MODE)/obj/src/jagged1_free$(.OBJ)\
  build/$(MODE)/obj/src/jagged2_part1$(.OBJ)\
  build/$(MODE)/obj/src/jagged4_part2$(.OBJ)\
  build/$(MODE)/obj/src/mesh_cf_part2$(.OBJ)\
  build/$(MODE)/obj/src/mesh_boundary_hyperfaces_from_constraint$(.OBJ)\
  build/$(MODE)/obj/src/mesh_boundary_hyperfaces_from_constraint_1$(.OBJ)\
  build/$(MODE)/obj/src/polytope_coordinates_arithmetic_mean$(.OBJ)\
  build/$(MODE)/obj/src/unsigned_approximation_of_scalar_field_on_1_cells$(.OBJ)\
  build/$(MODE)/obj/src/unsigned_approximation_of_scalar_field_on_hyperfaces$(.OBJ)\
  | build/$(MODE)/lib/plugins
	$(CC) -o $@ -fPIC -shared $^ $(LDLIBS)

build/$(MODE)/lib/plugins/libanimation$(.DLL): $(_obj_plugins_animation)\
  build/$(MODE)/obj/src/cmc_error_message_position_in_code$(.OBJ)\
  | build/$(MODE)/lib/plugins
	$(CC) -o $@ -fPIC -shared $^\
	  $(shell pkg-config --libs gtk+-3.0) $(LDLIBS)

build/$(MODE)/lib/plugins/libcanvas$(.DLL): $(_obj_plugins_canvas)\
  build/$(MODE)/obj/src/cmc_rgb_allocate_color$(.OBJ)\
  build/$(MODE)/obj/src/cmc_rgb_check_color_scheme_rainbow$(.OBJ)\
  build/$(MODE)/obj/src/cmc_rgb_color_scheme_rainbow$(.OBJ)\
  build/$(MODE)/obj/src/cmc_rgb_set_from_scheme_rainbow$(.OBJ)\
  build/$(MODE)/obj/src/cmc_rgb_get_color_rgb$(.OBJ)\
  build/$(MODE)/obj/src/cmc_graphics_mesh_2d_0_cochain_sequence_draw_values$(.OBJ)\
  build/$(MODE)/obj/src/cmc_graphics_mesh_2d_1_cochain_sequence_draw_values$(.OBJ)\
  build/$(MODE)/obj/src/cmc_graphics_mesh_2d_1_cochain_sequence_draw_values_polar_forman$(.OBJ)\
  build/$(MODE)/obj/src/cmc_graphics_mesh_2d_skeleton_draw$(.OBJ)\
  build/$(MODE)/obj/src/cmc_graphics_mesh_2d_skeleton_draw_polar$(.OBJ)\
  build/$(MODE)/obj/src/cmc_graphics_mesh_2d_skeleton_draw_polar_forman$(.OBJ)\
  build/$(MODE)/obj/src/cmc_graphics_colorbar_draw_rectangles$(.OBJ)\
  build/$(MODE)/obj/src/line_2d_midpoint$(.OBJ)\
  build/$(MODE)/obj/src/line_2d_direction_90_degrees$(.OBJ)\
  build/$(MODE)/obj/src/line_2d_oriented_set_from_center_and_direction$(.OBJ)\
  build/$(MODE)/obj/src/line_2d_set_flow_rate_direction$(.OBJ)\
  build/$(MODE)/obj/src/vector_2d_norm$(.OBJ)\
  build/$(MODE)/obj/src/vector_2d_scalar_multiply$(.OBJ)\
  build/$(MODE)/obj/src/arc_2d_set_flow_rate_direction$(.OBJ)\
  build/$(MODE)/obj/src/mesh_cf_part2$(.OBJ)\
  build/$(MODE)/obj/src/jagged4_part2$(.OBJ)\
  build/$(MODE)/obj/src/int_array_total_sum$(.OBJ)\
  build/$(MODE)/obj/src/cmc_error_message_malloc$(.OBJ)\
  build/$(MODE)/obj/src/cmc_error_message_position_in_code$(.OBJ)\
  | build/$(MODE)/lib/plugins
	$(CC) -o $@ -fPIC -shared $^\
	  $(shell pkg-config --libs cairo) $(LDLIBS)

################################### linking ####################################
build/$(MODE)/bin: | build/$(MODE)
	mkdir -p $@

$(_bin_array): build/$(MODE)/bin/%$(.EXE): build/$(MODE)/obj/main/%$(.OBJ)\
  $(_libs_src_array) | build/$(MODE)/bin
	$(CC) -o $@ $< $(_libs_src_array) $(LDLIBS)

$(_bin_algebra): build/$(MODE)/bin/%$(.EXE): build/$(MODE)/obj/main/%$(.OBJ)\
  $(_libs_src_algebra) | build/$(MODE)/bin
	$(CC) -o $@ $< $(_libs_src_algebra) $(LDLIBS)

$(_bin_region): build/$(MODE)/bin/%$(.EXE): build/$(MODE)/obj/main/%$(.OBJ)\
  $(_libs_src_region) | build/$(MODE)/bin
	$(CC) -o $@ $< $(_libs_src_region) $(LDLIBS)

$(_bin_mesh): build/$(MODE)/bin/%$(.EXE): build/$(MODE)/obj/main/%$(.OBJ)\
  $(_libs_src_mesh) | build/$(MODE)/bin
	$(CC) -o $@ $< $(_libs_src_mesh) $(LDLIBS)

$(_bin_diffusion): build/$(MODE)/bin/%$(.EXE): build/$(MODE)/obj/main/%$(.OBJ)\
  $(_libs_src_diffusion) | build/$(MODE)/bin
	$(CC) -o $@ $< $(_libs_src_diffusion) $(LDLIBS)

$(_bin_graphics): build/$(MODE)/bin/%$(.EXE): build/$(MODE)/obj/main/%$(.OBJ)\
  $(_libs_src_graphics) | build/$(MODE)/bin
	$(CC) -o $@ $< $(_libs_src_graphics) $(LDLIBS)
