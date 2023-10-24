CC = g++
CFLAGS = -Wall -Iinclude -std=c++11

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
EXECUTABLE = $(BIN_DIR)/pa08.out


all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@



run: all
	./$(EXECUTABLE)


clean:
	rm -rf $(OBJ_DIR)/*.o $(EXECUTABLE)


$(OBJS): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(EXECUTABLE): | $(BIN_DIR)

$(TEST_EXECUTABLE): | $(BIN_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)