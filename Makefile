.PHONY: all self-test

all: self-test

self-test: test
	./test
	-rm test

test: test.cpp tiny_unit.h
	${CXX} -Wall $< -o $@
