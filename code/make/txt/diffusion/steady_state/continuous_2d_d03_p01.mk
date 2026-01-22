.PHONY: txt_diffusion_steady_state_continuous_2d_d03_p01\
        txt_diffusion_steady_state_continuous_2d_d03_p01_clean\
        txt_diffusion_steady_state_continuous_2d_d03_p01_distclean

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01:\
  | build/$(MODE)/txt/diffusion/steady_state
	mkdir -p $@

_txt_diffusion_steady_state_continuous_2d_d03_p01 :=\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/exact_disk_polar_4_3_forman_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/exact_disk_polar_4_3_forman_flow_rate.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/exact_disk_polar_4_3_forman_potential_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/exact_disk_polar_4_3_forman_flow_rate_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_4_3_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_4_3_forman_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_4_3_forman_flow_rate.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_4_3_forman_potential_difference_with_exact.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_4_3_forman_flow_rate_difference_with_exact.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_4_3_forman_potential_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_4_3_forman_flow_rate_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_4_3_forman_potential_relative_error_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_4_3_forman_flow_rate_relative_error_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_4_3_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_4_3_forman_solution.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_4_3_forman_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_4_3_forman_potential_difference_with_exact.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_4_3_forman_flow_rate_difference_with_exact.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_4_3_forman_potential_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_4_3_forman_flow_rate_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_4_3_forman_potential_relative_error_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_4_3_forman_flow_rate_relative_error_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/exact_disk_polar_18_10_forman_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/exact_disk_polar_18_10_forman_flow_rate.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/exact_disk_polar_18_10_forman_potential_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/exact_disk_polar_18_10_forman_flow_rate_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_18_10_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_18_10_forman_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_18_10_forman_flow_rate.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_18_10_forman_potential_difference_with_exact.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_18_10_forman_flow_rate_difference_with_exact.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_18_10_forman_potential_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_18_10_forman_flow_rate_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_18_10_forman_potential_relative_error_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_18_10_forman_flow_rate_relative_error_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_18_10_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_18_10_forman_solution.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_18_10_forman_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_18_10_forman_potential_difference_with_exact.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_18_10_forman_flow_rate_difference_with_exact.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_18_10_forman_potential_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_18_10_forman_flow_rate_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_18_10_forman_potential_relative_error_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_18_10_forman_flow_rate_relative_error_with_exact_norm_2.txt\

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/exact_disk_polar_4_3_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_exact_potential$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_4_3/forman.txt\
  build/$(MODE)/obj/plugins/diffusion_steady_state_continuous_2d_d03_p01$(.OBJ)\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01\
    build/$(MODE)/lib/plugins/libdiffusion$(.DLL)
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d03_p00_exact_potential_disk_polar\
  --raw > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/exact_disk_polar_4_3_forman_flow_rate.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_exact_flow_rate$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_4_3/forman.txt\
  build/$(MODE)/obj/plugins/diffusion_steady_state_continuous_2d_d03_p01$(.OBJ)\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01\
    build/$(MODE)/lib/plugins/libdiffusion$(.DLL)
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d03_p00_exact_flow_rate_disk_polar\
  --raw > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/exact_disk_polar_4_3_forman_potential_norm_2.txt:\
  build/$(MODE)/bin/double_array_lebesgue_norm$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/exact_disk_polar_4_3_forman_potential.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
	$(INTERPRETER) $<\
  --size=49\
  --vector=$(word 2, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/exact_disk_polar_4_3_forman_flow_rate_norm_2.txt:\
  build/$(MODE)/bin/double_array_lebesgue_norm$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/exact_disk_polar_4_3_forman_flow_rate.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
	$(INTERPRETER) $<\
  --size=92\
  --vector=$(word 2, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_4_3_forman_input.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_weak_from_continuous$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_4_3/forman.txt\
  build/$(MODE)/txt/mesh/disk_polar_4_3/forman_vol.txt\
  build/$(MODE)/obj/plugins/diffusion_steady_state_continuous_2d_d03_p01$(.OBJ)\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01\
    build/$(MODE)/lib/plugins/libdiffusion$(.DLL)
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d03_p01\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_4_3_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_weak_solve$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_4_3/forman.txt\
  build/$(MODE)/txt/mesh/disk_polar_4_3/forman_inner.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_4_3_forman_input.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_4_3_forman_flow_rate.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_flow_rate_from_potential$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_4_3/forman.txt\
  build/$(MODE)/txt/mesh/disk_polar_4_3/forman_hodge.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_4_3_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_4_3_forman_potential.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  --steady-state-primal-weak-raw $(word 4, $^)\
  --raw $(word 5, $^)\
  --raw > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_4_3_forman_potential_difference_with_exact.txt:\
  build/$(MODE)/bin/double_array_subtract$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_4_3_forman_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/exact_disk_polar_4_3_forman_potential.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
	$(INTERPRETER) $<\
  --size=49\
  --minuend=$(word 2, $^)\
  --subtrahend=$(word 3, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_4_3_forman_flow_rate_difference_with_exact.txt:\
  build/$(MODE)/bin/double_array_subtract$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_4_3_forman_flow_rate.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/exact_disk_polar_4_3_forman_flow_rate.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
	$(INTERPRETER) $<\
  --size=92\
  --minuend=$(word 2, $^)\
  --subtrahend=$(word 3, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_4_3_forman_potential_difference_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_array_lebesgue_norm$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_4_3_forman_potential_difference_with_exact.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
	$(INTERPRETER) $<\
  --size=49\
  --vector=$(word 2, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_4_3_forman_flow_rate_difference_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_array_lebesgue_norm$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_4_3_forman_flow_rate_difference_with_exact.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
	$(INTERPRETER) $<\
  --size=92\
  --vector=$(word 2, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_4_3_forman_potential_relative_error_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_divide$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_4_3_forman_potential_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/exact_disk_polar_4_3_forman_potential_norm_2.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
	$(INTERPRETER) $<\
  --numerator=$(word 2, $^)\
  --denominator=$(word 3, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_4_3_forman_flow_rate_relative_error_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_divide$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_4_3_forman_flow_rate_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/exact_disk_polar_4_3_forman_flow_rate_norm_2.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
	$(INTERPRETER) $<\
  --numerator=$(word 2, $^)\
  --denominator=$(word 3, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_4_3_forman_input.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_from_continuous$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_4_3/forman.txt\
  build/$(MODE)/txt/mesh/disk_polar_4_3/forman_vol.txt\
  build/$(MODE)/obj/plugins/diffusion_steady_state_continuous_2d_d03_p01$(.OBJ)\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01\
    build/$(MODE)/lib/plugins/libdiffusion$(.DLL)
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d03_p01\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_4_3_forman_solution.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_solve$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_4_3/forman.txt\
  build/$(MODE)/txt/mesh/disk_polar_4_3/forman_inner.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_4_3_forman_input.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_4_3_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_potential$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_4_3/forman.txt\
  build/$(MODE)/txt/mesh/disk_polar_4_3/forman_vol.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_4_3_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_4_3_forman_solution.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  $(word 5, $^)\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_4_3_forman_potential_difference_with_exact.txt:\
  build/$(MODE)/bin/double_array_subtract$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_4_3_forman_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/exact_disk_polar_4_3_forman_potential.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
	$(INTERPRETER) $<\
  --size=49\
  --minuend=$(word 2, $^)\
  --subtrahend=$(word 3, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_4_3_forman_flow_rate_difference_with_exact.txt:\
  build/$(MODE)/bin/double_array_subtract$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_4_3_forman_solution.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/exact_disk_polar_4_3_forman_flow_rate.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
	$(INTERPRETER) $<\
  --size=92\
  --minuend-format=--steady-state-mixed-weak-solution-flow-rate-raw\
  --minuend=$(word 2, $^)\
  --subtrahend=$(word 3, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_4_3_forman_potential_difference_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_array_lebesgue_norm$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_4_3_forman_potential_difference_with_exact.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
	$(INTERPRETER) $<\
  --size=49\
  --vector=$(word 2, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_4_3_forman_flow_rate_difference_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_array_lebesgue_norm$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_4_3_forman_flow_rate_difference_with_exact.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
	$(INTERPRETER) $<\
  --size=92\
  --vector=$(word 2, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_4_3_forman_potential_relative_error_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_divide$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_4_3_forman_potential_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/exact_disk_polar_4_3_forman_potential_norm_2.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
	$(INTERPRETER) $<\
  --numerator=$(word 2, $^)\
  --denominator=$(word 3, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_4_3_forman_flow_rate_relative_error_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_divide$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_4_3_forman_flow_rate_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/exact_disk_polar_4_3_forman_flow_rate_norm_2.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
	$(INTERPRETER) $<\
  --numerator=$(word 2, $^)\
  --denominator=$(word 3, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/exact_disk_polar_18_10_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_exact_potential$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_18_10/forman.txt\
  build/$(MODE)/obj/plugins/diffusion_steady_state_continuous_2d_d03_p01$(.OBJ)\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01\
    build/$(MODE)/lib/plugins/libdiffusion$(.DLL)
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d03_p00_exact_potential_disk_polar\
  --raw > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/exact_disk_polar_18_10_forman_flow_rate.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_exact_flow_rate$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_18_10/forman.txt\
  build/$(MODE)/obj/plugins/diffusion_steady_state_continuous_2d_d03_p01$(.OBJ)\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01\
    build/$(MODE)/lib/plugins/libdiffusion$(.DLL)
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d03_p00_exact_flow_rate_disk_polar\
  --raw > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/exact_disk_polar_18_10_forman_potential_norm_2.txt:\
  build/$(MODE)/bin/double_array_lebesgue_norm$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/exact_disk_polar_18_10_forman_potential.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
	$(INTERPRETER) $<\
  --size=721\
  --vector=$(word 2, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/exact_disk_polar_18_10_forman_flow_rate_norm_2.txt:\
  build/$(MODE)/bin/double_array_lebesgue_norm$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/exact_disk_polar_18_10_forman_flow_rate.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
	$(INTERPRETER) $<\
  --size=1422\
  --vector=$(word 2, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_18_10_forman_input.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_weak_from_continuous$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_18_10/forman.txt\
  build/$(MODE)/txt/mesh/disk_polar_18_10/forman_vol.txt\
  build/$(MODE)/obj/plugins/diffusion_steady_state_continuous_2d_d03_p01$(.OBJ)\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01\
    build/$(MODE)/lib/plugins/libdiffusion$(.DLL)
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d03_p01\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_18_10_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_weak_solve$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_18_10/forman.txt\
  build/$(MODE)/txt/mesh/disk_polar_18_10/forman_inner.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_18_10_forman_input.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_18_10_forman_flow_rate.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_flow_rate_from_potential$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_18_10/forman.txt\
  build/$(MODE)/txt/mesh/disk_polar_18_10/forman_hodge.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_18_10_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_18_10_forman_potential.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  --steady-state-primal-weak-raw $(word 4, $^)\
  --raw $(word 5, $^)\
  --raw > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_18_10_forman_potential_difference_with_exact.txt:\
  build/$(MODE)/bin/double_array_subtract$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_18_10_forman_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/exact_disk_polar_18_10_forman_potential.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
	$(INTERPRETER) $<\
  --size=721\
  --minuend=$(word 2, $^)\
  --subtrahend=$(word 3, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_18_10_forman_flow_rate_difference_with_exact.txt:\
  build/$(MODE)/bin/double_array_subtract$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_18_10_forman_flow_rate.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/exact_disk_polar_18_10_forman_flow_rate.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
	$(INTERPRETER) $<\
  --size=1422\
  --minuend=$(word 2, $^)\
  --subtrahend=$(word 3, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_18_10_forman_potential_difference_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_array_lebesgue_norm$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_18_10_forman_potential_difference_with_exact.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
	$(INTERPRETER) $<\
  --size=721\
  --vector=$(word 2, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_18_10_forman_flow_rate_difference_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_array_lebesgue_norm$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_18_10_forman_flow_rate_difference_with_exact.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
	$(INTERPRETER) $<\
  --size=1422\
  --vector=$(word 2, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_18_10_forman_potential_relative_error_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_divide$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_18_10_forman_potential_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/exact_disk_polar_18_10_forman_potential_norm_2.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
	$(INTERPRETER) $<\
  --numerator=$(word 2, $^)\
  --denominator=$(word 3, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_18_10_forman_flow_rate_relative_error_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_divide$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/primal_weak_cochain_disk_polar_18_10_forman_flow_rate_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/exact_disk_polar_18_10_forman_flow_rate_norm_2.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
	$(INTERPRETER) $<\
  --numerator=$(word 2, $^)\
  --denominator=$(word 3, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_18_10_forman_input.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_from_continuous$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_18_10/forman.txt\
  build/$(MODE)/txt/mesh/disk_polar_18_10/forman_vol.txt\
  build/$(MODE)/obj/plugins/diffusion_steady_state_continuous_2d_d03_p01$(.OBJ)\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01\
    build/$(MODE)/lib/plugins/libdiffusion$(.DLL)
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d03_p01\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_18_10_forman_solution.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_solve$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_18_10/forman.txt\
  build/$(MODE)/txt/mesh/disk_polar_18_10/forman_inner.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_18_10_forman_input.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_18_10_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_potential$(.EXE)\
  build/$(MODE)/txt/mesh/disk_polar_18_10/forman.txt\
  build/$(MODE)/txt/mesh/disk_polar_18_10/forman_vol.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_18_10_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_18_10_forman_solution.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  $(word 5, $^)\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_18_10_forman_potential_difference_with_exact.txt:\
  build/$(MODE)/bin/double_array_subtract$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_18_10_forman_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/exact_disk_polar_18_10_forman_potential.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
	$(INTERPRETER) $<\
  --size=721\
  --minuend=$(word 2, $^)\
  --subtrahend=$(word 3, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_18_10_forman_flow_rate_difference_with_exact.txt:\
  build/$(MODE)/bin/double_array_subtract$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_18_10_forman_solution.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/exact_disk_polar_18_10_forman_flow_rate.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
	$(INTERPRETER) $<\
  --size=1422\
  --minuend-format=--steady-state-mixed-weak-solution-flow-rate-raw\
  --minuend=$(word 2, $^)\
  --subtrahend=$(word 3, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_18_10_forman_potential_difference_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_array_lebesgue_norm$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_18_10_forman_potential_difference_with_exact.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
	$(INTERPRETER) $<\
  --size=721\
  --vector=$(word 2, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_18_10_forman_flow_rate_difference_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_array_lebesgue_norm$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_18_10_forman_flow_rate_difference_with_exact.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
	$(INTERPRETER) $<\
  --size=1422\
  --vector=$(word 2, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_18_10_forman_potential_relative_error_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_divide$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_18_10_forman_potential_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/exact_disk_polar_18_10_forman_potential_norm_2.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
	$(INTERPRETER) $<\
  --numerator=$(word 2, $^)\
  --denominator=$(word 3, $^)\
  --output=$@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_18_10_forman_flow_rate_relative_error_with_exact_norm_2.txt:\
  build/$(MODE)/bin/double_divide$(.EXE)\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/mixed_weak_cochain_disk_polar_18_10_forman_flow_rate_difference_with_exact_norm_2.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01/exact_disk_polar_18_10_forman_flow_rate_norm_2.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
	$(INTERPRETER) $<\
  --numerator=$(word 2, $^)\
  --denominator=$(word 3, $^)\
  --output=$@

txt_diffusion_steady_state_continuous_2d_d03_p01:\
  $(_txt_diffusion_steady_state_continuous_2d_d03_p01)

txt_diffusion_steady_state_continuous_2d_d03_p01_clean:
	-$(RM) $(_txt_diffusion_steady_state_continuous_2d_d03_p01)

txt_diffusion_steady_state_continuous_2d_d03_p01_distclean:
	-$(RM) -r build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d03_p01
