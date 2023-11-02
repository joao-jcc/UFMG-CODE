#include <iostream>
#include "linkedList.hpp"
#include "utils.hpp"
#include "sort.hpp"

int main() {
    //graph
    LinkedList<int>** graph = nullptr;
    int n_vertex = read_graph(graph);


    print_graph(graph, n_vertex);

    selection_sort(graph, n_vertex);

    print_graph(graph, n_vertex);

    delete graph;

    return 0;
}
