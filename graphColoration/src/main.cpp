#include <iostream>
#include "linkedList.hpp"
#include "utils.hpp"
#include "sort.hpp"

int main() {

    // sort option
    char sort_option;
    std::cin >> sort_option;

    // read graph
    Vertex<int>** graph = nullptr;
    int n_vertex = read_graph(graph);

    // validation
    bool validation = validate_graph(graph, n_vertex);
    std::cout << validation;

    if (!validation) {
        return 0;
    } else {
        //sort
        sort(graph, n_vertex, sort_option);

        // printing graph
        print_graph_id(graph, n_vertex);
    }


    // releasing memory
    delete[] graph;

    return 0;
}
