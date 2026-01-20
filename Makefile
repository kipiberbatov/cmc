################################ default target ################################
.PHONY: all
all: obj_src obj_main obj_plugins_diffusion\
     lib_src lib_plugins_diffusion\
     bin\
     txt

##################################### mode #####################################
MODE := release

########################## preparing build directory ###########################
build:
	mkdir -p $@

build/$(MODE): | build
	mkdir -p $@

############### generating object files, libraries and binaries ################
-include code/make/c_compile.mk

########################## preparing assets directory ##########################
assets/mesh: | assets
	mkdir -p $@

assets:
	mkdir -p $@

######################## running text-outputting demos #########################
-include code/make/txt.mk

######################### running PDF-outputting demos #########################
-include code/make/pdf.mk

######################### running SVG-outputting demos #########################
-include code/make/svg.mk

############################ running GTK animations ############################
-include code/make/gtk.mk

################### creating a PDF documentation using LaTeX ###################
-include code/make/docs.mk

############### creating a website linking to PDF documentation ################
-include code/make/website.mk

################################### cleaning ###################################
-include code/make/clean.mk

########################## removing built artifacts ############################
.PHONY: distclean
distclean:
	-$(RM) -r build
