SHELL := /bin/bash
CC = g++
CFLAGS = -std=c++11 -Wall -ggdb

EXE = tp2.out
CPP = tp2.cpp

all: $(EXE)

tp2.out: $(CPP)
	$(CC) $(CPP) $(CFLAGS) -o tp2.out

run: $(EXE)
	./$(EXE)

test: $(EXE)
	for file in tests/* ; do echo -e "\n\n$$file"; time ./tp2.out < $$file; done

clean:
	rm -f tp2.out