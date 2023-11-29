//
// Created by João Costa on 26/11/23.
//


#include "segTree.hpp"

SegTree::SegTree(int size) : _size(size) {
    seg_array = new Matrix*[4*size];
};

SegTree::~SegTree() {
    delete[] seg_array;
}

Matrix* SegTree::build(int p, int l, int r, Matrix** array) {
    if (l == r) {
//        std::cout << "l: " << l << " r: " << r << std::endl;
//        array[l]->print();
        return seg_array[p] = array[l];
    }

    int m = (l+r) / 2; //floor

    Matrix left_child = *build(2*p, l, m, array);
    Matrix right_child = *build(2*p+1, m+1, r, array);
    Matrix* result = new Matrix(left_child * right_child);

    std::cout << "l: " << l << " r: " << r << std::endl;
    result->print();

    return seg_array[p] = result;

}


Matrix* SegTree::query(int a, int b, int p, int l, int r) {
    if (b < l || r < a) {
        Matrix* result = new Matrix();
        std::cout << "l: " << l << " r: " << r << std::endl;
        result->print();
        return result; // I2
    }

    int m = (l+r) / 2;

    Matrix left_child = *query(a, b, 2*p, l, m);
    Matrix right_child = *query(a, b, 2*p+1, m+1, r);
    Matrix* result = new Matrix(left_child * right_child);

    std::cout << "l: " << l << " r: " << r << std::endl;
    result->print();

    return result;
}


int SegTree::get_size() {
    return _size;
}