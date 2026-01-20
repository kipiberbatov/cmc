.PHONY: txt_diffusion_steady_state\
        txt_diffusion_steady_state_clean\
        txt_diffusion_steady_state_distclean

build/$(MODE)/txt/diffusion/steady_state: | build/$(MODE)/txt/diffusion
	mkdir -p $@

include code/make/txt/diffusion/steady_state/continuous_2d_d00_p00.mk
include code/make/txt/diffusion/steady_state/continuous_2d_d00_p01.mk
include code/make/txt/diffusion/steady_state/continuous_2d_d00_p02.mk
include code/make/txt/diffusion/steady_state/continuous_2d_d00_p03.mk
include code/make/txt/diffusion/steady_state/continuous_2d_d00_p04.mk
include code/make/txt/diffusion/steady_state/continuous_2d_d00_p05.mk
include code/make/txt/diffusion/steady_state/continuous_2d_d01_p00.mk
include code/make/txt/diffusion/steady_state/continuous_2d_d02_p00.mk
include code/make/txt/diffusion/steady_state/continuous_2d_d02_p01.mk
include code/make/txt/diffusion/steady_state/continuous_2d_d03_p00.mk
include code/make/txt/diffusion/steady_state/continuous_2d_d03_p01.mk
include code/make/txt/diffusion/steady_state/continuous_2d_d04_p00.mk
include code/make/txt/diffusion/steady_state/continuous_2d_d04_p01.mk
include code/make/txt/diffusion/steady_state/continuous_2d_d04_p02.mk
include code/make/txt/diffusion/steady_state/continuous_2d_d04_p03.mk
include code/make/txt/diffusion/steady_state/continuous_2d_parallelogram_20_15_degrees_45_p00.mk
include code/make/txt/diffusion/steady_state/continuous_3d_d00_p00.mk
include code/make/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman.mk
include code/make/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_100_grains_forman.mk
include code/make/txt/diffusion/steady_state/continuous_3d_d00_p01.mk
include code/make/txt/diffusion/steady_state/continuous_3d_cube_3654_p00.mk

_txt_diffusion_steady_state :=\
  $(_txt_diffusion_steady_state_continuous_2d_d00_p00)\
  $(_txt_diffusion_steady_state_continuous_2d_d00_p01)\
  $(_txt_diffusion_steady_state_continuous_2d_d00_p02)\
  $(_txt_diffusion_steady_state_continuous_2d_d00_p03)\
  $(_txt_diffusion_steady_state_continuous_2d_d00_p04)\
  $(_txt_diffusion_steady_state_continuous_2d_d00_p05)\
  $(_txt_diffusion_steady_state_continuous_2d_d01_p00)\
  $(_txt_diffusion_steady_state_continuous_2d_d02_p00)\
  $(_txt_diffusion_steady_state_continuous_2d_d02_p01)\
  $(_txt_diffusion_steady_state_continuous_2d_d03_p00)\
  $(_txt_diffusion_steady_state_continuous_2d_d03_p01)\
  $(_txt_diffusion_steady_state_continuous_2d_d04_p00)\
  $(_txt_diffusion_steady_state_continuous_2d_d04_p01)\
  $(_txt_diffusion_steady_state_continuous_2d_d04_p02)\
  $(_txt_diffusion_steady_state_continuous_2d_d04_p03)\
  $(_txt_diffusion_steady_state_continuous_2d_parallelogram_20_15_degrees_45_p00)\
  $(_txt_diffusion_steady_state_continuous_3d_d00_p00)\
  $(_txt_diffusion_steady_state_continuous_3d_d00_p00_3d_10_grains_forman)\
  $(_txt_diffusion_steady_state_continuous_3d_d00_p00_3d_100_grains_forman)\
  $(_txt_diffusion_steady_state_continuous_3d_d00_p01)\
  $(_txt_diffusion_steady_state_continuous_3d_cube_3654_p00)\

txt_diffusion_steady_state: $(_txt_diffusion_steady_state)

txt_diffusion_steady_state_clean:
	-$(RM) $(_txt_diffusion_steady_state)

txt_diffusion_steady_state_distclean:
	-$(RM) -r build/$(MODE)/txt/diffusion/steady_state
