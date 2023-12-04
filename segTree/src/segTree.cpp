//
// Created by João Costa on 26/11/23.
//


#include "segTree.hpp"

SegTree::SegTree(int size) : _size(size) {
    seg_array = new Matrix*[4*size];

    for (int i=0; i < 4*size; ++i) {
        seg_array[i] = new Matrix(); // identity
    }
};

SegTree::~SegTree() {
    for (int i=0; i < 4*_size; ++i) {
        delete seg_array[i];
    }

    delete[] seg_array;
}


Matrix* SegTree::build(int p, int l, int r, Matrix** array) {
    if (l == r) {
        delete seg_array[p];
        return seg_array[p] = array[l];
    }

    int m = (l+r) / 2; //floor

    Matrix left_child = *build(2*p, l, m, array);
    Matrix right_child = *build(2*p+1, m+1, r, array);
    Matrix* result = left_child * right_child;

    delete seg_array[p];
    return seg_array[p] = result;

}


Matrix* SegTree::query(int a, int b, int p, int l, int r) {
    // Disjoint
    if (r < a || l > b) {
        return seg_array[0]; // identity;
    }

    // Contains
    if (a <= l && r <= b) {
        return seg_array[p];
    }


    int m = (l+r) / 2;

    Matrix* left_child = query(a, b, 2*p, l, m);
    Matrix* right_child = query(a, b, 2*p+1, m+1, r);
    Matrix* result = (*left_child) * (*right_child);


    return result;
}


Matrix* SegTree::update(int i, Matrix* x, int p, int l, int r) {
    if (i < l || r < i) {
        return seg_array[p];
    }

    if (l == r) {
        delete seg_array[p];
        return seg_array[p] = x;
    }

    int m = (l+r)/2;
    Matrix left_child = *update(i, x, 2*p, l, m);
    Matrix right_child = *update(i, x, 2*p+1, m+1, r);

    delete seg_array[p];
    return seg_array[p] = left_child * right_child;
}


int SegTree::get_size() {
    return _size;
}

void SegTree::print_node(int position) {
    seg_array[position]->print();
}