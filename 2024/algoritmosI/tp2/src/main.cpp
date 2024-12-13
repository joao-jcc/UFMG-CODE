#include <iostream>
#include <vector>
#include "graph.hpp"
#include "flow.hpp"


int main() {

    Graph ggr;
    Flow flow(ggr);
    flow.print();
    
    return 0;
}