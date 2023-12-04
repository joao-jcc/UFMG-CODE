//
// Created by João Costa on 03/12/23.
//

#include "simpleVector.hpp"

SimpleVector::SimpleVector(int n) : _n(n), _vector(nullptr) {
    build();
}

SimpleVector::~SimpleVector() {
    for (int i=0; i < _n; ++i) {
        delete _vector[i];
    }

    delete[] _vector;
}

void SimpleVector::build() {
    _vector = new Matrix*[_n];
    for (int i=0; i < _n; ++i) {
        _vector[i] = new Matrix();
    }
}

void SimpleVector::update(int i, Matrix *matrix) {
    delete _vector[i];
    _vector[i] = matrix;
}

Matrix* SimpleVector::query(int i, int j) {
    Matrix* matrix = new Matrix();
    for (; i <= j; ++i) {
        Matrix* temp = (*matrix) * (*_vector[i]);
        delete matrix;
        matrix = temp;
    }

    return matrix;
}

void SimpleVector::print() {
    for (int i=0; i < _n; ++i) {
        _vector[i]->print();
    }
}



