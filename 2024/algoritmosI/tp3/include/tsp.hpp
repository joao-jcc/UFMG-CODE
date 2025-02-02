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
    size_t next_sbin;  // Próximo subconjunto de vértices visitados
    size_t next_root;  // Próximo vértice a ser visitado
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

    private:
        // Algoritmos para resolver o TSP
        void _brute_force();  // Força bruta
        void _brute_force_aux(size_t root, 
                              size_t cost, 
                              std::vector<size_t>& path,
                              size_t index,
                              size_t end);

        void _greedy();  // Algoritmo guloso

        void _dynamic();  // Programação dinâmica
        State _dynamic_aux(size_t root,
                           size_t sbin,
                           size_t end,
                           std::vector<std::vector<State>>& mem);
};

#endif
