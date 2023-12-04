//
// Created by João Costa on 03/12/23.
//

#include "simpleVector.hpp"

// Construtor da classe com um tamanho padrão opcional
SimpleVector::SimpleVector(int n) : _n(n), _vector(nullptr) {
    // Inicializa o vetor chamando o método build
    build();
}

// Destrutor
SimpleVector::~SimpleVector() {
    // Desaloca o vetor de matrizes
    delete[] _vector;
}

// Inicializa o vetor com matrizes padrão (matriz identidade)
void SimpleVector::build() {
    // Aloca o vetor de matrizes
    _vector = new Matrix[_n];

    // Inicializa cada elemento do vetor como matriz identidade
    for (int i = 0; i < _n; ++i) {
        _vector[i] = Matrix();
    }
}

// Atualiza o vetor na posição i com uma matriz
void SimpleVector::update(int i, Matrix matrix) {
    _vector[i] = matrix;
}

// Realiza uma consulta no vetor para o intervalo [i, j]
Matrix SimpleVector::query(int i, int j) {
    Matrix matrix;

    // Multiplica as matrizes no intervalo [i, j]
    for (; i <= j; ++i) {
        matrix = matrix * _vector[i];
    }

    return matrix;
}

// Imprime o vetor
void SimpleVector::print() {
    for (int i = 0; i < _n; ++i) {
        _vector[i].print();
    }
}
