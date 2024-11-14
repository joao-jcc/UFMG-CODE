// graphW.hpp
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Graph {
    public:
        Graph(const string& inputFile);
        void print() const;
    
    public:
        int N; // Number of vertices
        vector<vector<int>> g;
        vector<vector<int>> gt;

        unordered_map<string, int> nameToIndex;
        vector<string> indexToName;

        void _read(const string& inputFile);
};

#endif // GRAPH_HPP
