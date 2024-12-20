#include "flow.hpp"
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <cstddef>

#define UNDEFINED std::numeric_limits<size_t>::max() // Representa vértices não definidos no BFS (sem pais).

// Construtor: inicializa os cálculos de fluxo máximo, energia faltante e perdas.
Flow::Flow(Graph& graph) : g(graph) {
    maxFlow_ = fordFulkerson();
    missingEnergy_ = missingEnergy();
    loss_ = loss();
    fullEdges_ = criticalEdges();
}

// Busca em largura para encontrar um caminho no grafo residual.
std::vector<size_t> Flow::bfs(size_t start) {
    size_t N = g.N; // Número de vértices.
    std::vector<bool> explored(N, false); // Marca vértices visitados.
    std::vector<size_t> parents(N, UNDEFINED); // Armazena o caminho encontrado.

    std::queue<size_t> s; 
    s.push(start); 
    explored[start] = true;

    while (!s.empty()) {
        size_t u = s.front(); 
        s.pop();

        // Explora vizinhos com capacidade positiva no grafo residual.
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

// Atualiza o grafo residual com base no gargalo do caminho encontrado.
size_t Flow::updateResidualGraph(std::vector<size_t>& parents, size_t sink) {
    size_t bottleneck = std::numeric_limits<size_t>::max();
    size_t current = sink;

    // Determina o gargalo do caminho encontrado.
    while (parents[current] != UNDEFINED) {
        size_t parent = parents[current];
        bottleneck = std::min(bottleneck, g.graphR[parent][current]);
        current = parent;
    }

    // Atualiza o grafo residual com o valor do gargalo.
    current = sink;
    while (parents[current] != UNDEFINED) {
        size_t parent = parents[current];
        g.graphR[parent][current] -= bottleneck;
        g.graphR[current][parent] += bottleneck;
        current = parent;
    }

    return bottleneck;
}

// Implementa o algoritmo de Ford-Fulkerson para encontrar o fluxo máximo.
size_t Flow::fordFulkerson() {
    size_t max_flow = 0;
    size_t source = 0; // Fonte é o vértice 0.
    size_t sink = g.N - 1; // Sumidouro é o último vértice.

    parents = bfs(source);
    while (parents[sink] != UNDEFINED) {
        size_t bottleneck = updateResidualGraph(parents, sink);
        max_flow += bottleneck;
        parents = bfs(source);
    }

    return max_flow;
}

// Calcula a energia faltante baseada nas capacidades residuais conectadas ao sumidouro.
size_t Flow::missingEnergy() {
    size_t miss = 0;
    for (size_t v = 1; v < g.N - 1; ++v) {
        miss += g.graphR[v][g.N - 1];
    }

    return miss;
}

// Calcula as perdas de energia total no sistema.
size_t Flow::loss() {
    size_t lossEnergy = 0;
    for (size_t u = 0; u < g.N; ++u) {
        if (!g.isGenerator[u]) { continue; }
        for (size_t v = 0; v < g.N; ++v) {
            lossEnergy += g.graph[u][v];
        } 
    }

    lossEnergy -= maxFlow_;
    return lossEnergy;
}

// Identifica e retorna as arestas críticas que estão completamente saturadas.
std::vector<Edge> Flow::criticalEdges() {
    std::vector<Edge> edgesFull;
    for (size_t u = 1; u < g.N - 1; ++u) {
        for (size_t v = 1; v < g.N - 1; ++v) {
            if (u != v && g.graph[u][v] > 0 && g.graphR[u][v] == 0) {
                edgesFull.push_back(Edge{u, v, g.graph[u][v]});
            }
        }
    }

    quicksort(edgesFull); // Ordena as arestas críticas.
    return edgesFull;
}

// Imprime os resultados do cálculo de fluxo.
void Flow::print() {
    std::cout << maxFlow_ << std::endl;
    std::cout << missingEnergy_ << std::endl;
    std::cout << loss_ << std::endl;
    std::cout << fullEdges_.size() << std::endl;

    for (size_t i = 0; i < fullEdges_.size(); ++i) {
        Edge edge = fullEdges_[i];
        std::cout << edge.u << " ";
        std::cout << edge.v << " ";
        std::cout << edge.capacity << std::endl;
    }
}
