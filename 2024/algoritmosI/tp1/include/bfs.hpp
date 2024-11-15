// bfs.hpp

#ifndef BFS_HPP
#define BFS_HPP

#include <vector>
#include <queue>
#include "graph.hpp"



struct InfoBFS
{
    int cost; // soma das profundidades de cada vértice
    int nExplored; // número de vértices explorados na bfs
    std::vector<bool> explored;
    std::vector<int> depths;
};


class BFS {
    public:
        BFS(const Graph& graph);
        std::vector<int> findMinPath(int start, int end); // caminho mínimo entre dois vértices quaisquer, incluindo start e end.

        int capital;
        int capitalCost;
        std::vector<int> capitalDepths;
        std::vector<std::vector<int>> allParents; // armazena todas as árvores das BFS's

        void print();

    private:
        InfoBFS _bfs(int start); // BFS iniciada em um vértice start
        void _findCapital();
        const Graph& graph;
};


#endif // BFS_HPP
