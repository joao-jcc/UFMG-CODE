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

    if (!validation) {
        std::cout << validation << std::endl;
        return 0;
    } else {
        //sort
        sort(graph, n_vertex, sort_option);

        std::cout << validation;
        // printing graph
        print_graph_id(graph, n_vertex);
    }


    // releasing memory
    free_graph(graph, n_vertex);

    return 0;
}
