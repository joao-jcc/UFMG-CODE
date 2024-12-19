#include "utils.hpp"
#include <vector>

// Compara duas arestas com base nos critérios de ordenação especificados.
bool edgeComparator(const Edge& e1, const Edge& e2) {
    if (e1.capacity != e2.capacity) {
        return e1.capacity > e2.capacity; // Prioridade para maior capacidade.
    }
    
    if (e1.u != e2.u) {
        return e1.u < e2.u; // Caso as capacidades sejam iguais, ordena pelo vértice de origem.
    }
    
    return e1.v < e2.v; // Caso os critérios anteriores sejam iguais, ordena pelo vértice de destino.
}

// Particiona o vetor de arestas em relação a um pivô.
size_t partition(std::vector<Edge>& edges, size_t low, size_t high) {
    Edge pivot = edges[high]; // Define o último elemento como pivô.
    size_t i = low; // Índice para os elementos menores que o pivô.

    for (size_t j = low; j < high; ++j) {
        if (edgeComparator(edges[j], pivot)) {
            std::swap(edges[i], edges[j]); // Move elementos menores que o pivô para a esquerda.
            ++i;
        }
    }

    std::swap(edges[i], edges[high]); // Coloca o pivô na posição correta.
    return i; // Retorna o índice do pivô.
}

// Função recursiva auxiliar do Quicksort.
void quicksortHelper(std::vector<Edge>& edges, size_t low, size_t high) {
    if (low < high) {
        size_t pi = partition(edges, low, high); // Particiona o vetor.

        if (pi > 0) quicksortHelper(edges, low, pi - 1); // Ordena a sublista esquerda.
        quicksortHelper(edges, pi + 1, high); // Ordena a sublista direita.
    }
}

// Ordena um vetor de arestas utilizando o Quicksort.
void quicksort(std::vector<Edge>& edges) {
    if (!edges.empty()) {
        quicksortHelper(edges, 0, edges.size() - 1);
    }
}
