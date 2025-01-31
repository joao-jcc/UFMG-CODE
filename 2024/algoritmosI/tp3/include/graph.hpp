#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

#define MAX_SIZET std::numeric_limits<size_t>::max()
#define UNDEFINED std::numeric_limits<size_t>::max()


class Graph {

    public:
        Graph();
    
    public:
        std::vector<std::vector<size_t>> matrix; // estrutura principal do grafo 
        size_t N; // número de vértices
        std::vector<std::string> index_to_name;
        std::map<std::string, size_t> name_to_index;
        char method;
    
    private:
        void _read();
       

};


#endif