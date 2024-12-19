#include <iostream>
#include <vector>
#include "graph.hpp"
#include "flow.hpp"


int main() {

    Graph ggr;
    ggr.print();
    Flow flow(ggr);
    flow.print();
    
    return 0;
}