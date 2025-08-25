#include <iostream>
#include "tsp.hpp"


int main(void) {
    
    Graph g; g.read();

    g.print();
    TSP tsp; tsp.set(g);

    tsp.solve('b');

    tsp.print_solution();

    return 0;
}