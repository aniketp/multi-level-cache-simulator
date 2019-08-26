CC = g++
SRC = cache.cpp
PRC = read_traces.c
OBJ = read_traces simulator
CXXFLAGS = -lstdc++fs -std=c++11 -Wall -Wextra

all:
	make process
	make run

process: $(PRC) simulate ./traces
	$(CC) -o read_traces $(PRC)
	./read_traces

simulate: $(SRC)
	$(CC) -o simulator simulator.cpp $(SRC) $(CXXFLAGS)

run: ./output $(OBJ)
	./simulator

.PHONY: clean

clean:
	rm -rf output read_traces simulator fa-lru fa-min
