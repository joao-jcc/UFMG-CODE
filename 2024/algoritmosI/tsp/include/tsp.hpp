#ifndef TSP_HPP
#define TSP_HPP

#include <limits>
#include "graph.hpp"

#define MAX_SIZET std::numeric_limits<size_t>::max()
#define UNDEFINED std::numeric_limits<size_t>::max()


class TSP {
    public:
        TSP();

        void solve();
        void read(const std::string& file_path); 
        void print_solution();
        char method;
    
    private:
        Graph graph;
        std::vector<size_t> best_path;
        size_t best_cost;

    private:
        void _read();

        // Soluções do TSP
        void _brute_force_aux(size_t root, 
                    size_t total_cost, 
                    std::vector<size_t>& path, 
                    size_t n,
                    size_t end);

        void _brute_force();

        void _greedy();
        void _dynamic();


};

#endif