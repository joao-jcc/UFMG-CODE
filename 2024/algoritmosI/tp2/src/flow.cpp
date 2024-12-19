#include "flow.hpp"
#include <vector>
#include <queue>
#include <limits>

#define UNDEFINED std::numeric_limits<size_t>::max()

Flow::Flow(Graph& graph) : g(graph) {
    maxFlow_ = fordFulkerson();
    missingEnergy_ = missingEnergy();
    loss_ = loss();
    fullEdges_ = criticalEdges();
}


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
    size_t source = 0;  // gerador base é o vértice 0
    size_t sink = g.N - 1; // o sumidouro é o último vértice

    parents = bfs(source);
    while (parents[sink] != UNDEFINED) {
        size_t bottleneck = updateResidualGraph(parents, sink);
        max_flow += bottleneck;
        parents = bfs(source);
    }

    return max_flow;
}


size_t Flow::missingEnergy() {
    size_t miss = 0;
    for (size_t v=1; v < g.N-1; ++v) {
        miss += g.graphR[v][g.N-1];
    }

    return miss;
}


size_t Flow::loss() {
    size_t lossEnergy=0;
    for (size_t u=0; u < g.N; ++u) {
        if (!g.isGenerator[u]) {continue;}
        for (size_t v=0; v < g.N; ++v) {
            lossEnergy += g.graph[u][v];
        } 
    }

    lossEnergy -= maxFlow_;

    return lossEnergy;
}


std::vector<Edge> Flow::criticalEdges() {
    std::vector<Edge> edgesFull;
    for (size_t u=1; u < g.N-1; ++u) {
        for (size_t v=1; v < g.N-1; ++v) {
            if (u != v && g.graph[u][v] > 0 && g.graphR[u][v] == 0) {
                edgesFull.push_back(Edge{u, v, g.graph[u][v]});
            }
        }
    }
    
    quicksort(edgesFull);

    return edgesFull;
}


void Flow::print() {
    std::cout << maxFlow_ << std::endl;
    std::cout << missingEnergy_ << std::endl;
    std::cout << loss_ << std::endl;
    std::cout << fullEdges_.size() << std::endl;

    for (size_t i=0; i < fullEdges_.size(); ++i) {
        Edge edge = fullEdges_[i];
        std::cout << edge.u << " ";
        std::cout << edge.v << " ";
        std::cout << edge.capacity << std::endl;
    }
}