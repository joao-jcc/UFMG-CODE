#ifndef FLOW_HPP
#define FLOW_HPP

#include <vector>
#include <queue>
#include <limits>
#include "graph.hpp"
#include "utils.hpp"

class Flow {
private:
    Graph& g;
    std::vector<size_t> parents;

    size_t maxFlow_;
    size_t missingEnergy_;
    size_t loss_;
    std::vector<Edge> fullEdges_;

public:
    Flow(Graph& graph);

    std::vector<size_t> bfs(size_t start);
    size_t updateResidualGraph(std::vector<size_t>& parents, size_t sink);
    size_t fordFulkerson();

    size_t missingEnergy();
    std::vector<Edge> criticalEdges();
    size_t loss();

    void print();
};

#endif
