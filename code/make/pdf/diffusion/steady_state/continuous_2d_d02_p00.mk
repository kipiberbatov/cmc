.PHONY: pdf_diffusion_steady_state_continuous_2d_d02_p00\
        pdf_diffusion_steady_state_continuous_2d_d02_p00_clean\
        pdf_diffusion_steady_state_continuous_2d_d02_p00_distclean

build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d02_p00:\
  | build/$(MODE)/pdf/diffusion/steady_state
	mkdir -p $@

_pdf_diffusion_steady_state_continuous_2d_d02_p00 :=\
  build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d02_p00/exact_2d_10_grains_forman_potential.pdf\
  build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d02_p00/exact_2d_10_grains_forman_flow_rate.pdf\
  build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d02_p00/primal_strong_cochain_2d_10_grains_forman_potential.pdf\
  build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d02_p00/primal_strong_cochain_2d_10_grains_forman_flow_rate.pdf\
  build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_potential.pdf\
  build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_flow_rate.pdf\
  build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_potential.pdf\
  build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_flow_rate.pdf\

build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d02_p00/exact_2d_10_grains_forman_potential.pdf:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains/forman.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_2d_10_grains_forman_potential.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence_no_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_animation_pdf$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d02_p00\
    build/$(MODE)/lib/plugins/libcairo_graphics$(.DLL)\
    build/$(MODE)/lib/plugins/libcairo_animation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence_no_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_animation_pdf\
  --output=$@

build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d02_p00/exact_2d_10_grains_forman_flow_rate.pdf:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains/forman.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_2d_10_grains_forman_flow_rate.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_animation_pdf$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d02_p00\
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

build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d02_p00/primal_strong_cochain_2d_10_grains_forman_potential.pdf:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains/forman.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_strong_cochain_2d_10_grains_forman_potential.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence_no_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_animation_pdf$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d02_p00\
    build/$(MODE)/lib/plugins/libcairo_graphics$(.DLL)\
    build/$(MODE)/lib/plugins/libcairo_animation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence_no_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_animation_pdf\
  --output=$@

build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d02_p00/primal_strong_cochain_2d_10_grains_forman_flow_rate.pdf:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains/forman.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_strong_cochain_2d_10_grains_forman_flow_rate.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_animation_pdf$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d02_p00\
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

build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_potential.pdf:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains/forman.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_potential.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence_no_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_animation_pdf$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d02_p00\
    build/$(MODE)/lib/plugins/libcairo_graphics$(.DLL)\
    build/$(MODE)/lib/plugins/libcairo_animation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence_no_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_animation_pdf\
  --output=$@

build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_flow_rate.pdf:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains/forman.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_flow_rate.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_animation_pdf$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d02_p00\
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

build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_potential.pdf:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains/forman.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_potential.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence_no_skeleton$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_animation_pdf$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d02_p00\
    build/$(MODE)/lib/plugins/libcairo_graphics$(.DLL)\
    build/$(MODE)/lib/plugins/libcairo_animation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence_no_skeleton\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_animation_pdf\
  --output=$@

build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_flow_rate.pdf:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains/forman.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_solution.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_animation_pdf$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d02_p00\
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

pdf_diffusion_steady_state_continuous_2d_d02_p00:\
  $(_pdf_diffusion_steady_state_continuous_2d_d02_p00)

pdf_diffusion_steady_state_continuous_2d_d02_p00_clean:
	-$(RM) $(_pdf_diffusion_steady_state_continuous_2d_d02_p00)

pdf_diffusion_steady_state_continuous_2d_d02_p00_distclean:
	-$(RM) -r build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d02_p00
