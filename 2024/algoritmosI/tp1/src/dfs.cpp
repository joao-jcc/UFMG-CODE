#include <iostream>
#include <vector>
#include <stack>
#include "dfs.hpp"
#include "bfs.hpp"

DFS::DFS(const Graph& graph) : nComponents(0), graph(graph)  {
    components = std::vector<int>(graph.N, -1);
    _kosaraju();
    _genEdgesSCC();
}

void DFS::_dfs(int start,  std::vector<bool>& explored) {
    explored[start] = true;
    for (int neighbor : graph.g[start]) {
        if (!explored[neighbor]) {
            _dfs(neighbor, explored);
        }
    }
    deathOrder.push(start);
}

void DFS::_dfsSCC(int start, std::vector<bool>& explored) {
    explored[start] = true;
    components[start] = nComponents;
    for (int neighbor : graph.gt[start]) {
        if (!explored[neighbor]) {
            _dfsSCC(neighbor, explored);
        }
    }
}

void DFS::_kosaraju() {
    int N = graph.N;
    std::vector<bool> explored(N, false);

    // Primeira passagem: ordem de término dos nós
    for (int v = 0; v < N; ++v) {
        if (!explored[v]) {
            _dfs(v, explored);
        }
    }

    // Segunda passagem: Identificação das componentes
    explored.assign(N, false);

    while (!deathOrder.empty()) {
        int v = deathOrder.top();
        deathOrder.pop();
        if (!explored[v]) {
            _dfsSCC(v, explored);
            ++nComponents;
        }
    }
}

void DFS::_genEdgesSCC() {
    int N = graph.N;
    sccEdges.assign(nComponents, std::vector<bool>(N*N, false));
    for (int v=0; v < N; ++v)  {
        // loop pelos vizinhos de v
        for (int u : graph.g[v]) {
            if (components[u] == components[v]) {
                sccEdges[components[v]][v*N + u] = true;
            }
        }
    }
}

void DFS::findBattalions(const std::vector<int>& capitalDepths, int capital) {
    for (int component=0; component < nComponents; ++component) {

        int battalion = -1; int minDepth = INT_MAX;
        for (int v=0; v < graph.N; ++v) {

            if (components[v] == component && capitalDepths[v] < minDepth) {
                battalion = v; minDepth = capitalDepths[v];
            }

        }
        if (battalion == capital) {continue;}
        battalions.push_back(battalion);
    }
}

void DFS::print() {
        printf("%zu\n", battalions.size()); 
        for (int battalion : battalions) {printf("%s\n", graph.indexToName[battalion].c_str());}
}