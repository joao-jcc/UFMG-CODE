#include "prim.hpp"


std::vector<int> prim(std::vector<std::vector<wVertice> > graph, int start) {
    int N = graph.size();

    std::vector<int> parents(N, -1);
    std::vector<bool> S(N, false);

    S[start] = true;

    int totalCost = 0;

    for (int i=0; i < N-1; ++i) {
        int minU=INT_MAX; int minV=INT_MAX; int minW=INT_MAX;
        for (int u=0; u < N; ++u) {
            if (!S[u]) {continue;}

            // se u pertence a S olhe para os vizinhos de u
            for (wVertice v : graph[u]) {
                // se o vizinho também pertence a S
                if (S[v.index]) {continue;}
                // salve a aresta do cutSet se o seu peso é menor do que o peso mínimo
                if (v.cost < minW) {minU=u; minV=v.index; minW=v.cost;}
            }
        }
        parents[minV] = minU;
        totalCost += minW;
        S[minV] = true;
    }
    std::cout << "TC: " << totalCost << std::endl;
    return parents;
}