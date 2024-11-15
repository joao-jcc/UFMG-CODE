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
    void _setEdgesTrue(std::vector<int>& path, std::vector<bool>& exploredEdges, std::vector<int>& solution);

    BFS& bfs;
    DFS& dfs;
    Graph& graph;

    int nPatrols;
    std::vector<std::vector<int>> patrolsPath;

    void _patrol(int battalion);
    void _patrolAll();
};

#endif
