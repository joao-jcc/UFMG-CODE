CC = g++
CFLAGS = -Wall -Iinclude -std=c++17

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
EXECUTABLE = $(BIN_DIR)/tp3.out

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@


run: all
	./$(EXECUTABLE)


time:
	$(CC) $(CFLAGS) -o experiments/time experiments/time.cpp src/matrix.cpp src/utils.cpp src/segTree.cpp src/simpleVector.cpp
	./experiments/time

clean:
	rm -rf $(OBJ_DIR)/*.o $(EXECUTABLE) $(TEST_EXECUTABLE)

.PHONY: all clean

# Adicione regras para criar as pastas "obj" e "bin" se não existirem
$(OBJS): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(EXECUTABLE): | $(BIN_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)
