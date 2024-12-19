#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>

// Estrutura que representa uma aresta em um grafo.
struct Edge {
    size_t u; // Vértice de origem.
    size_t v; // Vértice de destino.
    size_t capacity; // Capacidade da aresta.
};

// Função de comparação para ordenar arestas por capacidade (decrescente).
// Critérios secundários: vértice de origem (crescente) e destino (crescente).
bool edgeComparator(const Edge& e1, const Edge& e2);

// Ordena um vetor de arestas utilizando o algoritmo Quicksort.
void quicksort(std::vector<Edge>& edges);

// Função auxiliar para o algoritmo Quicksort.
// Divide o vetor em duas partes e organiza os elementos em relação ao pivô.
void quicksortHelper(std::vector<Edge>& edges, size_t low, size_t high);

// Particiona o vetor de arestas para o Quicksort.
// Retorna a posição correta do pivô.
size_t partition(std::vector<Edge>& edges, size_t low, size_t high);

#endif // UTILS_HPP
