#include "graph.hpp"

// Constructor to read the graph from a file
Graph::Graph(const string& inputFile) {
    _read(inputFile);
}

// Private function to read the graph from the input file
void Graph::_read(const string& inputFile) {
    ifstream input(inputFile);
    if (!input) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        exit(1);
    }

    // Read the number of vertices and edges
    int M;
    input >> N >> M;  // Initialize N here
    g = vector<vector<int>>(N);
    gt = vector<vector<int>>(N);
    indexToName = vector<string>(N);
    
    int nodeCount = 0;
    string name1, name2;
    for (int i = 0; i < M; ++i) {
        input >> name1 >> name2;
        
        // Se o nome não estiver no mapa
        if (nameToIndex.find(name1) == nameToIndex.end()) {
            nameToIndex[name1] = nodeCount;
            indexToName[nodeCount++] = name1;
        }
        if (nameToIndex.find(name2) == nameToIndex.end()) {
            nameToIndex[name2] = nodeCount;
            indexToName[nodeCount++] = name2;
        }

        int idx1 = nameToIndex[name1];
        int idx2 = nameToIndex[name2];
        

        g[idx1].push_back(idx2);
        gt[idx2].push_back(idx1);
    }
}

// Function to print the directed graph using the original names
void Graph::print() const {
    std::cout << "G: " << std::endl;
    for (int i = 0; i < N; ++i) {
        cout << i << "/" << indexToName[i] << ": ";
        for (int v : g[i]) {
            cout << v << "/" << indexToName[v] << " ";
        }
        cout << endl;
    }
}
