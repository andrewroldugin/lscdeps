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

ODIR = out
ONAME = a
OPATH = $(ODIR)/$(ONAME)
OTEST = $(OPATH)_test
CXX = g++
CXXFLAGS = -Og -Wextra -Wall
BUILD = $(CXX) $(CXXFLAGS) $^ -o $@
GCC_CXXFLAGS =
CLANG_CXXFLAGS =

CXXFLAGS += $(GCC_CXXFLAGS)

ifeq ($(CXX),clang++)
	CXXFLAGS -= $(GCC_CXXFLAGS)
	CXXFLAGS += $(CLANG_CXXFLAGS)
endif

all: $(OPATH)

$(OPATH): src/main.cc
	$(BUILD)

test: $(OTEST)
	@$<

$(OTEST): test/main.cc
	$(BUILD) -Isrc -lgtest

clean:
	rm -f $(OPATH) $(OTEST)

.PHONY: all test clean
