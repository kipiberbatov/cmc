.PHONY: txt_diffusion_steady_state_continuous_3d_d00_p00_3d_10_grains_forman\
        txt_diffusion_steady_state_continuous_3d_d00_p00_3d_10_grains_forman_clean\
        txt_diffusion_steady_state_continuous_3d_d00_p00_3d_10_grains_forman_distclean

build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman:\
  | build/$(MODE)/txt/diffusion/steady_state
	mkdir -p $@

_txt_diffusion_steady_state_continuous_3d_d00_p00_3d_10_grains_forman :=\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/exact_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/exact_potential_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/primal_strong_cochain_input.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/primal_strong_cochain_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/primal_strong_cochain_flow_rate.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/primal_strong_cochain_potential_difference_with_exact.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/primal_strong_cochain_potential_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/primal_strong_cochain_potential_relative_error_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/primal_weak_cochain_input.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/primal_weak_cochain_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/primal_weak_cochain_flow_rate.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/primal_weak_cochain_potential_difference_with_exact.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/primal_weak_cochain_potential_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/primal_weak_cochain_potential_relative_error_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/mixed_weak_cochain_input.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/mixed_weak_cochain_solution.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/mixed_weak_cochain_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/mixed_weak_cochain_potential_difference_with_exact.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/mixed_weak_cochain_potential_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/mixed_weak_cochain_potential_relative_error_with_exact_norm_2.txt\

build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/exact_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_exact_potential$(.EXE)\
  build/$(MODE)/txt/mesh/3d_10_grains/forman.txt\
  build/$(MODE)/obj/plugins/diffusion_steady_state_continuous_3d_d00_p00$(.OBJ)\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman\
    build/$(MODE)/lib/plugins/libdiffusion$(.DLL)
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_3d_d00_p00_potential\
  --raw > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/exact_potential_norm_2.txt:\
  build/$(MODE)/bin/double_array_lebesgue_norm$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/exact_potential.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman
	$(INTERPRETER) $<\
  --size=229\
  --vector=$(word 2, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/primal_strong_cochain_input.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_strong_from_continuous$(.EXE)\
  build/$(MODE)/txt/mesh/3d_10_grains/forman.txt\
  build/$(MODE)/obj/plugins/diffusion_steady_state_continuous_3d_d00_p00$(.OBJ)\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman\
    build/$(MODE)/lib/plugins/libdiffusion$(.DLL)
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_3d_d00_p00\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/primal_strong_cochain_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_strong_solve$(.EXE)\
  build/$(MODE)/txt/mesh/3d_10_grains/forman.txt\
  build/$(MODE)/txt/mesh/3d_10_grains/forman_cbd.txt\
  build/$(MODE)/txt/mesh/3d_10_grains/forman_cbd_star.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/primal_strong_cochain_input.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  $(word 3, $^)\
  $(word 4, $^)\
  $(word 5, $^)\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/primal_strong_cochain_flow_rate.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_flow_rate_from_potential$(.EXE)\
  build/$(MODE)/txt/mesh/3d_10_grains/forman.txt\
  build/$(MODE)/txt/mesh/3d_10_grains/forman_hodge.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/primal_strong_cochain_input.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/primal_strong_cochain_potential.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  --steady-state-primal-strong-raw $(word 4, $^)\
  --raw $(word 5, $^)\
  --raw > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/primal_strong_cochain_potential_difference_with_exact.txt:\
  build/$(MODE)/bin/double_array_subtract$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/primal_strong_cochain_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/exact_potential.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman
	$(INTERPRETER) $<\
  --size=229\
  --minuend=$(word 2, $^)\
  --subtrahend=$(word 3, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/primal_strong_cochain_potential_difference_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_array_lebesgue_norm$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/primal_strong_cochain_potential_difference_with_exact.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman
	$(INTERPRETER) $<\
  --size=229\
  --vector=$(word 2, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/primal_strong_cochain_potential_relative_error_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_divide$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/primal_strong_cochain_potential_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/exact_potential_norm_2.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman
	$(INTERPRETER) $<\
  --numerator=$(word 2, $^)\
  --denominator=$(word 3, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/primal_weak_cochain_input.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_weak_from_continuous$(.EXE)\
  build/$(MODE)/txt/mesh/3d_10_grains/forman.txt\
  build/$(MODE)/txt/mesh/3d_10_grains/forman_vol.txt\
  build/$(MODE)/obj/plugins/diffusion_steady_state_continuous_3d_d00_p00$(.OBJ)\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman\
    build/$(MODE)/lib/plugins/libdiffusion$(.DLL)
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_3d_d00_p00\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/primal_weak_cochain_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_weak_solve$(.EXE)\
  build/$(MODE)/txt/mesh/3d_10_grains/forman.txt\
  build/$(MODE)/txt/mesh/3d_10_grains/forman_inner.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/primal_weak_cochain_input.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/primal_weak_cochain_flow_rate.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_flow_rate_from_potential$(.EXE)\
  build/$(MODE)/txt/mesh/3d_10_grains/forman.txt\
  build/$(MODE)/txt/mesh/3d_10_grains/forman_hodge.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/primal_weak_cochain_input.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/primal_weak_cochain_potential.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  --steady-state-primal-weak-raw $(word 4, $^)\
  --raw $(word 5, $^)\
  --raw > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/primal_weak_cochain_potential_difference_with_exact.txt:\
  build/$(MODE)/bin/double_array_subtract$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/primal_weak_cochain_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/exact_potential.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman
	$(INTERPRETER) $<\
  --size=229\
  --minuend=$(word 2, $^)\
  --subtrahend=$(word 3, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/primal_weak_cochain_potential_difference_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_array_lebesgue_norm$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/primal_weak_cochain_potential_difference_with_exact.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman
	$(INTERPRETER) $<\
  --size=229\
  --vector=$(word 2, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/primal_weak_cochain_potential_relative_error_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_divide$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/primal_weak_cochain_potential_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/exact_potential_norm_2.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman
	$(INTERPRETER) $<\
  --numerator=$(word 2, $^)\
  --denominator=$(word 3, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/mixed_weak_cochain_input.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_from_continuous$(.EXE)\
  build/$(MODE)/txt/mesh/3d_10_grains/forman.txt\
  build/$(MODE)/txt/mesh/3d_10_grains/forman_vol.txt\
  build/$(MODE)/obj/plugins/diffusion_steady_state_continuous_3d_d00_p00$(.OBJ)\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman\
    build/$(MODE)/lib/plugins/libdiffusion$(.DLL)
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_3d_d00_p00\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/mixed_weak_cochain_solution.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_solve$(.EXE)\
  build/$(MODE)/txt/mesh/3d_10_grains/forman.txt\
  build/$(MODE)/txt/mesh/3d_10_grains/forman_inner.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/mixed_weak_cochain_input.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/mixed_weak_cochain_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_potential$(.EXE)\
  build/$(MODE)/txt/mesh/3d_10_grains/forman.txt\
  build/$(MODE)/txt/mesh/3d_10_grains/forman_vol.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/mixed_weak_cochain_input.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/mixed_weak_cochain_solution.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  $(word 5, $^)\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/mixed_weak_cochain_potential_difference_with_exact.txt:\
  build/$(MODE)/bin/double_array_subtract$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/mixed_weak_cochain_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/exact_potential.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman
	$(INTERPRETER) $<\
  --size=229\
  --minuend=$(word 2, $^)\
  --subtrahend=$(word 3, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/mixed_weak_cochain_potential_difference_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_array_lebesgue_norm$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/mixed_weak_cochain_potential_difference_with_exact.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman
	$(INTERPRETER) $<\
  --size=229\
  --vector=$(word 2, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/mixed_weak_cochain_potential_relative_error_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_divide$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/mixed_weak_cochain_potential_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman/exact_potential_norm_2.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman
	$(INTERPRETER) $<\
  --numerator=$(word 2, $^)\
  --denominator=$(word 3, $^)\
  --output=$@

txt_diffusion_steady_state_continuous_3d_d00_p00_3d_10_grains_forman:\
  $(_txt_diffusion_steady_state_continuous_3d_d00_p00_3d_10_grains_forman)

txt_diffusion_steady_state_continuous_3d_d00_p00_3d_10_grains_forman_clean:
	-$(RM) $(_txt_diffusion_steady_state_continuous_3d_d00_p00_3d_10_grains_forman)

txt_diffusion_steady_state_continuous_3d_d00_p00_3d_10_grains_forman_distclean:
	-$(RM) -r build/$(MODE)/txt/diffusion/steady_state/continuous_3d_d00_p00_3d_10_grains_forman
