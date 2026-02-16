.PHONY: website website_fast website_clean

build/$(MODE)/website: | build
	mkdir -p $@

_website_resources := \
  build/$(MODE)/website/index.html \
  build/$(MODE)/website/style.css \

build/$(MODE)/website/index.html: code/html/index.html | build/$(MODE)/website
	cp $< $|

build/$(MODE)/website/style.css: code/css/style.css | build/$(MODE)/website
	cp $< $|

website_fast: build/$(MODE)/empty/website_fast.empty
website: build/$(MODE)/empty/website.empty

build/$(MODE)/empty/website_fast.empty: $(_website_resources) \
  build/$(MODE)/empty/docs_main_fast.empty
	cp build/$(MODE)/docs/main.pdf build/$(MODE)/website
	touch $@

build/$(MODE)/empty/website.empty: $(_website_resources) \
  build/$(MODE)/empty/docs_main.empty
	cp build/$(MODE)/docs/main.pdf build/$(MODE)/website
	touch build/$(MODE)/empty/website_fast.empty
	touch $@

_website_empty := \
  build/$(MODE)/empty/website_fast.empty \
  build/$(MODE)/empty/website.empty \

website_clean:
	-$(RM) -r build/$(MODE)/website
	-$(RM) $(_website_empty)
