.PHONY: pdf_diffusion_steady_state\
        pdf_diffusion_steady_state_clean\
        pdf_diffusion_steady_state_distclean

build/$(MODE)/pdf/diffusion/steady_state: | build/$(MODE)/pdf/diffusion
	mkdir -p $@

include code/make/pdf/diffusion/steady_state/continuous_2d_d00_p00.mk
include code/make/pdf/diffusion/steady_state/continuous_2d_d00_p01_brick_2d_2_forman.mk
include code/make/pdf/diffusion/steady_state/continuous_2d_d00_p02.mk
include code/make/pdf/diffusion/steady_state/continuous_2d_d00_p03_brick_2d_2_forman.mk
include code/make/pdf/diffusion/steady_state/continuous_2d_d00_p04.mk
include code/make/pdf/diffusion/steady_state/continuous_2d_d00_p05.mk
include code/make/pdf/diffusion/steady_state/continuous_2d_d01_p00.mk
include code/make/pdf/diffusion/steady_state/continuous_2d_d02_p00.mk
include code/make/pdf/diffusion/steady_state/continuous_2d_d02_p01.mk
include code/make/pdf/diffusion/steady_state/continuous_2d_d03_p00.mk
include code/make/pdf/diffusion/steady_state/continuous_2d_d03_p01.mk
include code/make/pdf/diffusion/steady_state/continuous_2d_d04_p00.mk
include code/make/pdf/diffusion/steady_state/continuous_2d_d04_p01.mk
include code/make/pdf/diffusion/steady_state/continuous_2d_d04_p02.mk
include code/make/pdf/diffusion/steady_state/continuous_2d_d04_p03.mk
include code/make/pdf/diffusion/steady_state/continuous_2d_parallelogram_20_15_degrees_45_p00.mk

_pdf_diffusion_steady_state :=\
  $(_pdf_diffusion_steady_state_continuous_2d_d00_p00)\
  $(_pdf_diffusion_steady_state_continuous_2d_d00_p01_brick_2d_2_forman)\
  $(_pdf_diffusion_steady_state_continuous_2d_d00_p02)\
  $(_pdf_diffusion_steady_state_continuous_2d_d00_p03_brick_2d_2_forman)\
  $(_pdf_diffusion_steady_state_continuous_2d_d00_p04)\
  $(_pdf_diffusion_steady_state_continuous_2d_d00_p05)\
  $(_pdf_diffusion_steady_state_continuous_2d_d01_p00)\
  $(_pdf_diffusion_steady_state_continuous_2d_d02_p00)\
  $(_pdf_diffusion_steady_state_continuous_2d_d02_p01)\
  $(_pdf_diffusion_steady_state_continuous_2d_d03_p00)\
  $(_pdf_diffusion_steady_state_continuous_2d_d03_p01)\
  $(_pdf_diffusion_steady_state_continuous_2d_d04_p00)\
  $(_pdf_diffusion_steady_state_continuous_2d_d04_p01)\
  $(_pdf_diffusion_steady_state_continuous_2d_d04_p02)\
  $(_pdf_diffusion_steady_state_continuous_2d_d04_p03)\
  $(_pdf_diffusion_steady_state_continuous_2d_parallelogram_20_15_degrees_45_p00)\

pdf_diffusion_steady_state: $(_pdf_diffusion_steady_state)

pdf_diffusion_steady_state_clean:
	-$(RM) $(_pdf_diffusion_steady_state)

pdf_diffusion_steady_state_distclean:
	-$(RM) -r build/$(MODE)/pdf/diffusion/steady_state
