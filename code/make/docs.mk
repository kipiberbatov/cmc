.PHONY: docs docs_fast docs_clean

_latex_src := $(shell find code/latex/src -name "*.tex")
_docs_pdf_dependencies := \
  $(_pdf_mesh) \
  $(_pdf_diffusion_steady_state) \
  $(_pdf_diffusion_transient) \

LATEX_COMPILER := TEXINPUTS=./code/latex/src: pdflatex -halt-on-error

build/$(MODE)/empty: | build/$(MODE)
	mkdir -p $@

docs_fast: build/$(MODE)/empty/docs_main_fast.empty
docs: build/$(MODE)/empty/docs_main.empty

build/$(MODE)/empty/docs_pdf_dependencies.empty: $(_docs_pdf_dependencies)
	touch $@

build/$(MODE)/docs: | build/$(MODE)
	mkdir -p $@

build/$(MODE)/empty/docs_main_fast.empty: code/latex/main.tex $(_latex_src) \
  build/$(MODE)/empty/docs_pdf_dependencies.empty \
  | build/$(MODE)/docs build/$(MODE)/empty
	$(LATEX_COMPILER) -output-directory=$(word 1, $|) $<
	touch $@

build/$(MODE)/empty/docs_main.empty: build/$(MODE)/empty/docs_main_fast.empty \
  | build/$(MODE)/docs
	$(LATEX_COMPILER) -output-directory=$| code/latex/main.tex
	touch $@

_docs_empty := \
  build/$(MODE)/empty/docs_main_fast.empty \
  build/$(MODE)/empty/docs_main.empty \

docs_clean:
	-$(RM) -r build/$(MODE)/docs
	-$(RM) $(_docs_empty)
