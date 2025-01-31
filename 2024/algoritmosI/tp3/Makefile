CC = g++
CCFLAGS = -std=c++17
FLAGS = -Wall -Wextra -Wpedantic -Wformat-security -Wconversion -Werror
INC = include
SRC = src
EXE = tp3
SRC_FILES = $(wildcard $(SRC)/*.cpp)


all: $(EXE)

$(EXE): $(SRC_FILES)
	$(CC) $(CCFLAGS) -o $@ $^ -I$(INC) $(FLAGS)

run: $(EXE)
	./$(EXE)


clean:
	rm -f $(EXE)
