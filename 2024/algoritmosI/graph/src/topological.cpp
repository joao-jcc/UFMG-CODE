#include "topological.hpp"
#include <vector>
#include <queue>

std::vector<int> topologicalOrder(std::vector<std::vector<int> >& graph) {
    int N = graph.size();
    // O(N): vetor de tamanho N com todas as entradas iguais a 0
    std::vector<int> entries(N, 0);

    // O(M): percorre-se todas as arestas duas vezes, 2M
    for (int v=0; v < N; ++v) {
        for (int u : graph[v]) {
            ++entries[u];
        }
    }

    // O(N): vértices com grau de entrada nulo
    std::queue<int> candidates;
    for (int v=0; v < N; ++v) {
        if (entries[v] == 0) candidates.push(v);
    }


    // O(M): loop por todas as aresta duas vezes, 2M
    std::vector<int> topologicalVec;
    while(!candidates.empty()) {
        int v = candidates.front(); candidates.pop();
        topologicalVec.push_back(v);

        for (int u : graph[v]) {
            if (--entries[u] == 0) candidates.push(u);
        }
    }

    if (topologicalVec.size() != N) {
        std::cout << "Não é DAG! Tem ciclo!" << std::endl;
        exit(1);
    }

    return topologicalVec;
}
