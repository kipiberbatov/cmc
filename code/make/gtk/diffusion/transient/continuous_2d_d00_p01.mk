.PHONY: gtk_diffusion_transient_continuous_2d_d00_p01\
        gtk_diffusion_transient_continuous_2d_d00_p01_clean\
        gtk_diffusion_transient_continuous_2d_d00_p01_distclean

build/$(MODE)/gtk/diffusion/transient/continuous_2d_d00_p01:\
  | build/$(MODE)/gtk/diffusion/transient
	mkdir -p $@

_gtk_diffusion_transient_continuous_2d_d00_p01 :=\
  build/$(MODE)/gtk/diffusion/transient/continuous_2d_d00_p01/primal_strong_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.log\
  build/$(MODE)/gtk/diffusion/transient/continuous_2d_d00_p01/primal_strong_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_flow_rate.log\
  build/$(MODE)/gtk/diffusion/transient/continuous_2d_d00_p01/primal_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.log\
  build/$(MODE)/gtk/diffusion/transient/continuous_2d_d00_p01/primal_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_flow_rate.log\
  build/$(MODE)/gtk/diffusion/transient/continuous_2d_d00_p01/mixed_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.log\
  build/$(MODE)/gtk/diffusion/transient/continuous_2d_d00_p01/mixed_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_flow_rate.log\

build/$(MODE)/gtk/diffusion/transient/continuous_2d_d00_p01/primal_strong_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.log:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_5/forman.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d00_p01/primal_strong_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_gtk_animation$(.OBJ)\
  | build/$(MODE)/gtk/diffusion/transient/continuous_2d_d00_p01\
    build/$(MODE)/lib/plugins/libcairo_graphics$(.DLL)\
    build/$(MODE)/lib/plugins/libgtk_animation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=2500\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_gtk_animation\
  --title=2d_d00_p01_primal_strong_brick_2d_5_forman_potential\
  --close-automatically=$(CLOSE_AUTOMATICALLY)\
  --timelapse=$(TIMELAPSE)\
  --output=$@

build/$(MODE)/gtk/diffusion/transient/continuous_2d_d00_p01/primal_strong_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_flow_rate.log:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_5/forman.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d00_p01/primal_strong_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_flow_rate.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_gtk_animation$(.OBJ)\
  | build/$(MODE)/gtk/diffusion/transient/continuous_2d_d00_p01\
    build/$(MODE)/lib/plugins/libcairo_graphics$(.DLL)\
    build/$(MODE)/lib/plugins/libgtk_animation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=2500\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_gtk_animation\
  --title=2d_d00_p01_primal_strong_brick_2d_5_forman_flow_rate\
  --close-automatically=$(CLOSE_AUTOMATICALLY)\
  --timelapse=$(TIMELAPSE)\
  --output=$@

build/$(MODE)/gtk/diffusion/transient/continuous_2d_d00_p01/primal_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.log:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_5/forman.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d00_p01/primal_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_gtk_animation$(.OBJ)\
  | build/$(MODE)/gtk/diffusion/transient/continuous_2d_d00_p01\
    build/$(MODE)/lib/plugins/libcairo_graphics$(.DLL)\
    build/$(MODE)/lib/plugins/libgtk_animation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=2500\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_gtk_animation\
  --title=2d_d00_p01_primal_weak_brick_2d_5_forman_potential\
  --close-automatically=$(CLOSE_AUTOMATICALLY)\
  --timelapse=$(TIMELAPSE)\
  --output=$@

build/$(MODE)/gtk/diffusion/transient/continuous_2d_d00_p01/primal_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_flow_rate.log:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_5/forman.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d00_p01/primal_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_flow_rate.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_gtk_animation$(.OBJ)\
  | build/$(MODE)/gtk/diffusion/transient/continuous_2d_d00_p01\
    build/$(MODE)/lib/plugins/libcairo_graphics$(.DLL)\
    build/$(MODE)/lib/plugins/libgtk_animation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=2500\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_gtk_animation\
  --title=2d_d00_p01_primal_weak_brick_2d_5_forman_flow_rate\
  --close-automatically=$(CLOSE_AUTOMATICALLY)\
  --timelapse=$(TIMELAPSE)\
  --output=$@

build/$(MODE)/gtk/diffusion/transient/continuous_2d_d00_p01/mixed_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.log:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_5/forman.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d00_p01/mixed_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_potential.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_gtk_animation$(.OBJ)\
  | build/$(MODE)/gtk/diffusion/transient/continuous_2d_d00_p01\
    build/$(MODE)/lib/plugins/libcairo_graphics$(.DLL)\
    build/$(MODE)/lib/plugins/libgtk_animation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=2500\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_gtk_animation\
  --title=2d_d00_p01_mixed_weak_brick_2d_5_forman_potential\
  --close-automatically=$(CLOSE_AUTOMATICALLY)\
  --timelapse=$(TIMELAPSE)\
  --output=$@

build/$(MODE)/gtk/diffusion/transient/continuous_2d_d00_p01/mixed_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_flow_rate.log:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_5/forman.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d00_p01/mixed_weak_cochain_brick_2d_5_forman_trapezoidal_0p001_2500_solution.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_gtk_animation$(.OBJ)\
  | build/$(MODE)/gtk/diffusion/transient/continuous_2d_d00_p01\
    build/$(MODE)/lib/plugins/libcairo_graphics$(.DLL)\
    build/$(MODE)/lib/plugins/libgtk_animation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=2500\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_gtk_animation\
  --title=2d_d00_p01_mixed_weak_brick_2d_5_forman_flow_rate\
  --close-automatically=$(CLOSE_AUTOMATICALLY)\
  --timelapse=$(TIMELAPSE)\
  --output=$@

gtk_diffusion_transient_continuous_2d_d00_p01:\
  $(_gtk_diffusion_transient_continuous_2d_d00_p01)

gtk_diffusion_transient_continuous_2d_d00_p01_clean:
	-$(RM) $(_gtk_diffusion_transient_continuous_2d_d00_p01)

gtk_diffusion_transient_continuous_2d_d00_p01_distclean:
	-$(RM) -r build/$(MODE)/gtk/diffusion/transient/continuous_2d_d00_p01
