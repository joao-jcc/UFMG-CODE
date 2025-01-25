CC = g++
CCFLAGS = -std=c++11
FLAGS = -Wall -Wextra -Wpedantic -Wformat-security -Wconversion -Werror
INC = include
SRC = src
EXE = main

all:
	$(CC) $(CCFLAGS) -o $(EXE) $(SRC)/* -I$(INC) $(FLAGS)

run: all
	./$(EXE)

clean:
	rm $(EXE)