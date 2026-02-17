.PHONY: pdf_diffusion_steady_state_continuous_2d_d00_p01\
        pdf_diffusion_steady_state_continuous_2d_d00_p01_brick_2d_2_forman_clean\
        pdf_diffusion_steady_state_continuous_2d_d00_p01_brick_2d_2_forman_distclean

build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d00_p01_brick_2d_2_forman:\
  | build/$(MODE)/pdf/diffusion/steady_state
	mkdir -p $@

_pdf_diffusion_steady_state_continuous_2d_d00_p01_brick_2d_2_forman :=\
  build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d00_p01_brick_2d_2_forman/exact_potential.pdf\
  build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d00_p01_brick_2d_2_forman/exact_flow_rate.pdf\
  build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d00_p01_brick_2d_2_forman/primal_strong_cochain_potential.pdf\
  build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d00_p01_brick_2d_2_forman/primal_strong_cochain_flow_rate.pdf\
  build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d00_p01_brick_2d_2_forman/primal_weak_cochain_potential.pdf\
  build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d00_p01_brick_2d_2_forman/primal_weak_cochain_flow_rate.pdf\
  build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d00_p01_brick_2d_2_forman/mixed_weak_cochain_potential.pdf\
  build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d00_p01_brick_2d_2_forman/mixed_weak_cochain_flow_rate.pdf\

build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d00_p01_brick_2d_2_forman/exact_potential.pdf:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2/forman.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p01_brick_2d_2_forman/exact_potential.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_animation_pdf$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d00_p01_brick_2d_2_forman\
    build/$(MODE)/lib/plugins/libcairo_graphics$(.DLL)\
    build/$(MODE)/lib/plugins/libcairo_animation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_animation_pdf\
  --output=$@

build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d00_p01_brick_2d_2_forman/exact_flow_rate.pdf:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2/forman.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p01_brick_2d_2_forman/exact_flow_rate.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_animation_pdf$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d00_p01_brick_2d_2_forman\
    build/$(MODE)/lib/plugins/libcairo_graphics$(.DLL)\
    build/$(MODE)/lib/plugins/libcairo_animation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_animation_pdf\
  --output=$@

build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d00_p01_brick_2d_2_forman/primal_strong_cochain_potential.pdf:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2/forman.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p01_brick_2d_2_forman/primal_strong_cochain_potential.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_animation_pdf$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d00_p01_brick_2d_2_forman\
    build/$(MODE)/lib/plugins/libcairo_graphics$(.DLL)\
    build/$(MODE)/lib/plugins/libcairo_animation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_animation_pdf\
  --output=$@

build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d00_p01_brick_2d_2_forman/primal_strong_cochain_flow_rate.pdf:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2/forman.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p01_brick_2d_2_forman/primal_strong_cochain_flow_rate.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_animation_pdf$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d00_p01_brick_2d_2_forman\
    build/$(MODE)/lib/plugins/libcairo_graphics$(.DLL)\
    build/$(MODE)/lib/plugins/libcairo_animation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_animation_pdf\
  --output=$@

build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d00_p01_brick_2d_2_forman/primal_weak_cochain_potential.pdf:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2/forman.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p01_brick_2d_2_forman/primal_weak_cochain_potential.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_animation_pdf$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d00_p01_brick_2d_2_forman\
    build/$(MODE)/lib/plugins/libcairo_graphics$(.DLL)\
    build/$(MODE)/lib/plugins/libcairo_animation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_animation_pdf\
  --output=$@

build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d00_p01_brick_2d_2_forman/primal_weak_cochain_flow_rate.pdf:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2/forman.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p01_brick_2d_2_forman/primal_weak_cochain_flow_rate.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_animation_pdf$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d00_p01_brick_2d_2_forman\
    build/$(MODE)/lib/plugins/libcairo_graphics$(.DLL)\
    build/$(MODE)/lib/plugins/libcairo_animation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_animation_pdf\
  --output=$@

build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d00_p01_brick_2d_2_forman/mixed_weak_cochain_potential.pdf:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2/forman.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p01_brick_2d_2_forman/mixed_weak_cochain_potential.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_animation_pdf$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d00_p01_brick_2d_2_forman\
    build/$(MODE)/lib/plugins/libcairo_graphics$(.DLL)\
    build/$(MODE)/lib/plugins/libcairo_animation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_animation_pdf\
  --output=$@

build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d00_p01_brick_2d_2_forman/mixed_weak_cochain_flow_rate.pdf:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2/forman.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p01_brick_2d_2_forman/mixed_weak_cochain_solution.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_animation_pdf$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d00_p01_brick_2d_2_forman\
    build/$(MODE)/lib/plugins/libcairo_graphics$(.DLL)\
    build/$(MODE)/lib/plugins/libcairo_animation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence-format=--steady-state-mixed-weak-solution-flow-rate-raw\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_animation_pdf\
  --output=$@

pdf_diffusion_steady_state_continuous_2d_d00_p01:\
  $(_pdf_diffusion_steady_state_continuous_2d_d00_p01_brick_2d_2_forman)

pdf_diffusion_steady_state_continuous_2d_d00_p01_brick_2d_2_forman_clean:
	-$(RM) $(_pdf_diffusion_steady_state_continuous_2d_d00_p01_brick_2d_2_forman)

pdf_diffusion_steady_state_continuous_2d_d00_p01_brick_2d_2_forman_distclean:
	-$(RM) -r build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d00_p01_brick_2d_2_forman
