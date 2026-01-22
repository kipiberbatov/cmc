.PHONY: txt_diffusion_transient_continuous_2d_d02_p00\
        txt_diffusion_transient_continuous_2d_d02_p00_clean\
        txt_diffusion_transient_continuous_2d_d02_p00_distclean

build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00:\
  | build/$(MODE)/txt/diffusion/transient
	mkdir -p $@

_txt_diffusion_transient_continuous_2d_d02_p00 :=\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00/primal_strong_cochain_2d_10_grains_forman_input.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00/primal_strong_cochain_2d_10_grains_forman_trapezoidal_0p05_1000_potential.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00/primal_strong_cochain_2d_10_grains_forman_trapezoidal_0p05_1000_flow_rate.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_input.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_trapezoidal_0p05_1000_potential.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_trapezoidal_0p05_1000_flow_rate.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_input.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_trapezoidal_0p05_1000_solution.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_trapezoidal_0p05_1000_potential.txt

build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00/primal_strong_cochain_2d_10_grains_forman_input.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_primal_strong_from_continuous$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains/forman.txt\
  build/$(MODE)/obj/plugins/diffusion_transient_continuous_2d_d02_p00$(.OBJ)\
  | build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00\
    build/$(MODE)/lib/plugins/libdiffusion$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --dynamic-library=$(word 2, $|)\
  --input-data=diffusion_transient_continuous_2d_d02_p00\
  > $@

build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00/primal_strong_cochain_2d_10_grains_forman_trapezoidal_0p05_1000_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_primal_strong_solve_trapezoidal$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains/forman.txt\
  build/$(MODE)/txt/mesh/2d_10_grains/forman_cbd.txt\
  build/$(MODE)/txt/mesh/2d_10_grains/forman_cbd_star.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00/primal_strong_cochain_2d_10_grains_forman_input.txt\
  | build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --mesh-coboundary-0=$(word 3, $^)\
  --mesh-coboundary-star-1=$(word 4, $^)\
  --input-data=$(word 5, $^)\
  --time-step=0.05\
  --number-of-steps=1000\
  > $@

build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00/primal_strong_cochain_2d_10_grains_forman_trapezoidal_0p05_1000_flow_rate.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_flow_rate_from_potential$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains/forman.txt\
  build/$(MODE)/txt/mesh/2d_10_grains/forman_hodge.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00/primal_strong_cochain_2d_10_grains_forman_input.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00/primal_strong_cochain_2d_10_grains_forman_trapezoidal_0p05_1000_potential.txt\
  | build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --mesh-hodge=$(word 3, $^)\
  --kappa-1-format=transient-primal-strong-raw\
  --kappa-1=$(word 4, $^)\
  --potential=$(word 5, $^)\
  --number-of-steps=1000\
  > $@

build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_input.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_primal_weak_from_continuous$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains/forman.txt\
  build/$(MODE)/txt/mesh/2d_10_grains/forman_vol.txt\
  build/$(MODE)/obj/plugins/diffusion_transient_continuous_2d_d02_p00$(.OBJ)\
  | build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00\
    build/$(MODE)/lib/plugins/libdiffusion$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --mesh-volumes=$(word 3, $^)\
  --dynamic-library=$(word 2, $|)\
  --input-data=diffusion_transient_continuous_2d_d02_p00\
  > $@

build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_trapezoidal_0p05_1000_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_primal_weak_solve_trapezoidal$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains/forman.txt\
  build/$(MODE)/txt/mesh/2d_10_grains/forman_inner.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_input.txt\
  | build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --mesh-inner=$(word 3, $^)\
  --input-data=$(word 4, $^)\
  --time-step=0.05\
  --number-of-steps=1000\
  > $@

build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_trapezoidal_0p05_1000_flow_rate.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_flow_rate_from_potential$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains/forman.txt\
  build/$(MODE)/txt/mesh/2d_10_grains/forman_hodge.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_input.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00/primal_weak_cochain_2d_10_grains_forman_trapezoidal_0p05_1000_potential.txt\
  | build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --mesh-hodge=$(word 3, $^)\
  --kappa-1-format=transient-primal-weak-raw\
  --kappa-1=$(word 4, $^)\
  --potential=$(word 5, $^)\
  --number-of-steps=1000\
  > $@

build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_input.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_mixed_weak_from_continuous$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains/forman.txt\
  build/$(MODE)/txt/mesh/2d_10_grains/forman_hodge.txt\
  build/$(MODE)/txt/mesh/2d_10_grains/forman_vol.txt\
  build/$(MODE)/obj/plugins/diffusion_transient_continuous_2d_d02_p00$(.OBJ)\
  | build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00\
    build/$(MODE)/lib/plugins/libdiffusion$(.DLL)
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --mesh-hodge-star=$(word 3, $^)\
  --mesh-volumes=$(word 4, $^)\
  --dynamic-library=$(word 2, $|)\
  --input-data=diffusion_transient_continuous_2d_d02_p00\
  > $@

build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_trapezoidal_0p05_1000_solution.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_mixed_weak_solve_trapezoidal$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains/forman.txt\
  build/$(MODE)/txt/mesh/2d_10_grains/forman_inner.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_input.txt\
  | build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --mesh-inner=$(word 3, $^)\
  --input-data=$(word 4, $^)\
  --time-step=0.05\
  --number-of-steps=1000\
  > $@

build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_trapezoidal_0p05_1000_potential.txt:\
  build/$(MODE)/bin/diffusion_transient_discrete_mixed_weak_potential$(.EXE)\
  build/$(MODE)/txt/mesh/2d_10_grains/forman.txt\
  build/$(MODE)/txt/mesh/2d_10_grains/forman_vol.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_input.txt\
  build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00/mixed_weak_cochain_2d_10_grains_forman_trapezoidal_0p05_1000_solution.txt\
  | build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00
	$(INTERPRETER) $<\
  --mesh=$(word 2, $^)\
  --mesh-volumes=$(word 3, $^)\
  --input-data=$(word 4, $^)\
  --number-of-steps=1000\
  --solution=$(word 5, $^)\
  > $@

txt_diffusion_transient_continuous_2d_d02_p00:\
  $(_txt_diffusion_transient_continuous_2d_d02_p00)

txt_diffusion_transient_continuous_2d_d02_p00_clean:
	-$(RM) $(_txt_diffusion_transient_continuous_2d_d02_p00)

txt_diffusion_transient_continuous_2d_d02_p00_distclean:
	-$(RM) -r build/$(MODE)/txt/diffusion/transient/continuous_2d_d02_p00
