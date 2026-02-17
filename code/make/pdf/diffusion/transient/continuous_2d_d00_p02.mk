.PHONY: pdf_diffusion_transient_continuous_2d_d00_p02\
        pdf_diffusion_transient_continuous_2d_d00_p02_clean\
        pdf_diffusion_transient_continuous_2d_d00_p02_distclean

build/$(MODE)/pdf/diffusion/transient/continuous_2d_d00_p02:\
  | build/$(MODE)/pdf/diffusion/transient
	mkdir -p $@

_pdf_diffusion_transient_continuous_2d_d00_p02 :=\
  build/$(MODE)/pdf/diffusion/transient/continuous_2d_d00_p02/primal_strong_cochain_brick_2d_5_forman_trapezoidal_0p001_1000_potential.pdf\
  build/$(MODE)/pdf/diffusion/transient/continuous_2d_d00_p02/primal_strong_cochain_brick_2d_5_forman_trapezoidal_0p001_1000_flow_rate.pdf\
  build/$(MODE)/pdf/diffusion/transient/continuous_2d_d00_p02/primal_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_1000_potential.pdf\
  build/$(MODE)/pdf/diffusion/transient/continuous_2d_d00_p02/primal_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_1000_flow_rate.pdf\
  build/$(MODE)/pdf/diffusion/transient/continuous_2d_d00_p02/mixed_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_1000_potential.pdf\
  build/$(MODE)/pdf/diffusion/transient/continuous_2d_d00_p02/mixed_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_1000_flow_rate.pdf\

build/$(MODE)/pdf/diffusion/transient/continuous_2d_d00_p02/primal_strong_cochain_brick_2d_5_forman_trapezoidal_0p001_1000_potential.pdf:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_5/forman.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d00_p02/primal_strong_cochain_brick_2d_5_forman_trapezoidal_0p001_1000_potential.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_animation_pdf$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/transient/continuous_2d_d00_p02\
    build/$(MODE)/lib/plugins/libcairo_graphics$(.DLL)\
    build/$(MODE)/lib/plugins/libcairo_animation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=1000\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_animation_pdf\
  --output=$@

build/$(MODE)/pdf/diffusion/transient/continuous_2d_d00_p02/primal_strong_cochain_brick_2d_5_forman_trapezoidal_0p001_1000_flow_rate.pdf:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_5/forman.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d00_p02/primal_strong_cochain_brick_2d_5_forman_trapezoidal_0p001_1000_flow_rate.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_animation_pdf$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/transient/continuous_2d_d00_p02\
    build/$(MODE)/lib/plugins/libcairo_graphics$(.DLL)\
    build/$(MODE)/lib/plugins/libcairo_animation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=1000\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_animation_pdf\
  --output=$@

build/$(MODE)/pdf/diffusion/transient/continuous_2d_d00_p02/primal_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_1000_potential.pdf:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_5/forman.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d00_p02/primal_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_1000_potential.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_animation_pdf$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/transient/continuous_2d_d00_p02\
    build/$(MODE)/lib/plugins/libcairo_graphics$(.DLL)\
    build/$(MODE)/lib/plugins/libcairo_animation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=1000\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_animation_pdf\
  --output=$@

build/$(MODE)/pdf/diffusion/transient/continuous_2d_d00_p02/primal_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_1000_flow_rate.pdf:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_5/forman.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d00_p02/primal_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_1000_flow_rate.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_animation_pdf$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/transient/continuous_2d_d00_p02\
    build/$(MODE)/lib/plugins/libcairo_graphics$(.DLL)\
    build/$(MODE)/lib/plugins/libcairo_animation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=1000\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_animation_pdf\
  --output=$@

build/$(MODE)/pdf/diffusion/transient/continuous_2d_d00_p02/mixed_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_1000_potential.pdf:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_5/forman.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d00_p02/mixed_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_1000_potential.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_animation_pdf$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/transient/continuous_2d_d00_p02\
    build/$(MODE)/lib/plugins/libcairo_graphics$(.DLL)\
    build/$(MODE)/lib/plugins/libcairo_animation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=1000\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_animation_pdf\
  --output=$@

build/$(MODE)/pdf/diffusion/transient/continuous_2d_d00_p02/mixed_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_1000_flow_rate.pdf:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_5/forman.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d00_p02/mixed_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_1000_solution.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_animation_pdf$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/transient/continuous_2d_d00_p02\
    build/$(MODE)/lib/plugins/libcairo_graphics$(.DLL)\
    build/$(MODE)/lib/plugins/libcairo_animation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=1000\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_animation_pdf\
  --output=$@

pdf_diffusion_transient_continuous_2d_d00_p02:\
  $(_pdf_diffusion_transient_continuous_2d_d00_p02)

pdf_diffusion_transient_continuous_2d_d00_p02_clean:
	-$(RM) $(_pdf_diffusion_transient_continuous_2d_d00_p02)

pdf_diffusion_transient_continuous_2d_d00_p02_distclean:
	-$(RM) -r build/$(MODE)/pdf/diffusion/transient/continuous_2d_d00_p02
