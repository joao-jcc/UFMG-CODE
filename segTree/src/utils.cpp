#include "utils.hpp"

LI** allocate_array2D(int rows, int cols) {
    LI** matrix = new LI*[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new LI[cols];
    }
    return matrix;
}

void deallocate_array2D(LI** array, int row, int col) {
    for (int i = 0; i < row; ++i) {
        delete[] array[i];
    }

    delete[] array;
}
