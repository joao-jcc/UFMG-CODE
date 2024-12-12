#include <iostream>
#include <vector>
#include "graph.hpp"
#include "flow.hpp"


int main() {

    Graph ggr;
    ggr.print();

    Flow flow(ggr);

    std::cout << "max flow: " << flow.fordFulkerson() << std::endl;

    return 0;
}