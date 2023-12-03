#include "utils.hpp"

LI** allocate_array2D(int rows, int cols) {
    LI** matrix = new LI*[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new LI[cols];
    }
    return matrix;
}