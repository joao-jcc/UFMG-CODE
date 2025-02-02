#include <iostream>
#include "tsp.hpp"


int main(void) {
    // inicializa grafo e tsp
    Graph g;
    TSP tsp(g);
    
    // resolve o tsp
    tsp.solve();

    // exibe solução
    tsp.print_solution();

    return 0;
}