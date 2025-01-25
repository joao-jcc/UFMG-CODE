#include <iostream>
#include "tsp.hpp"


int main(void) {

    TSP tsp; tsp.solve();
    tsp.print_solution();
    
    return 0;
}