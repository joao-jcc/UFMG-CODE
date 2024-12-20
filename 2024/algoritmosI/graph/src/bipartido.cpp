// bipartido.cpp

#include "bipartido.hpp"
#include <iostream>
#include <queue>

bool is_bipartite(const std::vector<std::vector<int> >& graph) {
    int N = graph.size();
    std::vector<Color> colors(N, WHITE);
    std::vector<int> parents(N, -1);

    std::queue<int> s;
    s.push(0);
    colors[0] = RED;

    while (!s.empty()) {
        int v = s.front();
        s.pop();

        for (int u : graph[v]) {
            if (colors[u] == WHITE) {
                s.push(u);
                parents[u] = v;
                colors[u] = (colors[v] == RED) ? BLUE : RED;
            } else if (colors[u] == colors[v]) {
                // Se um vértice adjacente tiver a mesma cor, o grafo não é bipartido
                std::cout << "Não é Bipartido!" << std::endl;
                return false;
            }
        }
    }

    std::cout << "Bipartido!" << std::endl;
    return true;
}
