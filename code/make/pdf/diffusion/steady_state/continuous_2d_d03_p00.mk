.PHONY: pdf_diffusion_steady_state_continuous_2d_d03_p00\
        pdf_diffusion_steady_state_continuous_2d_d03_p00_clean\
        pdf_diffusion_steady_state_continuous_2d_d03_p00_distclean

build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00:\
  | build/$(MODE)/pdf/diffusion/steady_state
	mkdir -p $@

_pdf_diffusion_steady_state_continuous_2d_d03_p00 :=\
  build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00/exact_disk_polar_4_3_forman_potential.pdf\
  build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00/exact_disk_polar_4_3_forman_flow_rate.pdf\
  build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00/primal_weak_cochain_disk_polar_4_3_forman_potential.pdf\
  build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00/primal_weak_cochain_disk_polar_4_3_forman_flow_rate.pdf\
  build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00/mixed_weak_cochain_disk_polar_4_3_forman_potential.pdf\
  build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00/mixed_weak_cochain_disk_polar_4_3_forman_flow_rate.pdf\
  build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00/exact_disk_polar_18_10_forman_potential.pdf\
  build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00/exact_disk_polar_18_10_forman_flow_rate.pdf\
  build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00/primal_weak_cochain_disk_polar_18_10_forman_potential.pdf\
  build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00/primal_weak_cochain_disk_polar_18_10_forman_flow_rate.pdf\
  build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00/mixed_weak_cochain_disk_polar_18_10_forman_potential.pdf\
  build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00/mixed_weak_cochain_disk_polar_18_10_forman_flow_rate.pdf\

build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00/exact_disk_polar_4_3_forman_potential.pdf:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_4_3_forman.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p00/exact_disk_polar_4_3_forman_potential.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence_polar_forman$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence_polar_forman\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_pdf_animation\
  --output=$@

build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00/exact_disk_polar_4_3_forman_flow_rate.pdf:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_4_3_forman.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p00/exact_disk_polar_4_3_forman_flow_rate.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence_polar_forman$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence_polar_forman\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_pdf_animation\
  --output=$@

build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00/primal_weak_cochain_disk_polar_4_3_forman_potential.pdf:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_4_3_forman.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p00/primal_weak_cochain_disk_polar_4_3_forman_potential.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence_polar_forman$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence_polar_forman\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_pdf_animation\
  --output=$@

build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00/primal_weak_cochain_disk_polar_4_3_forman_flow_rate.pdf:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_4_3_forman.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p00/primal_weak_cochain_disk_polar_4_3_forman_flow_rate.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence_polar_forman$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence_polar_forman\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_pdf_animation\
  --output=$@

build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00/mixed_weak_cochain_disk_polar_4_3_forman_potential.pdf:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_4_3_forman.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p00/mixed_weak_cochain_disk_polar_4_3_forman_potential.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence_polar_forman$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence_polar_forman\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_pdf_animation\
  --output=$@

build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00/mixed_weak_cochain_disk_polar_4_3_forman_flow_rate.pdf:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_4_3_forman.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p00/mixed_weak_cochain_disk_polar_4_3_forman_solution.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence_polar_forman$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence-format=--steady-state-mixed-weak-solution-flow-rate-raw\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence_polar_forman\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_pdf_animation\
  --output=$@

build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00/exact_disk_polar_18_10_forman_potential.pdf:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_18_10_forman.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p00/exact_disk_polar_18_10_forman_potential.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence_polar_forman$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence_polar_forman\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_pdf_animation\
  --output=$@

build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00/exact_disk_polar_18_10_forman_flow_rate.pdf:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_18_10_forman.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p00/exact_disk_polar_18_10_forman_flow_rate.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence_polar_forman$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence_polar_forman\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_pdf_animation\
  --output=$@

build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00/primal_weak_cochain_disk_polar_18_10_forman_potential.pdf:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_18_10_forman.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p00/primal_weak_cochain_disk_polar_18_10_forman_potential.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence_polar_forman$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence_polar_forman\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_pdf_animation\
  --output=$@

build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00/primal_weak_cochain_disk_polar_18_10_forman_flow_rate.pdf:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_18_10_forman.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p00/primal_weak_cochain_disk_polar_18_10_forman_flow_rate.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence_polar_forman$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence_polar_forman\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_pdf_animation\
  --output=$@

build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00/mixed_weak_cochain_disk_polar_18_10_forman_potential.pdf:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_18_10_forman.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p00/mixed_weak_cochain_disk_polar_18_10_forman_potential.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence_polar_forman$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence_polar_forman\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_pdf_animation\
  --output=$@

build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00/mixed_weak_cochain_disk_polar_18_10_forman_flow_rate.pdf:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_18_10_forman.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p00/mixed_weak_cochain_disk_polar_18_10_forman_solution.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence_polar_forman$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_pdf_animation$(.OBJ)\
  | build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=0\
  --cochain-sequence-format=--steady-state-mixed-weak-solution-flow-rate-raw\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence_polar_forman\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_pdf_animation\
  --output=$@

pdf_diffusion_steady_state_continuous_2d_d03_p00:\
  $(_pdf_diffusion_steady_state_continuous_2d_d03_p00)

pdf_diffusion_steady_state_continuous_2d_d03_p00_clean:
	-$(RM) $(_pdf_diffusion_steady_state_continuous_2d_d03_p00)

pdf_diffusion_steady_state_continuous_2d_d03_p00_distclean:
	-$(RM) -r build/$(MODE)/pdf/diffusion/steady_state/continuous_2d_d03_p00
