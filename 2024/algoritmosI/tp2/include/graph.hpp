#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

// Classe que representa um grafo orientado para cálculo de fluxo.
class Graph {
public:
    Graph(); // Construtor que inicializa o grafo.
    void print(); // Imprime o grafo e o grafo residual.

private:
    void _read(); // Método auxiliar para leitura dos dados do grafo.

public:
    size_t N; // Número total de vértices (incluindo gerador-base e sumidouro).
    size_t M; // Número de arestas.
    std::vector<std::vector<size_t>> graph; // Matriz de adjacência do grafo.
    std::vector<std::vector<size_t>> graphR; // Matriz de adjacência do grafo residual.
    std::vector<bool> isGenerator; // Marca quais vértices são geradores.
};

#endif // GRAPH_HPP
