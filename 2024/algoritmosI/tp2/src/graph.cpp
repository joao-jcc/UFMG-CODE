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
    N += 2; // dois vértices adicionais para representar o gerador-base e o sumidouro

    graph = std::vector<std::vector<size_t>>(N, std::vector<size_t>(N, 0));
    graphR = std::vector<std::vector<size_t>>(N, std::vector<size_t>(N, 0));
    isGenerator = std::vector<bool>(N, false);

    // lê tipo dos vértices: gerador ou consumidor
    for (size_t i = 1; i < N-1; ++i) {
        size_t v; size_t c; // v: vértice, c: consumo
        std::cin >> v >> c;
        if (c == 0) {
            // adiciona aresta infinita do gerador-base ao gerador v
            graph[0][v] = std::numeric_limits<size_t>::max(); 
            graphR[0][v] = std::numeric_limits<size_t>::max();
            isGenerator[v] = true;
        }
        else {
            // incrementa aresta do consumidor v ao sumidoudouro
            graph[v][N-1] += c;
            graphR[v][N-1] += c;            
        }
    }

    size_t u, v, c; // aresta (u, v) com capacidade c
    for (size_t i = 0; i < M; ++i) {
        std::cin >> u >> v >> c;

        graph[u][v] += c;
        graphR[u][v] += c;
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