#include "utils.hpp"

// Função para alocar um array bidimensional de inteiros longos
LI** allocate_array2D(int rows, int cols) {
    // Aloca um array de ponteiros para linhas
    LI** matrix = new LI*[rows];

    // Para cada linha, aloca um array de inteiros longos
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new LI[cols];
    }

    // Retorna o ponteiro para a matriz alocada
    return matrix;
}

// Função para desalocar um array bidimensional de inteiros longos
void deallocate_array2D(LI** array, int rows) {
    // Para cada linha, desaloca o array de inteiros longos
    for (int i = 0; i < rows; ++i) {
        delete[] array[i];
    }

    // Desaloca o array de ponteiros para linhas
    delete[] array;
}
