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
CXXFLAGS = -Og -Wextra -Wall -Isrc
BUILD = $(CXX) $(CXXFLAGS) $^ -o $@
GCC_CXXFLAGS =
CLANG_CXXFLAGS =
SRC =

ifeq ($(CXX),clang++)
	CXXFLAGS += $(CLANG_CXXFLAGS)
else
	CXXFLAGS += $(GCC_CXXFLAGS)
endif

all: $(ODIR) $(OPATH)

$(ODIR):
	mkdir -p $@

$(OPATH): src/main.cc $(SRC)
	$(BUILD)

test: $(ODIR) $(OTEST)
	@$(OTEST)

$(OTEST): src/main_test.cc $(SRC)
	$(BUILD) -lgtest

clean:
	rm -rf $(ODIR)

.PHONY: all test clean
