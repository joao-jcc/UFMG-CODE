#include "utils.hpp"

bool edgeComparator(const Edge& e1, const Edge& e2) {
    if (e1.capacity != e2.capacity) {
        return e1.capacity > e2.capacity;
    }
    
    if (e1.u != e2.u) {
        return e1.u < e2.u;
    }
    
    return e1.v < e2.v;
}

size_t partition(std::vector<Edge>& edges, size_t low, size_t high) {
    Edge pivot = edges[high];
    size_t i = low;

    for (size_t j = low; j < high; ++j) {
        if (edgeComparator(edges[j], pivot)) {
            std::swap(edges[i], edges[j]);
            ++i;
        }
    }

    std::swap(edges[i], edges[high]);
    return i;
}

void quicksortHelper(std::vector<Edge>& edges, size_t low, size_t high) {
    if (low < high) {
        size_t pi = partition(edges, low, high);

        if (pi > 0) quicksortHelper(edges, low, pi - 1);
        quicksortHelper(edges, pi + 1, high);
    }
}

void quicksort(std::vector<Edge>& edges) {
    if (!edges.empty()) {
        quicksortHelper(edges, 0, edges.size() - 1);
    }
}