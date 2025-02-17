#include "graph.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <limits>
#include <cstddef>

#define _ ios_base::sync_with_stdio(0);cin.tie(0); // Otimização para entrada/saída padrão.

// Construtor: inicializa o grafo a partir da entrada padrão.
Graph::Graph() {
    _read();
}

// Lê os dados do grafo e inicializa as estruturas internas.
void Graph::_read() {
    if (!std::cin) {
        std::cerr << "Error reading input!" << std::endl;
        exit(1);
    }

    std::cin >> N >> M; // Lê o número de vértices e arestas.
    N += 2; // Adiciona vértices extras para o gerador-base (0) e o sumidouro (N-1).

    // Inicializa as matrizes de adjacência e o vetor de geradores.
    graph = std::vector<std::vector<size_t>>(N, std::vector<size_t>(N, 0));
    graphR = std::vector<std::vector<size_t>>(N, std::vector<size_t>(N, 0));
    isGenerator = std::vector<bool>(N, false);

    // Lê informações dos vértices (gerador ou consumidor).
    for (size_t i = 1; i < N - 1; ++i) {
        size_t v, c; // v: vértice, c: consumo.
        std::cin >> v >> c;

        if (c == 0) {
            // Adiciona aresta infinita do gerador-base ao gerador `v`.
            graph[0][v] = std::numeric_limits<size_t>::max(); 
            graphR[0][v] = std::numeric_limits<size_t>::max();
            isGenerator[v] = true;
        } else {
            // Adiciona capacidade do consumidor `v` ao sumidouro.
            graph[v][N - 1] += c;
            graphR[v][N - 1] += c;            
        }
    }

    // Lê arestas e suas capacidades.
    size_t u, v, c; // Aresta (u, v) com capacidade `c`.
    for (size_t i = 0; i < M; ++i) {
        std::cin >> u >> v >> c;

        // Incrementa a capacidade entre os vértices.
        graph[u][v] += c;
        graphR[u][v] += c;
    }
}