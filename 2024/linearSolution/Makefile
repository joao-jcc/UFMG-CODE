# Variables
CC = g++
FLAGS = -std=c++11

BIN_DIR := bin
INCLUDE_DIR := include
EXTERNAL_DIR := third_party
SOURCE_DIR := source
TEST_DIR := tests
EXECUTABLE := $(BIN_DIR)/main
TEST_EXECUTABLE := $(BIN_DIR)/test_main

# Source files for the main program
MAIN_SOURCES := $(wildcard $(SOURCE_DIR)/*.cpp)
# Source files for the test program, excluding main.cpp
TEST_SOURCES := $(filter-out $(SOURCE_DIR)/main.cpp,$(MAIN_SOURCES))

# Build the main program
all: $(EXECUTABLE)

$(EXECUTABLE): $(MAIN_SOURCES) $(INCLUDE_DIR)/*.hpp
	$(CC) $(FLAGS) -o $(EXECUTABLE) $(MAIN_SOURCES) -I$(INCLUDE_DIR)

# Build the test program
test: $(TEST_EXECUTABLE)

$(TEST_EXECUTABLE): $(TEST_DIR)/*.cpp $(TEST_SOURCES) $(INCLUDE_DIR)/*.hpp $(EXTERNAL_DIR)/doctest.h
	$(CC) $(FLAGS) -o $(TEST_EXECUTABLE) $(TEST_DIR)/*.cpp $(TEST_SOURCES) -I$(INCLUDE_DIR) -I$(EXTERNAL_DIR)

# Run the main program
run: $(EXECUTABLE)
	./$(EXECUTABLE)

# run test program
run_test: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

# Clean compiled files
clean:
	rm -f $(BIN_DIR)/*
