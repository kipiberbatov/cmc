.PHONY: txt_diffusion_steady_state_continuous_2d_d00_p03\
        txt_diffusion_steady_state_continuous_2d_d00_p03_clean\
        txt_diffusion_steady_state_continuous_2d_d00_p03_distclean

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03:\
  | build/$(MODE)/txt/diffusion/steady_state
	mkdir -p $@

_txt_diffusion_steady_state_continuous_2d_d00_p03 :=\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03/exact_brick_2d_2_forman_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03/exact_brick_2d_2_forman_flow_rate.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03/primal_strong_cochain_brick_2d_2_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03/primal_strong_cochain_brick_2d_2_forman_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03/primal_strong_cochain_brick_2d_2_forman_flow_rate.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03/primal_weak_cochain_brick_2d_2_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03/primal_weak_cochain_brick_2d_2_forman_potential.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03/primal_weak_cochain_brick_2d_2_forman_flow_rate.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03/mixed_weak_cochain_brick_2d_2_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03/mixed_weak_cochain_brick_2d_2_forman_solution.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03/mixed_weak_cochain_brick_2d_2_forman_potential.txt\

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03/exact_brick_2d_2_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_exact_potential$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2/forman.txt\
  build/$(MODE)/obj/plugins/diffusion_steady_state_continuous_2d_d00_p03$(.OBJ)\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03\
    build/$(MODE)/lib/plugins/libdiffusion$(.DLL)
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d00_p03_potential\
  --raw > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03/exact_brick_2d_2_forman_flow_rate.txt:\
  build/$(MODE)/bin/diffusion_steady_state_continuous_exact_flow_rate$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2/forman.txt\
  build/$(MODE)/obj/plugins/diffusion_steady_state_continuous_2d_d00_p03$(.OBJ)\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03\
    build/$(MODE)/lib/plugins/libdiffusion$(.DLL)
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d00_p03_flow_rate\
  --raw > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03/primal_strong_cochain_brick_2d_2_forman_input.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_strong_from_continuous$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2/forman.txt\
  build/$(MODE)/obj/plugins/diffusion_steady_state_continuous_2d_d00_p03$(.OBJ)\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03\
    build/$(MODE)/lib/plugins/libdiffusion$(.DLL)
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d00_p03\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03/primal_strong_cochain_brick_2d_2_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_strong_solve$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2/forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2/forman_cbd.txt\
  build/$(MODE)/txt/mesh/brick_2d_2/forman_cbd_star.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03/primal_strong_cochain_brick_2d_2_forman_input.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  $(word 3, $^)\
  $(word 4, $^)\
  $(word 5, $^)\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03/primal_strong_cochain_brick_2d_2_forman_flow_rate.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_flow_rate_from_potential$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2/forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2/forman_hodge.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03/primal_strong_cochain_brick_2d_2_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03/primal_strong_cochain_brick_2d_2_forman_potential.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  --steady-state-primal-strong-raw $(word 4, $^)\
  --raw $(word 5, $^)\
  --raw > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03/primal_weak_cochain_brick_2d_2_forman_input.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_weak_from_continuous$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2/forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2/forman_vol.txt\
  build/$(MODE)/obj/plugins/diffusion_steady_state_continuous_2d_d00_p03$(.OBJ)\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03\
    build/$(MODE)/lib/plugins/libdiffusion$(.DLL)
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d00_p03\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03/primal_weak_cochain_brick_2d_2_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_primal_weak_solve$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2/forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2/forman_inner.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03/primal_weak_cochain_brick_2d_2_forman_input.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03/primal_weak_cochain_brick_2d_2_forman_flow_rate.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_flow_rate_from_potential$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2/forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2/forman_hodge.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03/primal_weak_cochain_brick_2d_2_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03/primal_weak_cochain_brick_2d_2_forman_potential.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  --steady-state-primal-weak-raw $(word 4, $^)\
  --raw $(word 5, $^)\
  --raw > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03/mixed_weak_cochain_brick_2d_2_forman_input.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_from_continuous$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2/forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2/forman_vol.txt\
  build/$(MODE)/obj/plugins/diffusion_steady_state_continuous_2d_d00_p03$(.OBJ)\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03\
    build/$(MODE)/lib/plugins/libdiffusion$(.DLL)
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 2, $|)\
  diffusion_steady_state_continuous_2d_d00_p03\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03/mixed_weak_cochain_brick_2d_2_forman_solution.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_solve$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2/forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2/forman_inner.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03/mixed_weak_cochain_brick_2d_2_forman_input.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  > $@

build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03/mixed_weak_cochain_brick_2d_2_forman_potential.txt:\
  build/$(MODE)/bin/diffusion_steady_state_discrete_mixed_weak_potential$(.EXE)\
  build/$(MODE)/txt/mesh/brick_2d_2/forman.txt\
  build/$(MODE)/txt/mesh/brick_2d_2/forman_vol.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03/mixed_weak_cochain_brick_2d_2_forman_input.txt\
  build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03/mixed_weak_cochain_brick_2d_2_forman_solution.txt\
  | build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03
	$(INTERPRETER) $<\
  --raw $(word 2, $^)\
  --raw $(word 3, $^)\
  $(word 4, $^)\
  $(word 5, $^)\
  > $@

txt_diffusion_steady_state_continuous_2d_d00_p03:\
  $(_txt_diffusion_steady_state_continuous_2d_d00_p03)

txt_diffusion_steady_state_continuous_2d_d00_p03_clean:
	-$(RM) $(_txt_diffusion_steady_state_continuous_2d_d00_p03)

txt_diffusion_steady_state_continuous_2d_d00_p03_distclean:
	-$(RM) -r build/$(MODE)/txt/diffusion/steady_state/continuous_2d_d00_p03
