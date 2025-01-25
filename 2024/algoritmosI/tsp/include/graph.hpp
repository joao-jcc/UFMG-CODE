#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

class Node {
    public:
        Node(size_t v, size_t w);
    
    public:
        size_t v;
        size_t w;
};


class Graph {

    public:
        Graph();
        void read();
        void print();

    
    public:
        std::map<std::string, size_t> name_to_index;
        std::vector<std::string> index_to_name;
        size_t N; // número de vértices
        size_t M; // número de arestas
        std::vector<std::vector<Node>> g; // estrutura principal do grafo 

};


#endif