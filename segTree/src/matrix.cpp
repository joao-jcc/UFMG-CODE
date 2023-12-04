
#include "matrix.hpp"

Matrix::Matrix(int rows, int cols, bool identity) : _rows(rows), _cols(cols) {
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
    deallocate_array2D(_matrix, _rows);
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
    LI** array2 = other.get_array();

    LI** result = allocate_array2D(_rows, other.get_cols());

    for (int i = 0; i < _rows; ++i) {
        for (int j = 0; j < other.get_cols(); ++j) {
        result[i][j] = 0;
            for (int k = 0; k < _cols; ++k) {
            result[i][j] += array1[i][k] % (int)(1e8) * array2[k][j] % (int)(1e8);
            result[i][j] %= (int)(1e8);
            }
        }
    }

    return new Matrix(result, _rows, other.get_cols());
}

Vector2D Matrix::operator*(const Vector2D& other) const {

    LI cord_x = (_matrix[0][0] * other.x + _matrix[0][1] * other.y) % (int)(1e8);
    LI cord_y = (_matrix[1][0] * other.x + _matrix[1][1] * other.y) % (int)(1e8);

    return Vector2D(cord_x, cord_y);
}


int Matrix::get_rows() const {
    return _rows;
}

int Matrix::get_cols() const {
    return _cols;
}

LI** Matrix::get_array() const {
    return _matrix;
}

