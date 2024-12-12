#ifndef FLOW_HPP
#define FLOW_HPP

#include <vector>
#include <queue>
#include <limits>
#include "graph.hpp"

class Flow {
private:
    Graph& g;
    std::vector<size_t> parents;

public:
    Flow(Graph& graph);

    std::vector<size_t> bfs(size_t start);
    size_t updateResidualGraph(std::vector<size_t>& parents, size_t sink);
    size_t fordFulkerson();
};

#endif
