//
// Created by João Costa on 26/11/23.
//


#include "segTree.hpp"

SegTree::SegTree(int size) : _size(size) {
    seg_array = new Matrix*[4*size];
    seg_array[0] = new Matrix(); // default identity at zero position
};

SegTree::~SegTree() {
    delete[] seg_array;
}


Matrix* SegTree::build(int p, int l, int r, Matrix** array) {
    if (l == r) {
//        std::cout << "LEAF " << p << std::endl;
//        array[l]->print();
        return seg_array[p] = array[l];
    }

    int m = (l+r) / 2; //floor

    Matrix left_child = *build(2*p, l, m, array);
    Matrix right_child = *build(2*p+1, m+1, r, array);
    Matrix* result = left_child * right_child;

//    std::cout << "INNER " << p << std::endl;
//    result->print();
    return seg_array[p] = result;

}


Matrix* SegTree::query(int a, int b, int p, int l, int r) {
    std::cout << "build(" << a << " " << b << " " << p << " " << l << " " << r << ")" << std::endl;

    // LEAF POSITIVE
    if (l == r && a <= r && b >= r) {
        std::cout << "LEAF POSITIVE" << std::endl;
        return seg_array[p];
    }

    // LEAF NEGATIVE
    if (l == r && !(a == r || b == r)) {
        std::cout << "LEAF NEGATIVE" << std::endl;
        return seg_array[0];
    }

    // Disjoint
    if (a < l && b > r) {
        return seg_array[0]; // identity;
    }

    // Matchs Exactly
    if (a == l && b == r) {
        std::cout << "MATCHS EXACTLY" << std::endl;
        return seg_array[p];
    }




    int m = (l+r) / 2;

    Matrix left_child = *query(a, b, 2*p, l, m);
    Matrix right_child = *query(a, b, 2*p+1, m+1, r);
    Matrix* result = left_child * right_child;


    return result;
}


int SegTree::get_size() {
    return _size;
}

void SegTree::print_node(int position) {
    seg_array[position]->print();
}