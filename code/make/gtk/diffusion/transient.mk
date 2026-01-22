.PHONY: gtk_diffusion_transient\
        gtk_diffusion_transient_clean\
        gtk_diffusion_transient_distclean

build/$(MODE)/gtk/diffusion/transient: | build/$(MODE)/gtk/diffusion
	mkdir -p $@

include code/make/gtk/diffusion/transient/continuous_2d_d00_p00_brick_2d_2_forman.mk
include code/make/gtk/diffusion/transient/continuous_2d_d00_p01.mk
include code/make/gtk/diffusion/transient/continuous_2d_d00_p02.mk
include code/make/gtk/diffusion/transient/continuous_2d_d00_p03.mk
include code/make/gtk/diffusion/transient/continuous_2d_d00_p04.mk
include code/make/gtk/diffusion/transient/continuous_2d_d00_p05.mk
include code/make/gtk/diffusion/transient/continuous_2d_d01_p00.mk
include code/make/gtk/diffusion/transient/continuous_2d_d02_p00.mk
include code/make/gtk/diffusion/transient/continuous_2d_d02_p01.mk
include code/make/gtk/diffusion/transient/continuous_2d_d03_p00.mk
include code/make/gtk/diffusion/transient/continuous_2d_d03_p01.mk

_gtk_diffusion_transient :=\
  $(_gtk_diffusion_transient_continuous_2d_d00_p00_brick_2d_2_forman)\
  $(_gtk_diffusion_transient_continuous_2d_d00_p01)\
  $(_gtk_diffusion_transient_continuous_2d_d00_p02)\
  $(_gtk_diffusion_transient_continuous_2d_d00_p03)\
  $(_gtk_diffusion_transient_continuous_2d_d00_p04)\
  $(_gtk_diffusion_transient_continuous_2d_d00_p05)\
  $(_gtk_diffusion_transient_continuous_2d_d01_p00)\
  $(_gtk_diffusion_transient_continuous_2d_d02_p00)\
  $(_gtk_diffusion_transient_continuous_2d_d02_p01)\
  $(_gtk_diffusion_transient_continuous_2d_d03_p00)\
  $(_gtk_diffusion_transient_continuous_2d_d03_p01)\

gtk_diffusion_transient: $(_gtk_diffusion_transient)

gtk_diffusion_transient_clean:
	-$(RM) $(_gtk_diffusion_transient)

gtk_diffusion_transient_distclean:
	-$(RM) -r build/$(MODE)/gtk/diffusion/transient
