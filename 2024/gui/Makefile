CC = g++
FLAGS = -std=c++11


WX_CONFIG := wx-config
WX_CXXFLAGS := $(shell $(WX_CONFIG) --cxxflags)
WX_LIBS := $(shell $(WX_CONFIG) --libs)


EXECUTABLE := bin/main

# Source files for the main program
MAIN_SOURCES := source/*.cpp

# Include headers
INCLUDE_DIR := include


# Build the main program
all: $(EXECUTABLE)

$(EXECUTABLE): $(MAIN_SOURCES)
	$(CC) $(FLAGS) $(WX_CXXFLAGS)  -o $(EXECUTABLE) $(MAIN_SOURCES) $(WX_LIBS) -I$(INCLUDE_DIR)

# run
run: $(EXECUTABLE)
	./$(EXECUTABLE)

# clean
clean:
	rm -rf $(EXECUTABLE)