#
# Copyright (c) 2019, Aditya Rohan
# Copyright (c) 2019, Aniket Pandey
#

CC = g++
CSRC = $(wildcard *.c)
CPPSRC = $(wildcard *.cpp)
SRC-CA = $(wildcard cache/*.cpp)

# Relevant (self-explanatory) directories
CACHE = ./cache
INCLUDE = ./include
TRACES = ./traces
PART2 = ./part2

CFLAGS = -I$(INCLUDE)
_DEPS = cache.h cache-min.h
DEPS = $(patsubst %, $(INCLUDE)/%, $(_DEPS))
CXXFLAGS = -lstdc++fs -std=c++11 -Wall -Wextra

all: clean process simulate part2

process: $(CSRC) $(TRACES) $(DEPS)
	mkdir -p $(OBJ)
	$(CC) -o $@ $<; ./$@

simulate: $(CPPSRC) $(SRC-CA) $(DEPS)
	$(CC) -o $@ $^ $(CXXFLAGS) $(CFLAGS); ./$@

part2: check fa-lru fa-min

fa-lru: $(PART2)/fa-lru.cpp $(SRC-CA) $(DEPS)
	$(CC) -o $@ $^ $(CXXFLAGS) $(CFLAGS); ./$@

fa-min: $(PART2)/fa-min.cpp $(SRC-CA) $(DEPS)
	$(CC) -o $@ $^ $(CXXFLAGS) $(CFLAGS); ./$@

.PHONY: clean check

check: SHELL:=/bin/bash
check:
	@echo Warning: Part-2 would take more than 5 hours on a normal \
	machine. Continue? [Y/n]
	@read line; if [ $$line == "n" ]; then echo TIP: Better to run \
	build instructions individually; echo; exit 1 ; fi

clean:
	rm -rf output simulate process fa-lru fa-min
