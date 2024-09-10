// Matrix.cpp

#include "matrix.hpp"

// Construtor da matriz com valores padrão
Matrix::Matrix(int rows, int cols, bool identity) : _rows(rows), _cols(cols) {
    // Aloca o array bidimensional para armazenar os elementos da matriz
    _matrix = allocate_array2D(_rows, _cols);

    // Inicializa a matriz como matriz identidade, se necessário
    if (identity) {
        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < _cols; ++j) {
                _matrix[i][j] = (i == j) ? (LI)1 : (LI)0;
            }
        }
    }
}

// Construtor de cópia
Matrix::Matrix(const Matrix& other) : _rows(other._rows), _cols(other._cols) {

    // Aloca o array bidimensional e copia os elementos da matriz
    _matrix = allocate_array2D(_rows, _cols);
    for (int i = 0; i < _rows; ++i) {
        for (int j = 0; j < _cols; ++j) {
            _matrix[i][j] = other._matrix[i][j];
        }
    }
}

// Destrutor
Matrix::~Matrix() {
    // Desaloca o array bidimensional
    deallocate_array2D(_matrix, _rows);
}

// Lê os valores da matriz a partir da entrada padrão
void Matrix::read() {
    for (int i = 0; i < _rows; ++i) {
        for (int j = 0; j < _cols; ++j) {
            std::cin >> _matrix[i][j];
        }
    }
}

// Imprime a matriz
void Matrix::print() {
    for (int i = 0; i < _rows; ++i) {
        for (int j = 0; j < _cols; ++j) {
            std::cout << _matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Sobrecarga do operador de atribuição
Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        // Desaloca a matriz existente
        deallocate_array2D(_matrix, _rows);

        // Copia as dimensões
        _rows = other._rows;
        _cols = other._cols;

        // Aloca uma nova matriz
        _matrix = allocate_array2D(_rows, _cols);

        // Copia os elementos da matriz
        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < _cols; ++j) {
                _matrix[i][j] = other._matrix[i][j];
            }
        }
    }
    return *this;
}

// Sobrecarga do operador de multiplicação de matrizes
Matrix Matrix::operator*(const Matrix& other) {
    if (_cols != other.get_rows()) {
        throw MatrixMultiplicationException("As dimensões das matrizes não são compatíveis para multiplicação.");
    }

    // Cria a matriz resultado
    Matrix result(_rows, other.get_cols());

    // Realiza a multiplicação de matrizes
    for (int i = 0; i < _rows; ++i) {
        for (int j = 0; j < other.get_cols(); ++j) {
            result._matrix[i][j] = 0;
            for (int k = 0; k < _cols; ++k) {
                result._matrix[i][j] += _matrix[i][k] % static_cast<LI>(1e8) * other._matrix[k][j] % static_cast<LI>(1e8);
                result._matrix[i][j] %= static_cast<LI>(1e8);
            }
        }
    }

    return result;
}

// Sobrecarga do operador de multiplicação de matriz por vetor
Vector2D Matrix::operator*(const Vector2D& other) const {
    // Calcula as coordenadas resultantes após a multiplicação
    LI cord_x = (_matrix[0][0] * other.x + _matrix[0][1] * other.y) % static_cast<LI>(1e8);
    LI cord_y = (_matrix[1][0] * other.x + _matrix[1][1] * other.y) % static_cast<LI>(1e8);

    // Retorna um novo vetor com as coordenadas resultantes
    return Vector2D(cord_x, cord_y);
}

// Obtém o número de linhas da matriz
int Matrix::get_rows() const {
    return _rows;
}

// Obtém o número de colunas da matriz
int Matrix::get_cols() const {
    return _cols;
}

// Obtém o array bidimensional que armazena os elementos da matriz
LI** Matrix::get_array() const {
    return _matrix;
}
