#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include "graph.hpp"

void read_graph(Grafo* grafo) {
    int n; // Number of vertices in the graph
    std::cin >> n;

    for (int i=0; i < n; ++i) {
        grafo->InsereVertice();
    }

    for (int i = 0; i < n; ++i) {
        int degree;
        std::cin >> degree;

        for (int j = 0; j < degree; ++j) {
            // Read the space between numbers
            std::cin.get();
            int neighbor;
            std::cin >> neighbor;
            grafo->InsereAresta(i, neighbor);
        }
    }

}

void print_data(Grafo* grafo) {
        std::cout << grafo->QuantidadeVertices() << std::endl;
        std::cout << grafo->QuantidadeArestas() << std::endl;
        std::cout << grafo->GrauMinimo() << std::endl;
        std::cout << grafo->GrauMaximo() << std::endl;
}

void print_neighbors(Grafo* grafo) {
    for (int vertice = 0; vertice < grafo->QuantidadeVertices(); ++vertice) {
        grafo->ImprimeVizinhos(vertice);
    }
}

void print_complete(Grafo* grafo) {
    int n_vertices = grafo->QuantidadeVertices();
    if (grafo->GrauMaximo() == n_vertices - 1 && grafo->GrauMinimo() == n_vertices - 1) {
        std::cout << 1 << std::endl;
    } 
    else {
        std::cout << 0 << std::endl;
    }
}

#endif