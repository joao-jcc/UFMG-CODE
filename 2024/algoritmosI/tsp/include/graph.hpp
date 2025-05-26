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
        Node();
    
    public:
        size_t v;
        size_t w;
};


class Graph {

    public:
        Graph();
        void read(std::string& path);
        void read();
        void print();
    
    public:
        std::vector<std::vector<Node>> g; // estrutura principal do grafo 
        size_t N; // número de vértices
        size_t M; // número de arestas
        std::vector<std::string> index_to_name;
        std::map<std::string, size_t> name_to_index;
        char method;
        
       

};


#endif