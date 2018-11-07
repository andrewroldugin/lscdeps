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

CXXFLAGS = -Og -Wextra -Wall -Isrc -Ithird_party/tclap/include -std=c++1z
LDLIBS = -lgtest -lstdc++fs -lstdc++
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

src/main: src/main.o src/lsd/processor.o src/lsd/file.o src/lsd/include_error.o

src/main_tests: src/main_tests.o src/lsd/processor_test.o src/lsd/processor.o \
		src/lsd/file.o src/lsd/include_error.o

clean:
	find src -name *.o -delete
	rm -f src/main src/main_tests

.PHONY: all test clean
