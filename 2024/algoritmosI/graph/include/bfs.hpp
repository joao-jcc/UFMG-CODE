// bfs.hpp

#ifndef BFS_HPP
#define BFS_HPP

#include <vector>
#include <queue>

enum Color {
    WHITE, // not explored
    GRAY   // explored
};

// Declaração da função bfs
std::vector<int> bfs(const std::vector<std::vector<int>>& graph, int start);

#endif // BFS_HPP
