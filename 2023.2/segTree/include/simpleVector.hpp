//
// Created by João Costa on 03/12/23.
//

// Evitar múltiplas inclusões do mesmo cabeçalho
#ifndef SIMPLEVECTOR_HPP
#define SIMPLEVECTOR_HPP

#include "matrix.hpp"

// Definição da classe SimpleVector
class SimpleVector {
public:
    // Construtor da classe com um tamanho padrão opcional
    SimpleVector(int n = 0);

    // Destrutor
    ~SimpleVector();

    // Inicializa o vetor
    void build();

    // Atualiza o vetor na posição i com uma matriz
    void update(int i, Matrix matrix);

    // Realiza uma consulta no vetor para o intervalo [i, j]
    Matrix query(int i, int j);

    // Imprime o vetor
    void print();

    // Obtém o tamanho do vetor
    int get_size() {
        return _n;
    }

    // Obtém o ponteiro para o vetor de matrizes
    Matrix* get_vector() {
        return _vector;
    }

private:
    // Tamanho do vetor
    int _n;

    // Array de matrizes
    Matrix* _vector;
};

#endif // SIMPLEVECTOR_HPP
