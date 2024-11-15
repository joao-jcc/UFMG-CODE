#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>

class Graph {
    public:
        Graph();     
            
    private:
        void _read();     

    public:
        int N; 
        std::vector<std::vector<int>> g;
        std::vector<std::vector<int>> gt;

        std::unordered_map<std::string, int> nameToIndex;
        std::vector<std::string> indexToName;
};

#endif // GRAPH_HPP
