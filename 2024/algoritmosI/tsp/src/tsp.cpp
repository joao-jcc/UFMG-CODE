#include "tsp.hpp"

TSP::TSP() : 
    graph(nullptr), 
    best_path(std::vector<size_t>()), 
    best_cost(UNDEFINED),
    initialized(false) {}

void TSP::set(Graph& graph) { 
    this->graph = &graph; 
    initialized=true; 
    best_cost = UNDEFINED;
    best_path.clear();
}

void TSP::print_solution() {
    std::cout << "---- SOLUTION ----" << std::endl;
    for (size_t u : best_path) {
        std::cout << graph->index_to_name[u] << " ";
    }
    std::cout << std::endl;

    std::cout << "cost: " << best_cost << std::endl;
}


void TSP::solve(char method) {
    if (!initialized) {
        std::cerr << "ERRO: TSP não inicializado!" << std::endl;
        exit(1);
    }
    switch(method) {
        case 'b':
            _brute_force();
            break;
        
        case 'g':
            // _greedy(graph);
            break;
        
        case 'd':
            // _dynamic(graph);
            break;
        
        default:
            _brute_force();
            break;
    }

}

void TSP::_brute_force_aux(size_t root, 
                           size_t cost, 
                           std::vector<size_t>& path,
                           size_t index,
                           size_t end) {
    path[root] = index;

    for (Node node : graph->g[root]) {
        if (node.v == end && index == graph->N - 1) {

            if (best_cost > cost + node.w) {
                best_cost = cost + node.w; best_path = path;
            }

            path[root] = UNDEFINED; return;
        }

        // branch and bound
        if (path[node.v] != UNDEFINED) {continue;}
        // branch and bound
        // if (cost + node.w >= best_cost) { continue; }

        _brute_force_aux(node.v, cost + node.w, path, index + 1, end);
    }

    path[root] = UNDEFINED;
}


void TSP::_brute_force() {
    std::vector<size_t> path(graph->N, UNDEFINED);
    for (size_t root = 0; root < graph->N; ++root) {
        _brute_force_aux(root, 0, path, 0, root);
    }
}