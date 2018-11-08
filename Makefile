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

PRJ = a
TESTS = $(PRJ)_tests
CP = cp $< $@
CXXFLAGS = -Og -Wextra -Wall -Isrc -std=c++1z
LDLIBS = -lstdc++
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

src/main_tests: LDLIBS += -lgtest

test: $(TESTS)
	@./$<

clean:
	find src -name *.o -delete
	rm -f src/main src/main_tests $(PRJ) $(TESTS)

.PHONY: all test clean
