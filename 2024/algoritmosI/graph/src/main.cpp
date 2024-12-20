#include <iostream>
#include <vector>
#include "graph.hpp"
#include "bfs.hpp"
#include "topological.hpp"
#include "dijkstra.hpp"
#include "prim.hpp"

int main(void) {
    std::vector<std::vector<wVertice> > graphW = readW("data/gw1.txt");

    std::vector<int> parents = prim(graphW, 0);

    for (int i=0; i < parents.size(); ++i) {
        std::cout << i << " " << parents[i] << std::endl;
    }
    
    return 0;
}