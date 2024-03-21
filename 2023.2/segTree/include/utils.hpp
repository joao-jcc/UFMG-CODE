#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>

// Definindo um tipo de dado para inteiros longos
typedef long int LI;

// Estrutura para representar um vetor bidimensional
struct Vector2D {
    LI x, y;

    // Construtor da estrutura
    Vector2D(LI x = 0, LI y = 0) : x(x), y(y) {}

    // Método para imprimir as coordenadas do vetor
    void print() {
        std::cout << x << " " << y << std::endl;
    }
};

// Função para alocar um array bidimensional de inteiros longos
LI** allocate_array2D(int rows, int cols);

// Função para desalocar um array bidimensional de inteiros longos
void deallocate_array2D(LI** array, int rows);

#endif // UTILS_HPP
