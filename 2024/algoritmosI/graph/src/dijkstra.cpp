#include "dijkstra.hpp"

struct Compare {
    bool operator()(const wVertice& a, const wVertice& b) {
        return a.cost > b.cost; // Menor peso tem maior prioridade
    }
};

std::vector<int> dijkstra(const std::vector<std::vector<wVertice>>& graph, int start) {
    int N = graph.size();

    std::priority_queue<wVertice, std::vector<wVertice>, Compare> pq;
    std::vector<int> distances(N, INT_MAX);
    std::vector<int> minDistances(N, INT_MAX);
    std::vector<int> parents(N, -1);

    pq.push(wVertice{start, 0});
    int nExplored =0;

    while (nExplored != N) {
        wVertice u = pq.top(); pq.pop(); minDistances[u.index] = u.cost; ++nExplored;
        for (wVertice v : graph[u.index]) {
            // se já foi explorado siga para o próximo vizinho
            if (minDistances[v.index] != INT_MAX) {continue;}

            // atualiza distância
            if (minDistances[u.index] + v.cost < distances[v.index]) {
                distances[v.index] = minDistances[u.index] + v.cost;
                pq.push(wVertice{v.index, distances[v.index]});
                parents[v.index] = u.index;
            }
        }
    }
    
    return parents;
}   
