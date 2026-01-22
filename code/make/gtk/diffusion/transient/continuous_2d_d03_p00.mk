.PHONY: gtk_diffusion_transient_continuous_2d_d03_p00\
        gtk_diffusion_transient_continuous_2d_d03_p00_clean\
        gtk_diffusion_transient_continuous_2d_d03_p00_distclean

build/$(MODE)/gtk/diffusion/transient/continuous_2d_d03_p00:\
  | build/$(MODE)/gtk/diffusion/transient
	mkdir -p $@

_gtk_diffusion_transient_continuous_2d_d03_p00 :=\
  build/$(MODE)/gtk/diffusion/transient/continuous_2d_d03_p00/primal_strong_cochain_disk_polar_4_3_forman_trapezoidal_0p05_1000_potential.log\
  build/$(MODE)/gtk/diffusion/transient/continuous_2d_d03_p00/primal_strong_cochain_disk_polar_4_3_forman_trapezoidal_0p05_1000_flow_rate.log\
  build/$(MODE)/gtk/diffusion/transient/continuous_2d_d03_p00/primal_weak_cochain_disk_polar_4_3_forman_trapezoidal_0p05_1000_potential.log\
  build/$(MODE)/gtk/diffusion/transient/continuous_2d_d03_p00/primal_weak_cochain_disk_polar_4_3_forman_trapezoidal_0p05_1000_flow_rate.log\
  build/$(MODE)/gtk/diffusion/transient/continuous_2d_d03_p00/mixed_weak_cochain_disk_polar_4_3_forman_trapezoidal_0p05_1000_potential.log\
  build/$(MODE)/gtk/diffusion/transient/continuous_2d_d03_p00/mixed_weak_cochain_disk_polar_4_3_forman_trapezoidal_0p05_1000_flow_rate.log\

build/$(MODE)/gtk/diffusion/transient/continuous_2d_d03_p00/primal_strong_cochain_disk_polar_4_3_forman_trapezoidal_0p05_1000_potential.log:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_4_3/forman.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d03_p00/primal_strong_cochain_disk_polar_4_3_forman_trapezoidal_0p05_1000_potential.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence_polar_forman$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_gtk_animation$(.OBJ)\
  | build/$(MODE)/gtk/diffusion/transient/continuous_2d_d03_p00\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=1000\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence_polar_forman\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_gtk_animation\
  --title=2d_d03_p00_primal_strong_disk_polar_4_3_forman_potential\
  --close-automatically=$(CLOSE_AUTOMATICALLY)\
  --timelapse=$(TIMELAPSE)\
  --output=$@

build/$(MODE)/gtk/diffusion/transient/continuous_2d_d03_p00/primal_strong_cochain_disk_polar_4_3_forman_trapezoidal_0p05_1000_flow_rate.log:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_4_3/forman.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d03_p00/primal_strong_cochain_disk_polar_4_3_forman_trapezoidal_0p05_1000_flow_rate.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence_polar_forman$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_gtk_animation$(.OBJ)\
  | build/$(MODE)/gtk/diffusion/transient/continuous_2d_d03_p00\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=1000\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence_polar_forman\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_gtk_animation\
  --title=2d_d03_p00_primal_strong_disk_polar_4_3_forman_flow_rate\
  --close-automatically=$(CLOSE_AUTOMATICALLY)\
  --timelapse=$(TIMELAPSE)\
  --output=$@

build/$(MODE)/gtk/diffusion/transient/continuous_2d_d03_p00/primal_weak_cochain_disk_polar_4_3_forman_trapezoidal_0p05_1000_potential.log:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_4_3/forman.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d03_p00/primal_weak_cochain_disk_polar_4_3_forman_trapezoidal_0p05_1000_potential.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence_polar_forman$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_gtk_animation$(.OBJ)\
  | build/$(MODE)/gtk/diffusion/transient/continuous_2d_d03_p00\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=1000\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence_polar_forman\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_gtk_animation\
  --title=2d_d03_p00_primal_weak_disk_polar_4_3_forman_potential\
  --close-automatically=$(CLOSE_AUTOMATICALLY)\
  --timelapse=$(TIMELAPSE)\
  --output=$@

build/$(MODE)/gtk/diffusion/transient/continuous_2d_d03_p00/primal_weak_cochain_disk_polar_4_3_forman_trapezoidal_0p05_1000_flow_rate.log:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_4_3/forman.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d03_p00/primal_weak_cochain_disk_polar_4_3_forman_trapezoidal_0p05_1000_flow_rate.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence_polar_forman$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_gtk_animation$(.OBJ)\
  | build/$(MODE)/gtk/diffusion/transient/continuous_2d_d03_p00\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=1000\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence_polar_forman\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_gtk_animation\
  --title=2d_d03_p00_primal_weak_disk_polar_4_3_forman_flow_rate\
  --close-automatically=$(CLOSE_AUTOMATICALLY)\
  --timelapse=$(TIMELAPSE)\
  --output=$@

build/$(MODE)/gtk/diffusion/transient/continuous_2d_d03_p00/mixed_weak_cochain_disk_polar_4_3_forman_trapezoidal_0p05_1000_potential.log:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_0_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_4_3/forman.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d03_p00/mixed_weak_cochain_disk_polar_4_3_forman_trapezoidal_0p05_1000_potential.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence_polar_forman$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_gtk_animation$(.OBJ)\
  | build/$(MODE)/gtk/diffusion/transient/continuous_2d_d03_p00\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=1000\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_0_cochain_sequence_polar_forman\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_gtk_animation\
  --title=2d_d03_p00_mixed_weak_disk_polar_4_3_forman_potential\
  --close-automatically=$(CLOSE_AUTOMATICALLY)\
  --timelapse=$(TIMELAPSE)\
  --output=$@

build/$(MODE)/gtk/diffusion/transient/continuous_2d_d03_p00/mixed_weak_cochain_disk_polar_4_3_forman_trapezoidal_0p05_1000_flow_rate.log:\
  build/$(MODE)/bin/cmc_graphics_mesh_2d_1_cochain_sequence$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_4_3/forman.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d03_p00/mixed_weak_cochain_disk_polar_4_3_forman_trapezoidal_0p05_1000_solution.txt\
  build/$(MODE)/obj/plugins/cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence_polar_forman$(.OBJ)\
  build/$(MODE)/obj/plugins/cmc_cairo_gtk_animation$(.OBJ)\
  | build/$(MODE)/gtk/diffusion/transient/continuous_2d_d03_p00\
    build/$(MODE)/lib/plugins/libcanvas$(.DLL)\
    build/$(MODE)/lib/plugins/libanimation$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --number-of-time-steps=1000\
  --cochain-sequence=$(word 3, $^)\
  --canvas-library=$(word 2, $|)\
  --canvas-backend=cmc_cairo_graphics_draw_functions_mesh_2d_1_cochain_sequence_polar_forman\
  --animation-library=$(word 3, $|)\
  --animation-backend=cmc_cairo_gtk_animation\
  --title=2d_d03_p00_mixed_weak_disk_polar_4_3_forman_flow_rate\
  --close-automatically=$(CLOSE_AUTOMATICALLY)\
  --timelapse=$(TIMELAPSE)\
  --output=$@

gtk_diffusion_transient_continuous_2d_d03_p00:\
  $(_gtk_diffusion_transient_continuous_2d_d03_p00)

gtk_diffusion_transient_continuous_2d_d03_p00_clean:
	-$(RM) $(_gtk_diffusion_transient_continuous_2d_d03_p00)

gtk_diffusion_transient_continuous_2d_d03_p00_distclean:
	-$(RM) -r build/$(MODE)/gtk/diffusion/transient/continuous_2d_d03_p00
