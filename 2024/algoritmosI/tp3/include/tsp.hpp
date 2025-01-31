#ifndef TSP_HPP
#define TSP_HPP

#include <limits>
#include "graph.hpp"

#define MAX_SIZET std::numeric_limits<size_t>::max()
#define UNDEFINED std::numeric_limits<size_t>::max()


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

    public:
        // Soluções do TSP
        void _brute_force();
        size_t _brute_force_aux(size_t root, size_t sbin, size_t end);

        void _greedy();

        void _dynamic();

};

#endif