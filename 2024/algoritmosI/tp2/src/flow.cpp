#include "flow.hpp"
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

#define UNDEFINED std::numeric_limits<size_t>::max()

Flow::Flow(Graph& graph) : g(graph) {}

std::vector<size_t> Flow::bfs(size_t start) {
    size_t N = g.N;
    std::vector<bool> explored(N, false);
    std::vector<size_t> parents(N, UNDEFINED);

    std::queue<size_t> s; 
    s.push(start); 
    explored[start] = true;

    while (!s.empty()) {
        size_t u = s.front(); 
        s.pop();

        for (size_t v = 0; v < N; ++v) {
            if (g.graphR[u][v] > 0 && !explored[v]) {
                s.push(v);
                parents[v] = u;
                explored[v] = true;
            }
        }
    }

    return parents;
}


size_t Flow::updateResidualGraph(std::vector<size_t>& parents, size_t sink) {
    size_t bottleneck = std::numeric_limits<size_t>::max();
    size_t current = sink;

    while (parents[current] != UNDEFINED) {
        size_t parent = parents[current];
        bottleneck = std::min(bottleneck, g.graphR[parent][current]);
        current = parent;
    }

    current = sink;

    while (parents[current] != UNDEFINED) {
        size_t parent = parents[current];
        g.graphR[parent][current] -= bottleneck;
        g.graphR[current][parent] += bottleneck;
        current = parent;
    }

    return bottleneck;
}

size_t Flow::fordFulkerson() {
    size_t max_flow = 0;
    size_t source = 0;  // assumindo que a fonte é o vértice 0
    size_t sink = g.N - 1; // assumindo que o sumidouro é o último vértice

    parents = bfs(source);
    while (parents[sink] != UNDEFINED) {
        size_t bottleneck = updateResidualGraph(parents, sink);
        max_flow += bottleneck;
        parents = bfs(source);
    }

    return max_flow;
}
