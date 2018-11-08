# Makefile for small projects.
#
# Project can be built with gcc and clang compiler.
# g++ is used by default.
# To use clang set CXX:
# make CXX=clang++ CC=clang
#
# $@ name of the target
# $^ name of all prerequisites with duplicates removed
# $< name of the first prerequisite

PRJ = lsd
TESTS = $(PRJ)_tests
CP = cp $< $@
CXXFLAGS = -Og -Wextra -Wall -Isrc -Ithird_party/tclap/include -std=c++1z
LDLIBS = -lgtest -lstdc++fs -lstdc++
OBJ = src/lsd/processor.o src/lsd/file.o src/lsd/include_error.o
GCC_CXXFLAGS =
CLANG_CXXFLAGS =

ifeq ($(CXX),clang++)
	CXXFLAGS += $(CLANG_CXXFLAGS)
else
	CXXFLAGS += $(GCC_CXXFLAGS)
endif

all: $(PRJ) $(TESTS)

$(PRJ): src/main
	$(CP)

$(TESTS): src/main_tests
	$(CP)

test: $(TESTS)
	@./$<

src/main: src/main.o $(OBJ)

src/main_tests: src/main_tests.o $(OBJ)

clean:
	find src -name *.o -delete
	rm -f src/main src/main_tests $(PRJ) $(TESTS)

.PHONY: all test clean
