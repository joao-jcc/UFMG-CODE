#include "tsp.hpp"

// funções para gerenciar conjuntos bit-wise
static size_t full_set (size_t n) {
    return (1 << n) - 1;
}

static size_t del_set (size_t sbin, size_t element) {
    return ~(1 << element) & sbin;
}

static size_t init_set (size_t n, size_t element) {
    return del_set(full_set(n), element);
}

static bool find_set (size_t set, size_t element) {
    return ((1 << element) & set) == (1 << element);
}


// TSP

TSP::TSP(Graph graph) :
    graph(graph), 
    best_path(std::vector<size_t>()), 
    best_cost(UNDEFINED),
    count_solutions(0) {}


void TSP::print_solution() {
    std::cout << best_cost << std::endl;
    for (size_t i=0; i < best_path.size(); ++i) {
        if (i != best_path.size()-1) {
            std::cout << graph.index_to_name[best_path[i]] << " ";
        } else {
            std::cout << graph.index_to_name[best_path[i]] << std::endl;
        }
    }
}


void TSP::solve() {

    switch(graph.method) {
        case 'b':
            _brute_force();
            break;
        
        case 'g':
            _greedy();
            break;
        
        case 'd':
            _dynamic();
            break;
        
        default:
            _brute_force();
            break;
    }

}



size_t TSP::_brute_force_aux(size_t root, size_t sbin, size_t end) {

    // caso base: retorna o peso da aresta conectada à origem 0
    if (sbin == 0) {
        return graph.matrix[root][end];
    }

    size_t min_cost = MAX_SIZET;
    for (size_t v=0; v < graph.N; ++v) {
        if (find_set(sbin, v)) {

            size_t new_sbin = del_set(sbin, v);
            size_t cost = graph.matrix[root][v] + _brute_force_aux(v, new_sbin, end);
            
            min_cost = min_cost > cost ? cost : min_cost;
        }
    }


    return min_cost;
}


void TSP::_brute_force() {
    for (size_t root=0; root < graph.N; ++root) {
        size_t cost = _brute_force_aux(root, init_set(graph.N, root), root);
        best_cost = best_cost > cost ? cost : best_cost;
    }
}


void TSP::_greedy() {
   

}

void TSP::_dynamic() {
    
}