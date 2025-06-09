.PHONY: txt_diffusion_steady_state_continuous_2d_parallelogram_20_15_degrees_45_p00\
        txt_diffusion_steady_state_continuous_2d_parallelogram_20_15_degrees_45_p00_clean\
        txt_diffusion_steady_state_continuous_2d_parallelogram_20_15_degrees_45_p00_distclean

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_parallelogram_20_15_degrees_45_p00:\
  | build/$(MODE)/txt/diffusion/steady_state
	mkdir -p $@

_txt_diffusion_steady_state_continuous_2d_parallelogram_20_15_degrees_45_p00 :=\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_parallelogram_20_15_degrees_45_p00/exact_grid_5_3_forman_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_parallelogram_20_15_degrees_45_p00/exact_grid_5_3_forman_flow_rate.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_parallelogram_20_15_degrees_45_p00/cochain_grid_5_3_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_parallelogram_20_15_degrees_45_p00/primal_weak_cochain_grid_5_3_forman_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_parallelogram_20_15_degrees_45_p00/primal_weak_cochain_grid_5_3_forman_flow_rate.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_parallelogram_20_15_degrees_45_p00/mixed_weak_cochain_grid_5_3_forman_solution.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_parallelogram_20_15_degrees_45_p00/mixed_weak_cochain_grid_5_3_forman_potential.txt\

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_parallelogram_20_15_degrees_45_p00/exact_grid_5_3_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_exact_potential$(.EXE)\
  build/$(MODE)/txt/mesh/parallelogram_20_15_degrees_45_grid_5_3_forman.txt\
  build/$(MODE)/obj/plugins/diffusion_steady_state_continuous_2d_parallelogram_20_15_degrees_45_p00$(.OBJ)\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_parallelogram_20_15_degrees_45_p00\
    build/$(MODE)/lib/plugins/libdiffusion$(.DLL)
	$<\
  --raw $(word 2, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_parallelogram_20_15_degrees_45_p00_potential\
  --raw > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_parallelogram_20_15_degrees_45_p00/exact_grid_5_3_forman_flow_rate.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_exact_flow_rate$(.EXE)\
  build/$(MODE)/txt/mesh/parallelogram_20_15_degrees_45_grid_5_3_forman.txt\
  build/$(MODE)/obj/plugins/diffusion_steady_state_continuous_2d_parallelogram_20_15_degrees_45_p00$(.OBJ)\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_parallelogram_20_15_degrees_45_p00\
    build/$(MODE)/lib/plugins/libdiffusion$(.DLL)
	$<\
  --raw $(word 2, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_parallelogram_20_15_degrees_45_p00_flow_rate\
  --raw > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_parallelogram_20_15_degrees_45_p00/cochain_grid_5_3_forman_input.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_from_continuous$(.EXE)\
  build/$(MODE)/txt/mesh/parallelogram_20_15_degrees_45_grid_5_3_forman.txt\
  build/$(MODE)/txt/mesh/parallelogram_20_15_degrees_45_grid_5_3_forman_vol.txt\
  build/$(MODE)/obj/plugins/diffusion_steady_state_continuous_2d_parallelogram_20_15_degrees_45_p00$(.OBJ)\
  build/$(MODE)/obj/plugins/diffusion_steady_state_discrete_pre_processing_standard$(.OBJ)\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_parallelogram_20_15_degrees_45_p00\
    build/$(MODE)/lib/plugins/libdiffusion$(.DLL)
	$<\
  --mesh=$(word 2, $^)\
  --mesh-measures=$(word 3, $^)\
  --dynamic-library=$(word 2, $|)\
  --data=diffusion_steady_state_continuous_2d_parallelogram_20_15_degrees_45_p00\
  --pre-processing=diffusion_steady_state_discrete_pre_processing_standard\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_parallelogram_20_15_degrees_45_p00/primal_weak_cochain_grid_5_3_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_weak_solve_1$(.EXE)\
  build/$(MODE)/txt/mesh/parallelogram_20_15_degrees_45_grid_5_3_forman.txt\
  build/$(MODE)/txt/mesh/parallelogram_20_15_degrees_45_grid_5_3_forman_inner.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_parallelogram_20_15_degrees_45_p00/cochain_grid_5_3_forman_input.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_parallelogram_20_15_degrees_45_p00
	$<\
  --mesh=$(word 2, $^)\
  --mesh-inner=$(word 3, $^)\
  --data=$(word 4, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_parallelogram_20_15_degrees_45_p00/primal_weak_cochain_grid_5_3_forman_flow_rate.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_flow_rate_from_potential_1$(.EXE)\
  build/$(MODE)/txt/mesh/parallelogram_20_15_degrees_45_grid_5_3_forman.txt\
  build/$(MODE)/txt/mesh/parallelogram_20_15_degrees_45_grid_5_3_forman_hodge.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_parallelogram_20_15_degrees_45_p00/cochain_grid_5_3_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_parallelogram_20_15_degrees_45_p00/primal_weak_cochain_grid_5_3_forman_potential.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_parallelogram_20_15_degrees_45_p00
	$<\
  --mesh=$(word 2, $^)\
  --hodge-star=$(word 3, $^)\
  --dual-conductivity=$(word 4, $^)\
  --potential=$(word 5, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_parallelogram_20_15_degrees_45_p00/mixed_weak_cochain_grid_5_3_forman_solution.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_solve_1$(.EXE)\
  build/$(MODE)/txt/mesh/parallelogram_20_15_degrees_45_grid_5_3_forman.txt\
  build/$(MODE)/txt/mesh/parallelogram_20_15_degrees_45_grid_5_3_forman_inner.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_parallelogram_20_15_degrees_45_p00/cochain_grid_5_3_forman_input.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_parallelogram_20_15_degrees_45_p00
	$<\
  --mesh=$(word 2, $^)\
  --mesh-inner=$(word 3, $^)\
  --data=$(word 4, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_parallelogram_20_15_degrees_45_p00/mixed_weak_cochain_grid_5_3_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_potential_1$(.EXE)\
  build/$(MODE)/txt/mesh/parallelogram_20_15_degrees_45_grid_5_3_forman.txt\
  build/$(MODE)/txt/mesh/parallelogram_20_15_degrees_45_grid_5_3_forman_vol.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_parallelogram_20_15_degrees_45_p00/cochain_grid_5_3_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_parallelogram_20_15_degrees_45_p00/mixed_weak_cochain_grid_5_3_forman_solution.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_parallelogram_20_15_degrees_45_p00
	$<\
  --mesh=$(word 2, $^)\
  --mesh-measures=$(word 3, $^)\
  --data=$(word 4, $^)\
  --solution=$(word 5, $^)\
  --output=$@

txt_diffusion_steady_state_continuous_2d_parallelogram_20_15_degrees_45_p00:\
  $(_txt_diffusion_steady_state_continuous_2d_parallelogram_20_15_degrees_45_p00)

txt_diffusion_steady_state_continuous_2d_parallelogram_20_15_degrees_45_p00_clean:
	-$(RM) $(_txt_diffusion_steady_state_continuous_2d_parallelogram_20_15_degrees_45_p00)

txt_diffusion_steady_state_continuous_2d_parallelogram_20_15_degrees_45_p00_distclean:
	-$(RM) -r build/$(MODE)/txt/diffusion/steady_state/continuous_2d_parallelogram_20_15_degrees_45_p00
