#ifndef PATROL_HPP
#define PATROL_HPP

#include "graph.hpp"
#include "bfs.hpp"
#include "dfs.hpp"

class Patrol {
public:
    Patrol(BFS& bfs_, DFS& dfs_, Graph& graph_);
    void print();


private:
    void _setEdgesTrue(std::vector<size_t>& path, std::vector<bool>& exploredEdges, std::vector<size_t>& solution);

    BFS& bfs;
    DFS& dfs;
    Graph& graph;

    size_t nPatrols;
    std::vector<std::vector<size_t>> patrolsPath;

    void _patrol(size_t battalion);
    void _patrolAll();
};

#endif
