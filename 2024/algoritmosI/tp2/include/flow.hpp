#ifndef FLOW_HPP
#define FLOW_HPP

#include "graph.hpp"
#include "utils.hpp"
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

// Classe para calcular o fluxo máximo em um grafo e informações relacionadas.
class Flow {
private:
    Graph& g; // Referência para o grafo.
    std::vector<size_t> parents; // Vetor de predecessores usado no BFS.

    size_t maxFlow_; // Fluxo máximo calculado.
    size_t missingEnergy_; // Energia faltante no sistema.
    size_t loss_; // Perdas de energia no sistema.
    std::vector<Edge> fullEdges_; // Arestas críticas com capacidade totalmente utilizada.

public:
    // Construtor que inicializa o cálculo de fluxo.
    Flow(Graph& graph);

    // Executa a busca em largura para encontrar caminhos no grafo residual.
    std::vector<size_t> bfs(size_t start);

    // Atualiza o grafo residual com base no caminho encontrado.
    size_t updateResidualGraph(std::vector<size_t>& parents, size_t sink);

    // Algoritmo de Ford-Fulkerson para cálculo do fluxo máximo.
    size_t fordFulkerson();

    // Calcula a energia faltante no sistema.
    size_t missingEnergy();

    // Identifica as arestas críticas.
    std::vector<Edge> criticalEdges();

    // Calcula a perda total de energia no sistema.
    size_t loss();

    // Imprime os resultados do fluxo e informações adicionais.
    void print();
};

#endif
