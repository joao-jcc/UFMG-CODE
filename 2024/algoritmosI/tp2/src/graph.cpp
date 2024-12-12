#include "graph.hpp"

#define _ ios_base::sync_with_stdio(0);cin.tie(0);

Graph::Graph() {
    _read();
}

void Graph::_read() {
    if (!std::cin) {
        std::cerr << "Error reading input!" << std::endl;
        exit(1);
    }
    std::cin >> N >> M; // Inicializa número de vértices e arestas
    
    graph = std::vector<std::vector<size_t>>(N, std::vector<size_t>(N, 0));
    graphR = std::vector<std::vector<size_t>>(N, std::vector<size_t>(N, 0));

    // lê tipo dos vértices: gerador ou consumidor
    for (size_t i = 0; i < N; ++i) {
        size_t v; size_t type;
        std::cin >> v >> type;
    } 

    size_t u, v, c; // aresta (u, v) com capacidade c
    for (size_t i = 0; i < M; ++i) {
        std::cin >> u >> v >> c;

        graph[u-1][v-1] = c;
        graphR[u-1][v-1] = c;
    }
}


void Graph::print() {
    std::cout << "GRAPH" << std::endl;
    for (size_t i=0; i < N; ++i) {
        for (size_t j=0; j < N; ++j) {
            std::cout << std::setw(3) << graph[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "\nRESIDUAL" << std::endl;
    for (size_t i=0; i < N; ++i) {
        for (size_t j=0; j < N; ++j) {
            std::cout << std::setw(3) << graphR[i][j] << " ";
        }
        std::cout << std::endl;
    }
}