#ifndef TSP_HPP
#define TSP_HPP

#include <limits>
#include <vector>
#include <iostream>
#include "graph.hpp"

#define MAX_SIZET std::numeric_limits<size_t>::max()
#define UNDEFINED std::numeric_limits<size_t>::max()

// Estrutura para armazenar o estado na memoização
struct State {
    size_t cost;       // Custo do caminho parcial
    size_t next_sbin;  // Próximo sbin (estado filho)
    size_t next_root;
};


class TSP {
    public:
        TSP(Graph graph);

        void solve();
        void print_solution();
    
    public:
        Graph graph;
        std::vector<size_t> best_path;
        size_t best_cost;
        size_t count_solutions;

    private:
        // Soluções do TSP
        void _brute_force();
        void _brute_force_aux(size_t root, 
                              size_t cost, 
                              std::vector<size_t>& path,
                              size_t index,
                              size_t end);

        void _greedy();

        void _dynamic();
        State _dynamic_aux(size_t root,
                           size_t sbin,
                           size_t end,
                           std::vector<std::vector<State>>& mem);
};

#endif