#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <limits>

#define MAX_SIZET std::numeric_limits<size_t>::max() 
#define UNDEFINED std::numeric_limits<size_t>::max()  // Representa ausência de conexão no grafo

// Classe que representa um grafo não direcionado com pesos
class Graph {

    public:
        Graph();
    
    public:
        std::vector<std::vector<size_t>> matrix;
        size_t N; // Número de vértices
        std::vector<std::string> index_to_name; // Mapeia índices para nomes das cidades
        std::map<std::string, size_t> name_to_index; // Mapeia nomes das cidades para índices
        char method; // Algorítimo de execução: 'b', 'd', 'g'
    
    private:
        void _read();

};

#endif
