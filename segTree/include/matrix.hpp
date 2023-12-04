// Matrix.hpp

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <stdexcept>
#include "utils.hpp"

// Exceção personalizada para multiplicação de matrizes
class MatrixMultiplicationException : public std::exception {
public:
    explicit MatrixMultiplicationException(const char* message) : errorMessage(message) {}

    const char* what() const noexcept override {
        return errorMessage.c_str();
    }

private:
    std::string errorMessage;
};

// Definição da classe Matrix
class Matrix {
public:
    // Construtor da matriz com valores padrão
    explicit Matrix(int rows = 2, int cols = 2, bool identity = true);

    // Construtor de cópia
    Matrix(const Matrix& other);

    // Destrutor
    ~Matrix();

    // Imprime a matriz
    void print();

    // Lê os valores da matriz a partir da entrada padrão
    void read();

    // Sobrecarga do operador de atribuição
    Matrix& operator=(const Matrix& other);

    // Sobrecarga do operador de multiplicação de matrizes
    Matrix operator*(const Matrix& other);

    // Sobrecarga do operador de multiplicação de matriz por vetor
    Vector2D operator*(const Vector2D& other) const;

    // Obtém o número de linhas da matriz
    int get_rows() const;

    // Obtém o número de colunas da matriz
    int get_cols() const;

    // Obtém o array bidimensional que armazena os elementos da matriz
    LI** get_array() const;

private:
    // Ponteiro para o array bidimensional que armazena os elementos da matriz
    LI** _matrix;

    // Número de linhas da matriz
    int _rows;

    // Número de colunas da matriz
    int _cols;
};

#endif // MATRIX_HPP
