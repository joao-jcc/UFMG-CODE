//
// Created by João Costa on 26/11/23.
//

#ifndef UTILS_HPP
#define UTILS_HPP

typedef long int LI;
struct Tuple{
    LI** array;
    int row;
    int col;
};

inline LI** allocate_array2D(int rows, int cols) {
    LI** matrix = new LI*[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new LI[cols];
    }
    return matrix;
};


inline void deallocate_array2D(LI** array, int row, int col) {
    for (int i=0; i < row; ++i) {
        delete[] array[i];
    }

    delete[] array;
};

#endif //UTILS_HPP
