#include "utils.hpp"

// Função para particionar o vetor com base em um pivô
size_t partition(std::vector<Edge>& edges, size_t low, size_t high) {
    Edge pivot = edges[high];
    size_t i = low; // Corrigir inicialização para evitar underflow

    for (size_t j = low; j < high; ++j) {
        if (edges[j].capacity > pivot.capacity) {
            std::swap(edges[i], edges[j]);
            ++i;
        }
    }

    std::swap(edges[i], edges[high]);
    return i;
}

// Implementa o Quicksort recursivo
void quicksortHelper(std::vector<Edge>& edges, size_t low, size_t high) {
    if (low < high) {
        size_t pi = partition(edges, low, high);

        // Garantir índices válidos antes da recursão
        if (pi > 0) quicksortHelper(edges, low, pi - 1);
        quicksortHelper(edges, pi + 1, high);
    }
}

// Função principal para ordenar o vetor
void quicksort(std::vector<Edge>& edges) {
    if (!edges.empty()) {
        quicksortHelper(edges, 0, edges.size() - 1);
    }
}
