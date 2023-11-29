
#include "matrix.hpp"

Matrix::Matrix(int rows, int cols, bool identity) : _rows(rows), _cols(cols) {
    if (rows != cols) {
        throw(NotSquareMatrixException("Matrix must be Square"));
    }
    _matrix = allocate_array2D(_rows, _cols);

    if (identity) {
        for (int i = 0; i < _rows; ++i) {
             for (int j = 0; j < _cols; ++j) {
                _matrix[i][j] = (i == j) ? (LI) 1 : (LI) 0;
            }
        }
    }
}

Matrix::Matrix(LI** array, int rows, int cols) : _rows(rows), _cols(cols) {
    _matrix = array;
}


Matrix::~Matrix() {
//    std::cout << "destroying matrix" << std::endl;
//    deallocate_array2D(_matrix, _rows, _cols);
}


void Matrix::read() {

    for (int i=0; i < _rows; ++i) {
        for (int j=0; j < _cols; ++j) {
            std::cin >> _matrix[i][j];
        }
    }
}

void Matrix::print() {
    for (int i = 0; i < _rows; ++i) {
        for (int j = 0; j < _cols; ++j) {
            std::cout << _matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


Matrix* Matrix::operator*(const Matrix& other) {

    if (_cols != other.get_rows()) {
        throw(MatrixMultiplicationException("Matrix dimensions are not compatible for multiplication."));
    }


    LI** array1 = _matrix;
    LI** array2 = other.get_matrix();

    LI** result = allocate_array2D(_rows, other.get_cols());

    for (int i = 0; i < _rows; ++i) {
        for (int j = 0; j < other.get_cols(); ++j) {
        result[i][j] = 0;
            for (int k = 0; k < _cols; ++k) {
            result[i][j] += array1[i][k] * array2[k][j];
            }
        }
    }

    return new Matrix(result, _rows, other.get_cols());
}

int Matrix::get_rows() const {
    return _rows;
}

int Matrix::get_cols() const {
    return _cols;
}

LI** Matrix::get_matrix() const {
    return _matrix;
}

