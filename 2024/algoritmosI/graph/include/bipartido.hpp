// bipartido.hpp

#ifndef BIPARTIDO_HPP
#define BIPARTIDO_HPP

#include <vector>

enum Color {
    WHITE, // not colored
    RED,   // one color
    BLUE   // another color
};

// Declaração da função is_bipartite
bool is_bipartite(const std::vector<std::vector<int>>& graph);

#endif // BIPARTIDO_HPP
