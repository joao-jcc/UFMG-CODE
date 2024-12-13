#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>

struct Edge {
    size_t u;
    size_t v;
    size_t capacity;
};

void quicksort(std::vector<Edge>& edges);
void quicksortHelper(std::vector<Edge>& edges, size_t low, size_t high);
size_t partition(std::vector<Edge>& edges, size_t low, size_t high);

#endif
