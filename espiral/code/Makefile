# Compilador e flags
CC = gcc
CFLAGS = -Wall

# Diretórios
SRC_DIR = src
BIN_DIR = bin

# Nome dos executáveis
TRIANGULAR_EXEC = $(BIN_DIR)/esptriangular
SQUARE_EXEC = $(BIN_DIR)/espquadrada

all: $(TRIANGULAR_EXEC) $(SQUARE_EXEC)

$(TRIANGULAR_EXEC): $(SRC_DIR)/esptriangular.c
	$(CC) $(CFLAGS) -o $@ $^

$(SQUARE_EXEC): $(SRC_DIR)/espquadrada.c
	$(CC) $(CFLAGS) -o $@ $^

run_triangular: $(TRIANGULAR_EXEC)
	$(TRIANGULAR_EXEC) $(ARGS)

run_square: $(SQUARE_EXEC)
	$(SQUARE_EXEC) $(ARGS)

clean:
	rm -f $(TRIANGULAR_EXEC) $(SQUARE_EXEC)

# Instruções para Compilação e Execução
.PHONY: help
help:
	@echo "Uso:"
	@echo "make run_triangular ARGS=<seu_argumento>"
	@echo "make run_square ARGS=<seu_argumento>"
	@echo "make clean"
