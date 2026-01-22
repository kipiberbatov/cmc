.PHONY: txt_diffusion_steady_state_continuous_2d_d02_p00\
        txt_diffusion_steady_state_continuous_2d_d02_p00_clean\
        txt_diffusion_steady_state_continuous_2d_d02_p00_distclean

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00:\
  | build/$(MODE)/txt/diffusion/steady_state
	mkdir -p $@

_txt_diffusion_steady_state_continuous_2d_d02_p00 :=\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_2d_10_grains_forman_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_2d_10_grains_forman_flow_rate.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_2d_10_grains_forman_potential_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_2d_10_grains_forman_flow_rate_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_strong_cochain_2d_10_grains_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_strong_cochain_2d_10_grains_forman_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_strong_cochain_2d_10_grains_forman_flow_rate.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_flow_rate.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_potential_difference_with_exact.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_flow_rate_difference_with_exact.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_potential_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_flow_rate_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_potential_relative_error_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_flow_rate_relative_error_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_solution.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_potential_difference_with_exact.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_flow_rate_difference_with_exact.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_potential_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_flow_rate_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_potential_relative_error_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_flow_rate_relative_error_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_rectangle_20_15_brick_5_3_forman_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_rectangle_20_15_brick_5_3_forman_flow_rate.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_rectangle_20_15_brick_5_3_forman_potential_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_rectangle_20_15_brick_5_3_forman_flow_rate_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_strong_cochain_rectangle_20_15_brick_5_3_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_strong_cochain_rectangle_20_15_brick_5_3_forman_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_strong_cochain_rectangle_20_15_brick_5_3_forman_flow_rate.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_rectangle_20_15_brick_5_3_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_rectangle_20_15_brick_5_3_forman_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_rectangle_20_15_brick_5_3_forman_flow_rate.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_rectangle_20_15_brick_5_3_forman_potential_difference_with_exact.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_rectangle_20_15_brick_5_3_forman_flow_rate_difference_with_exact.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_rectangle_20_15_brick_5_3_forman_potential_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_rectangle_20_15_brick_5_3_forman_flow_rate_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_rectangle_20_15_brick_5_3_forman_potential_relative_error_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_rectangle_20_15_brick_5_3_forman_flow_rate_relative_error_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_rectangle_20_15_brick_5_3_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_rectangle_20_15_brick_5_3_forman_solution.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_rectangle_20_15_brick_5_3_forman_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_rectangle_20_15_brick_5_3_forman_potential_difference_with_exact.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_rectangle_20_15_brick_5_3_forman_flow_rate_difference_with_exact.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_rectangle_20_15_brick_5_3_forman_potential_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_rectangle_20_15_brick_5_3_forman_flow_rate_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_rectangle_20_15_brick_5_3_forman_potential_relative_error_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_rectangle_20_15_brick_5_3_forman_flow_rate_relative_error_with_exact_norm_2.txt\

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_2d_10_grains_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_exact_potential$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/obj/plugins/diffusion_steady_state_continuous_2d_d02_p00$(.OBJ)\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00\
    build/$(MODE)/lib/plugins/libdiffusion$(.DLL)
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d02_p00_potential\
  --raw > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_2d_10_grains_forman_flow_rate.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_exact_flow_rate$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/obj/plugins/diffusion_steady_state_continuous_2d_d02_p00$(.OBJ)\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00\
    build/$(MODE)/lib/plugins/libdiffusion$(.DLL)
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d02_p00_flow_rate\
  --raw > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_2d_10_grains_forman_potential_norm_2.txt:\
  build/$(MODE)/bin/double_array_lebesgue_norm$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_2d_10_grains_forman_potential.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --size=63\
  --vector=$(word 2, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_2d_10_grains_forman_flow_rate_norm_2.txt:\
  build/$(MODE)/bin/double_array_lebesgue_norm$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_2d_10_grains_forman_flow_rate.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --size=111\
  --vector=$(word 2, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_strong_cochain_2d_10_grains_forman_input.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_strong_from_continuous$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/obj/plugins/diffusion_steady_state_continuous_2d_d02_p00$(.OBJ)\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00\
    build/$(MODE)/lib/plugins/libdiffusion$(.DLL)
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d02_p00\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_strong_cochain_2d_10_grains_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_strong_solve$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_cbd.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_cbd_star.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_strong_cochain_2d_10_grains_forman_input.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  $(word 3, $^)\
  $(word 4, $^)\
  $(word 5, $^)\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_strong_cochain_2d_10_grains_forman_flow_rate.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_flow_rate_from_potential$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_hodge.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_strong_cochain_2d_10_grains_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_strong_cochain_2d_10_grains_forman_potential.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  --steady-state-primal-strong-raw $(word 4, $^)\
  --raw $(word 5, $^)\
  --raw > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_input.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_weak_from_continuous$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_vol.txt\
  build/$(MODE)/obj/plugins/diffusion_steady_state_continuous_2d_d02_p00$(.OBJ)\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00\
    build/$(MODE)/lib/plugins/libdiffusion$(.DLL)
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d02_p00\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_weak_solve$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_inner.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_input.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_flow_rate.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_flow_rate_from_potential$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_hodge.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_potential.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  --steady-state-primal-weak-raw $(word 4, $^)\
  --raw $(word 5, $^)\
  --raw > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_potential_difference_with_exact.txt:\
  build/$(MODE)/bin/double_array_subtract$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_2d_10_grains_forman_potential.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --size=63\
  --minuend=$(word 2, $^)\
  --subtrahend=$(word 3, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_flow_rate_difference_with_exact.txt:\
  build/$(MODE)/bin/double_array_subtract$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_flow_rate.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_2d_10_grains_forman_flow_rate.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --size=111\
  --minuend=$(word 2, $^)\
  --subtrahend=$(word 3, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_potential_difference_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_array_lebesgue_norm$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_potential_difference_with_exact.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --size=63\
  --vector=$(word 2, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_flow_rate_difference_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_array_lebesgue_norm$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_flow_rate_difference_with_exact.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --size=111\
  --vector=$(word 2, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_potential_relative_error_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_divide$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_potential_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_2d_10_grains_forman_potential_norm_2.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --numerator=$(word 2, $^)\
  --denominator=$(word 3, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_flow_rate_relative_error_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_divide$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_flow_rate_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_2d_10_grains_forman_flow_rate_norm_2.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --numerator=$(word 2, $^)\
  --denominator=$(word 3, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_input.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_from_continuous$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_vol.txt\
  build/$(MODE)/obj/plugins/diffusion_steady_state_continuous_2d_d02_p00$(.OBJ)\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00\
    build/$(MODE)/lib/plugins/libdiffusion$(.DLL)
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d02_p00\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_solution.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_solve$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_inner.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_input.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_potential$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains_forman.txt\
  build/$(MODE)/txt/mesh/2d_10_grains_forman_vol.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_solution.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  $(word 5, $^)\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_potential_difference_with_exact.txt:\
  build/$(MODE)/bin/double_array_subtract$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_2d_10_grains_forman_potential.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --size=63\
  --minuend=$(word 2, $^)\
  --subtrahend=$(word 3, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_flow_rate_difference_with_exact.txt:\
  build/$(MODE)/bin/double_array_subtract$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_solution.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_2d_10_grains_forman_flow_rate.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --size=111\
  --minuend-format=--steady-state-mixed-weak-solution-flow-rate-raw\
  --minuend=$(word 2, $^)\
  --subtrahend=$(word 3, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_potential_difference_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_array_lebesgue_norm$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_potential_difference_with_exact.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --size=63\
  --vector=$(word 2, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_flow_rate_difference_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_array_lebesgue_norm$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_flow_rate_difference_with_exact.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --size=111\
  --vector=$(word 2, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_potential_relative_error_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_divide$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_potential_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_2d_10_grains_forman_potential_norm_2.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --numerator=$(word 2, $^)\
  --denominator=$(word 3, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_flow_rate_relative_error_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_divide$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_flow_rate_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_2d_10_grains_forman_flow_rate_norm_2.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --numerator=$(word 2, $^)\
  --denominator=$(word 3, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_rectangle_20_15_brick_5_3_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_exact_potential$(.EXE)\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman.txt\
  build/$(MODE)/obj/plugins/diffusion_steady_state_continuous_2d_d02_p00$(.OBJ)\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00\
    build/$(MODE)/lib/plugins/libdiffusion$(.DLL)
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d02_p00_potential\
  --raw > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_rectangle_20_15_brick_5_3_forman_flow_rate.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_exact_flow_rate$(.EXE)\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman.txt\
  build/$(MODE)/obj/plugins/diffusion_steady_state_continuous_2d_d02_p00$(.OBJ)\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00\
    build/$(MODE)/lib/plugins/libdiffusion$(.DLL)
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d02_p00_flow_rate\
  --raw > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_rectangle_20_15_brick_5_3_forman_potential_norm_2.txt:\
  build/$(MODE)/bin/double_array_lebesgue_norm$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_rectangle_20_15_brick_5_3_forman_potential.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --size=77\
  --vector=$(word 2, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_rectangle_20_15_brick_5_3_forman_flow_rate_norm_2.txt:\
  build/$(MODE)/bin/double_array_lebesgue_norm$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_rectangle_20_15_brick_5_3_forman_flow_rate.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --size=136\
  --vector=$(word 2, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_strong_cochain_rectangle_20_15_brick_5_3_forman_input.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_strong_from_continuous$(.EXE)\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman.txt\
  build/$(MODE)/obj/plugins/diffusion_steady_state_continuous_2d_d02_p00$(.OBJ)\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00\
    build/$(MODE)/lib/plugins/libdiffusion$(.DLL)
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d02_p00\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_strong_cochain_rectangle_20_15_brick_5_3_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_strong_solve$(.EXE)\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman.txt\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman_cbd.txt\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman_cbd_star.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_strong_cochain_rectangle_20_15_brick_5_3_forman_input.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  $(word 3, $^)\
  $(word 4, $^)\
  $(word 5, $^)\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_strong_cochain_rectangle_20_15_brick_5_3_forman_flow_rate.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_flow_rate_from_potential$(.EXE)\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman.txt\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman_hodge.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_strong_cochain_rectangle_20_15_brick_5_3_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_strong_cochain_rectangle_20_15_brick_5_3_forman_potential.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  --steady-state-primal-strong-raw $(word 4, $^)\
  --raw $(word 5, $^)\
  --raw > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_rectangle_20_15_brick_5_3_forman_input.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_weak_from_continuous$(.EXE)\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman.txt\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman_vol.txt\
  build/$(MODE)/obj/plugins/diffusion_steady_state_continuous_2d_d02_p00$(.OBJ)\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00\
    build/$(MODE)/lib/plugins/libdiffusion$(.DLL)
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d02_p00\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_rectangle_20_15_brick_5_3_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_weak_solve$(.EXE)\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman.txt\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman_inner.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_rectangle_20_15_brick_5_3_forman_input.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_rectangle_20_15_brick_5_3_forman_flow_rate.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_flow_rate_from_potential$(.EXE)\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman.txt\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman_hodge.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_rectangle_20_15_brick_5_3_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_rectangle_20_15_brick_5_3_forman_potential.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  --steady-state-primal-weak-raw $(word 4, $^)\
  --raw $(word 5, $^)\
  --raw > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_rectangle_20_15_brick_5_3_forman_potential_difference_with_exact.txt:\
  build/$(MODE)/bin/double_array_subtract$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_rectangle_20_15_brick_5_3_forman_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_rectangle_20_15_brick_5_3_forman_potential.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --size=77\
  --minuend=$(word 2, $^)\
  --subtrahend=$(word 3, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_rectangle_20_15_brick_5_3_forman_flow_rate_difference_with_exact.txt:\
  build/$(MODE)/bin/double_array_subtract$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_rectangle_20_15_brick_5_3_forman_flow_rate.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_rectangle_20_15_brick_5_3_forman_flow_rate.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --size=136\
  --minuend=$(word 2, $^)\
  --subtrahend=$(word 3, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_rectangle_20_15_brick_5_3_forman_potential_difference_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_array_lebesgue_norm$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_rectangle_20_15_brick_5_3_forman_potential_difference_with_exact.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --size=77\
  --vector=$(word 2, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_rectangle_20_15_brick_5_3_forman_flow_rate_difference_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_array_lebesgue_norm$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_rectangle_20_15_brick_5_3_forman_flow_rate_difference_with_exact.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --size=136\
  --vector=$(word 2, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_rectangle_20_15_brick_5_3_forman_potential_relative_error_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_divide$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_rectangle_20_15_brick_5_3_forman_potential_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_rectangle_20_15_brick_5_3_forman_potential_norm_2.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --numerator=$(word 2, $^)\
  --denominator=$(word 3, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_rectangle_20_15_brick_5_3_forman_flow_rate_relative_error_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_divide$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/primal_weak_cochain_rectangle_20_15_brick_5_3_forman_flow_rate_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_rectangle_20_15_brick_5_3_forman_flow_rate_norm_2.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --numerator=$(word 2, $^)\
  --denominator=$(word 3, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_rectangle_20_15_brick_5_3_forman_input.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_from_continuous$(.EXE)\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman.txt\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman_vol.txt\
  build/$(MODE)/obj/plugins/diffusion_steady_state_continuous_2d_d02_p00$(.OBJ)\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00\
    build/$(MODE)/lib/plugins/libdiffusion$(.DLL)
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d02_p00\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_rectangle_20_15_brick_5_3_forman_solution.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_solve$(.EXE)\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman.txt\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman_inner.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_rectangle_20_15_brick_5_3_forman_input.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_rectangle_20_15_brick_5_3_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_potential$(.EXE)\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman.txt\
  build/$(MODE)/txt/mesh/rectangle_20_15_brick_5_3/forman_vol.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_rectangle_20_15_brick_5_3_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_rectangle_20_15_brick_5_3_forman_solution.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  $(word 5, $^)\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_rectangle_20_15_brick_5_3_forman_potential_difference_with_exact.txt:\
  build/$(MODE)/bin/double_array_subtract$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_rectangle_20_15_brick_5_3_forman_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_rectangle_20_15_brick_5_3_forman_potential.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --size=77\
  --minuend=$(word 2, $^)\
  --subtrahend=$(word 3, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_rectangle_20_15_brick_5_3_forman_flow_rate_difference_with_exact.txt:\
  build/$(MODE)/bin/double_array_subtract$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_rectangle_20_15_brick_5_3_forman_solution.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_rectangle_20_15_brick_5_3_forman_flow_rate.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --size=136\
  --minuend-format=--steady-state-mixed-weak-solution-flow-rate-raw\
  --minuend=$(word 2, $^)\
  --subtrahend=$(word 3, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_rectangle_20_15_brick_5_3_forman_potential_difference_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_array_lebesgue_norm$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_rectangle_20_15_brick_5_3_forman_potential_difference_with_exact.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --size=77\
  --vector=$(word 2, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_rectangle_20_15_brick_5_3_forman_flow_rate_difference_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_array_lebesgue_norm$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_rectangle_20_15_brick_5_3_forman_flow_rate_difference_with_exact.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --size=136\
  --vector=$(word 2, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_rectangle_20_15_brick_5_3_forman_potential_relative_error_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_divide$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_rectangle_20_15_brick_5_3_forman_potential_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_rectangle_20_15_brick_5_3_forman_potential_norm_2.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --numerator=$(word 2, $^)\
  --denominator=$(word 3, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_rectangle_20_15_brick_5_3_forman_flow_rate_relative_error_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_divide$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/mixed_weak_cochain_rectangle_20_15_brick_5_3_forman_flow_rate_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00/exact_rectangle_20_15_brick_5_3_forman_flow_rate_norm_2.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --numerator=$(word 2, $^)\
  --denominator=$(word 3, $^)\
  --output=$@

txt_diffusion_steady_state_continuous_2d_d02_p00:\
  $(_txt_diffusion_steady_state_continuous_2d_d02_p00)

txt_diffusion_steady_state_continuous_2d_d02_p00_clean:
	-$(RM) $(_txt_diffusion_steady_state_continuous_2d_d02_p00)

txt_diffusion_steady_state_continuous_2d_d02_p00_distclean:
	-$(RM) -r build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d02_p00
