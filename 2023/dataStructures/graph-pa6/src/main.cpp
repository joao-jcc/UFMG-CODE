#include <iostream>
#include <getopt.h> // Include for getopt

#include "graph.hpp"
#include "utils.hpp"

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "Use: [executable] [-d|-n|-k]" << std::endl;
        exit(1);
    }

    Grafo grafo;
    read_graph(&grafo);

    int option_data = false;
    int option_neighbors = false;
    int option_complete = false;

    // Use getopt to parse command-line options
    int opt;
    while ((opt = getopt(argc, argv, "dnk")) != -1) {
        switch (opt) {
            case 'd':
                option_data = true;
                break;
            case 'n':
                option_neighbors = true;
                break;
            case 'k':
                option_complete = true;
                break;
            default:
                std::cerr << "Uso: [executable] [-d|-n|-k]" << std::endl;
                exit(1);
        }
    }

    if (option_data) {
        print_data(&grafo);
    } 
    
    else if (option_neighbors) {
        print_neighbors(&grafo);
    } 
    
    else if (option_complete) {
        print_complete(&grafo);
    }

    return 0;
}
