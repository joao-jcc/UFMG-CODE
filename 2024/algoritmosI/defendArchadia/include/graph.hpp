#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>

const size_t UNDEFINED = std::numeric_limits<size_t>::max();

class Graph {
    public:
        Graph();     
    
    private:
        void _read();     

    public:
        size_t N; 
        std::vector<std::vector<size_t>> g;
        std::vector<std::vector<size_t>> gt;

        std::unordered_map<std::string, size_t> nameToIndex;
        std::vector<std::string> indexToName;
};

#endif // GRAPH_HPP
