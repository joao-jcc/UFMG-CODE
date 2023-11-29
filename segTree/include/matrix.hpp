//
// Created by João Costa on 26/11/23.
//

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <stdexcept>

#include "utils.hpp"


class MatrixMultiplicationException : public std::exception {
public:
    // Constructor that takes a custom error message
    explicit MatrixMultiplicationException(const char* message) : errorMessage(message) {}

    // Override the what() function to provide error message
    const char* what() const noexcept override {
        return errorMessage.c_str();
    }

private:
    std::string errorMessage;
};

class NotSquareMatrixException : public std::exception {
public:
    // Constructor that takes a custom error message
    explicit NotSquareMatrixException(const char* message) : errorMessage(message) {}

    // Override the what() function to provide error message
    const char* what() const noexcept override {
        return errorMessage.c_str();
    }

private:
    std::string errorMessage;
};



class Matrix {
public:
    explicit Matrix(int rows=2, int cols=2, bool identity=true);
    Matrix(LI** array, int rows, int cols);

    ~Matrix();

    void print();
    void read();

    Matrix* operator*(const Matrix& other);

    int get_rows() const;
    int get_cols() const;

    LI** get_matrix() const;

private:
    LI** _matrix;
    int _rows;
    int _cols;
};


#endif //MATRIX_HPP
