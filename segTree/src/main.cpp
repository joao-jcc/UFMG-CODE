//
// Created by João Costa on 26/11/23.
//

#include <iostream>
#include "matrix.hpp"
#include "segTree.hpp"

int main(void) {

    int n, q;
    std::cin >> n >> q;

    SegTree seg_tree(n);

    char operation;
    while(q--) {
        std::cin >> operation;

        if (operation == 'u') {
            // index
            int i;
            std::cin >> i;

            // matrix
            Matrix* matrix = new Matrix(2, 2, false);
            matrix->read();

            seg_tree.update(i, matrix, 1, 0, n-1);

        }

        else if (operation == 'q') {
            int born_time, death_time;
            Vector2D point;
            std::cin >> born_time >> death_time >> point.x >> point.y;

            Matrix* matrix = seg_tree.query(born_time, death_time, 1, 0, n-1);

            Vector2D new_point = (*matrix) * point;
            new_point.print();

        }
    }

    return 0;

}