// bfs.hpp

#ifndef CAPITAL_HPP
#define CAPITAL_HPP

#include <vector>
#include <queue>

struct InfoBFS
{
    int cost; // soma das profundidades de cada vértice
    int nExplored; // número de vértices explorados na bfs
    std::vector<bool> explored;
    std::vector<int> depths;
};

struct InfoCapital {
    int capital;
    std::vector<int> depths;

    void print();
};


InfoBFS bfs(const std::vector<std::vector<int>>& graph, int start, int N);

InfoCapital getCapital(const std::vector<std::vector<int>>& graph, int N);

#endif // CAPITAL_HPP
