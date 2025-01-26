CC = g++
CCFLAGS = -std=c++11
FLAGS = -Wall -Wextra -Wpedantic -Wformat-security -Wconversion -Werror
INC = include
SRC = src
EXE = main
SRC_FILES = $(wildcard $(SRC)/*.cpp)

## exp ##
EXP_FOLDER = experiments
INC_EXP = $(INC) $(EXP_FOLDER)
EXP_FILES := $(wildcard $(EXP_FOLDER)/*.cpp) $(SRC_FILES)
EXP_FILES := $(filter-out $(SRC)/main.cpp, $(EXP_FILES))
EXP_EXE = exp
## --- ##


all: $(EXE)

$(EXE): $(SRC_FILES)
	$(CC) $(CCFLAGS) -o $@ $^ -I$(INC) $(FLAGS)

run: $(EXE)
	./$(EXE)

## exp ##
time: $(EXP_EXE)

$(EXP_EXE): $(EXP_FILES)
	$(CC) $(CCFLAGS) -o $@ $^ $(addprefix -I, $(INC_EXP)) $(FLAGS)
## --- ##

clean:
	rm -f $(EXE) $(EXP_EXE)
