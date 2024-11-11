#include "capital.hpp"
#include <iostream>
#include <vector>
#include <queue>


void InfoCapital::print() {
    std::cout << "CAPITAL: " << capital << std::endl;

    std::cout << "DEPTHS: " << std::endl;
    for (int v=0; v < depths.size(); ++v) {
        std::cout << v << ": " << depths[v] << std::endl;
    }
}


InfoBFS bfs(const std::vector<std::vector<int> >& graph, int start, int N) {
    std::vector<bool> explored(N, false);
    std::vector<int> depths(N, 0);

    std::queue<int> s; s.push(start); explored[start] = true;
    int cost = 0; int nExplored = 1;
    while (!s.empty()) {
        int v = s.front(); s.pop();
        for (int u : graph[v]) {
            if (!explored[u]) {
                s.push(u);
                depths[u] = depths[v]+1;

                explored[u] = true;
                cost += depths[u]; ++nExplored;
            }
        }
    }

    return InfoBFS{cost, nExplored, explored, depths};
}


InfoCapital getCapital(const std::vector<std::vector<int>>& graph, int N) {
    
    std::vector<bool> candidates(N, true);
    int capital = -1; int minCost = INT_MAX; std::vector<int> depthsCapital(N, -1);
    for (int v=0; v < N; ++v) {

        InfoBFS info = bfs(graph, v, N);
        
        // v não acessa todo o grafo: seus descendentes não podem ser capital
        if (info.nExplored != N) {
            for (int u=0; u < N; ++u) {candidates[u] =  ! info.explored[u];}
        }
        // v acessa todo o grafo e tem custo menor que a capital anterior
        else if (info.cost < minCost) {
            capital = v; minCost = info.cost; depthsCapital = info.depths;
        }
    }   


    return InfoCapital{capital, depthsCapital};
}
