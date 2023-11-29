//
// Created by João Costa on 26/11/23.
//

#include <stdlib.h>
#include "matrix.hpp"
#include "segTree.hpp"

int main(int argc, char* argv[]) {

    Matrix matrix0(2, 2, false);
    Matrix matrix1(2, 2, false);
    Matrix matrix2(2, 2, false);
    Matrix matrix3(2, 2, false);

    matrix0.read();
    matrix1.read();
    matrix2.read();
    matrix3.read();


    Matrix* array[4] = {&matrix0, &matrix1, &matrix2, &matrix3};


    SegTree seg(4);
    seg.build(1, 0, 4-1, array);

    int a  = (int)strtol(argv[1], NULL, 10);
    int b = (int)strtol(argv[2], NULL, 10);

    seg.query(a, b, 1,0, 3)->print();


    return 0;
}