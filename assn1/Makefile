CC = g++
SRC = simulator.cpp
PRC = read_traces.c
OBJ = read_traces simulator
CXXFLAGS = -lstdc++fs -std=c++11 -Wall

all:
	make process
	make run

process: $(PRC) simulator ./traces
	$(CC) -o read_traces $(PRC)
	./read_traces

simulator: $(SRC)
	$(CC) -o simulator $(SRC) $(CXXFLAGS)

run: ./output $(OBJ)
	./simulator

.PHONY: clean

clean:
	rm -rf output read_traces simulator
