#ifndef DFS_HPP
#define DFS_HPP

#include <vector>
#include <stack>
#include "bfs.hpp"


class DFS {
    public:
        // Construtor que recebe uma referência ao objeto Graph
        DFS(const Graph& graph);

        void findBattalions(const std::vector<size_t>& depths, size_t capital);
        std::vector<std::vector<bool>> sccEdges;
        std::vector<size_t> battalions;

        std::vector<size_t> components;
        size_t nComponents;

        void print();

    private:
         // Calcula a ordem de "morte" dos nós na DFS (usado no algoritmo de Kosaraju)
        void _dfs(size_t start, std::vector<bool>& explored);

        // Realiza DFS para identificar componentes fortemente conexas
        void _dfsSCC(size_t start, std::vector<bool>& explored);

         // Aplica o algoritmo de Kosaraju para encontrar SCC's
        void _kosaraju();

        // Gera todas as arestas de cada componente SCC
        void _genEdgesSCC();


        const Graph& graph;
        std::stack<size_t> deathOrder;
};

#endif // DFS_HPP