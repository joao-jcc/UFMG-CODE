#ifndef UTILS_HPP
#define UTILS_HPP

typedef long int LI;

LI** allocate_array2D(int rows, int cols);

void deallocate_array2D(LI** array, int row, int col);

#endif // UTILS_HPP
