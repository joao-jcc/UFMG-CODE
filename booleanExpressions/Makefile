CC = g++
CFLAGS = -Wall -Iinclude -Ithird_party -std=c++11

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = test

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
EXECUTABLE = $(BIN_DIR)/tp1.out

TEST_SRCS = $(filter-out $(SRC_DIR)/main.cpp, $(wildcard $(SRC_DIR)/*.cpp)) $(wildcard $(TEST_DIR)/*.cpp)
TEST_EXECUTABLE = $(BIN_DIR)/test

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Build the test executable
$(TEST_EXECUTABLE):
	$(CC) -o $(TEST_EXECUTABLE) $(CFLAGS) $(TEST_SRCS)

experimental: CFLAGS += -pg
experimental: all
	gprof $(EXECUTABLE) -a "0 & (1 | ~2)" 100 > info/report01.txt
	gprof $(EXECUTABLE) -s "0 & (1 | ~2)" ae1 > info/report02.txt

run: all
	./$(EXECUTABLE)

test: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

clean:
	rm -rf $(OBJ_DIR)/*.o $(EXECUTABLE) $(TEST_EXECUTABLE)

.PHONY: all clean

# Adicione regras para criar as pastas "obj" e "bin" se não existirem
$(OBJS): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(EXECUTABLE): | $(BIN_DIR)

$(TEST_EXECUTABLE): | $(BIN_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)
