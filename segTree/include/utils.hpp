#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>

typedef long int LI;

struct Vector2D {
    LI x, y;

    // Constructor
    Vector2D(LI x=0, LI y=0) : x(x), y(y) {}

    void print() {
        std::cout << x << " " << y << std::endl;
    }

};


LI** allocate_array2D(int rows, int cols);

void deallocate_array2D(LI** array, int row, int col);


#endif // UTILS_HPP
