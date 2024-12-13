#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <string>
#include <iostream>
#include<iomanip>

class Graph {
    public:
        Graph();
        void print();    
    
    private:
        void _read();     

    public:
        size_t N; // número de vértices
        size_t M; // número de arestas
        std::vector<std::vector<size_t>> graph;
        std::vector<std::vector<size_t>> graphR; // grafo residual
        std::vector<bool> isGenerator;

};

#endif // GRAPH_HPP
