//
// Created by João Costa on 07/11/23.
//

#include <iostream>
#include <fstream>
#include <istream>

#include "linkedList.hpp"
#include "utils.hpp"
#include "sort.hpp"


int read_graph(Vertex<int>**& graph, std::istream& input = std::cin) {
    int n_vertex; // Number of vertices in the graph

    input >> n_vertex;
    graph = new Vertex<int>*[n_vertex]; // array of pointers to Vertex;

    for (int i = 0; i < n_vertex; ++i) {
        graph[i] = new Vertex<int>();

        int degree;
        input >> degree;
        for (int j = 0; j < degree; ++j) {
            int neighbor;
            input >> neighbor;
            graph[i]->append(neighbor);
        }
    }

    for (int i = 0; i < n_vertex; ++i) {
        unsigned color;
        input >> color;
        graph[i]->set_color(color);
    }

    return n_vertex;
}


void write_graph(Vertex<int>** graph, int n_vertex, std::ostream& output) {
    output << n_vertex << std::endl;

    for (int i = 0; i < n_vertex; ++i) {
        Vertex<int>* vertex = graph[i];
        unsigned neighbors = vertex->get_size();
        output << neighbors << ' ';

        Node<int>* temp = vertex->get_first();
        while (temp) {
            output << temp->data << ' ';
            temp=temp->next;
        }

        output << std::endl;
    }

    for (int i = 0; i < n_vertex; ++i) {
        unsigned color = graph[i]->get_color();
        output << color << std::endl;
    }
}



int main(void) {
    const char* input_path = "experiments/graphs/graph05.txt";
    const char* output_path = "experiments/results/output_graph05.txt";

    Vertex<int>** graph = nullptr; // Initialize the graph pointer

    // Read the graph from the input file
    std::ifstream input_file(input_path);
    if (input_file.is_open()) {
        int n_vertex = read_graph(graph, input_file);
        input_file.close();

        // Write the graph to the output file
        std::ofstream output_file(output_path);
        if (output_file.is_open()) {
            write_graph(graph, n_vertex, output_file);
            output_file.close();
        } else {
            std::cerr << "Error: Could not open the output file for writing." << std::endl;
        }

        // Clean up memory
        free_graph(graph, n_vertex);

    } else {
        std::cerr << "Error: Could not open the input file for reading." << std::endl;
    }

    return 0;
}
