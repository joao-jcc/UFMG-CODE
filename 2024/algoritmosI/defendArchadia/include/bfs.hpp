// bfs.hpp

#ifndef BFS_HPP
#define BFS_HPP

#include <vector>
#include <queue>
#include "graph.hpp"



struct InfoBFS
{
    size_t cost; // soma das profundidades de cada vértice
    size_t nExplored; // número de vértices explorados na bfs
    std::vector<bool> explored;
    std::vector<size_t> depths;
};


class BFS {
    public:
        BFS(const Graph& graph);
        std::vector<size_t> findMinPath(size_t start, size_t end); // caminho mínimo entre dois vértices quaisquer, incluindo start e end.

        size_t capital;
        size_t capitalCost;
        std::vector<size_t> capitalDepths;
        std::vector<std::vector<size_t>> allParents; // armazena todas as árvores das BFS's

        void print();

    private:
        InfoBFS _bfs(size_t start); // BFS iniciada em um vértice start
        void _findCapital();
        const Graph& graph;

};


#endif // BFS_HPP
