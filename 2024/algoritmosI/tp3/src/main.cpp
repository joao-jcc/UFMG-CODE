#include <iostream>
#include "tsp.hpp"


int main(void) {
    
    Graph g;
    TSP tsp(g);
    
    tsp.solve();
    tsp.print_solution();

    return 0;
}