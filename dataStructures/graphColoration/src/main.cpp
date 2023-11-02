#include <iostream>
#include "linkedList.hpp"
#include "utils.hpp"

int main() {
    //graph
    LinkedList<int>** graph = nullptr;
    int n_vertex = read_graph(graph);


    print_graph(graph, n_vertex);

    swap_vertex(graph[1], graph[2]);

    print_graph(graph, n_vertex);



    return 0;
}
