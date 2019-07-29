SRCS=$(shell find src/) $(shell find tex/)

default:

build/main.pdf: $(SRCS) Makefile gen.py scl.yaml
	mkdir -p build/
	python2 environ.py > build/environ.tex
	python2 gen.py > build/code.tex
	cp tex/* build/
	cd build && xelatex main.tex
	cd build && xelatex main.tex
	cp build/main.pdf releases/latest.pdf

test:

.PHONY: clean check open
check:
	true # code valid check

clean:
	rm -rf build/

open: build/main.pdf
	xdg-open build/main.pdf

