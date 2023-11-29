//
// Created by João Costa on 26/11/23.
//

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <stdexcept>

#include "utils.hpp"


class MatrixMultiplicationException : public std::runtime_error {
public:
    MatrixMultiplicationException(const std::string& message) : std::runtime_error(message) {

    };

};



class Matrix {
public:
    Matrix(int row=2, int col=2, bool identity=true);
    Matrix(Tuple tuple);

    ~Matrix();

    void print();
    void read();

    Tuple operator*(const Matrix& other);

    int get_rows() const;
    int get_cols() const;

    LI** get_matrix() const;

private:
    LI** _matrix;
    int _rows;
    int _cols;
};


#endif //MATRIX_HPP
