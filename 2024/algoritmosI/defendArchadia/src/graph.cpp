#include "graph.hpp"

#define _ ios_base::sync_with_stdio(0);cin.tie(0);

// Constructor to read the graph from standard input
Graph::Graph() {
    _read();
}

// Private function to read the graph from standard input
void Graph::_read() {
    // Use std::cin for input
    if (!std::cin) {
        std::cerr << "Error reading input!" << std::endl;
        exit(1);
    }

    // Read the number of vertices and edges
    size_t M;
    std::cin >> N >> M;  // Initialize N here
    g = std::vector<std::vector<size_t>>(N);
    gt = std::vector<std::vector<size_t>>(N);
    indexToName = std::vector<std::string>(N);

    size_t nodeCount = 0;
    std::string name1, name2;
    for (size_t i = 0; i < M; ++i) {
        std::cin >> name1 >> name2;

        // If the name is not in the map
        if (nameToIndex.find(name1) == nameToIndex.end()) {
            nameToIndex[name1] = nodeCount;
            indexToName[nodeCount++] = name1;
        }
        if (nameToIndex.find(name2) == nameToIndex.end()) {
            nameToIndex[name2] = nodeCount;
            indexToName[nodeCount++] = name2;
        }

        size_t idx1 = nameToIndex[name1];
        size_t idx2 = nameToIndex[name2];

        g[idx1].push_back(idx2);
        gt[idx2].push_back(idx1);
    }
}