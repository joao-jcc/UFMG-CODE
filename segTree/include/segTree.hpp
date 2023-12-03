//
// Created by João Costa on 26/11/23.
//

#ifndef SEGTREE_HPP
#define SEGTREE_HPP

#include "matrix.hpp"

class Matrix;

class SegTree {
public:
    SegTree(int size);
    ~SegTree();

    int get_size();

    Matrix* build(int p, int l, int r, Matrix** array);

    Matrix* query(int a, int b, int p, int l, int r);

    Matrix* update(int i, Matrix* x, int p, int l, int r);

    void print_node(int position);

private:
    int _size;
    Matrix** seg_array;



};

#endif
