# Nome do binário final
TARGET = bin/tp2

# Diretórios
SRC_DIR = src
INC_DIR = include
OUT_DIR = outs
TEST_DIR = tests
BIN_DIR = bin

# Arquivos de origem e objetos
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/%.o, $(SRCS))

# Compilador e flags
CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -Wformat-security -Wconversion -std=c++11 -I$(INC_DIR)

# Regra padrão
all: $(TARGET)

# Linkagem do binário
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilação dos arquivos .cpp em .o
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Diretório binário
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Limpeza dos binários e objetos
clean:
	rm -rf $(BIN_DIR)/*.o $(TARGET)

# Regra phony para garantir que alvos não sejam confundidos com arquivos
.PHONY: all clean
