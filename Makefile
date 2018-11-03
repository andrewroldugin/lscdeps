# Makefile for small projects.
#
# Project can be built with gcc and clang compiler.
# g++ is used by default.
# To use clang set CXX:
# make CXX=clang++
#
# $@ name of the target
# $^ name of all prerequisites with duplicates removed
# $< name of the first prerequisite

CXXFLAGS = -Og -Wextra -Wall -Isrc -std=c++1z
LDLIBS = -lgtest -lstdc++
GCC_CXXFLAGS =
CLANG_CXXFLAGS =

ifeq ($(CXX),clang++)
	CXXFLAGS += $(CLANG_CXXFLAGS)
else
	CXXFLAGS += $(GCC_CXXFLAGS)
endif

all: src/main

test: src/main_tests
	@$<

clean:
	find src -name *.o -delete
	rm -f src/main src/main_tests

.PHONY: all test clean
