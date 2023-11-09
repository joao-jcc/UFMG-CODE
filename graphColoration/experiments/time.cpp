//
// Created by João Costa on 07/11/23.
//

#include <iostream>
#include <fstream>
#include <dirent.h>
#include <istream>
#include <filesystem>
#include <string>
#include <chrono>

#include "heap.hpp"
#include "linkedList.hpp"
#include "utils.hpp"
#include "sort.hpp"

int read_graph(const char* input_path, Vertex<int>**& graph) {
    std::ifstream input_file(input_path);
    if (!input_file.is_open()) {
        std::cerr << "Error: Could not open the input file for reading." << std::endl;
        return 0;
    }

    int n_vertex; // Number of vertices in the graph
    input_file >> n_vertex;
    graph = new Vertex<int>*[n_vertex]; // array of pointers to Vertex;

    for (int i = 0; i < n_vertex; ++i) {
        graph[i] = new Vertex<int>();

        int degree;
        input_file >> degree;
        for (int j = 0; j < degree; ++j) {
            int neighbor;
            input_file >> neighbor;
            graph[i]->append(neighbor);
        }
    }

    for (int i = 0; i < n_vertex; ++i) {
        unsigned color;
        input_file >> color;
        graph[i]->set_color(color);
    }

    input_file.close();
    return n_vertex;
}



double measure_time(Vertex<int>** graph, int n_vertex, char sort_option) {
    // Declare start_time and end_time variables outside the switch
    auto start_time = std::chrono::high_resolution_clock::now();
    auto end_time = std::chrono::high_resolution_clock::now();

    switch (sort_option) {
        case 'b':
            bubble_sort(graph, n_vertex);
            break;

        case 's':
            selection_sort(graph, n_vertex);
            break;

        case 'i':
            insertion_sort(graph, n_vertex);
            break;

        case 'q':
            quick_sort(graph, n_vertex);
            break;

        case 'p':
            heap_sort(graph, n_vertex);
            break;

        case 'm':
            merge_sort(graph, n_vertex);
            break;

        case 'y':
            count_sort(graph, n_vertex);
            break;

        default:
            bubble_sort(graph, n_vertex);
            break;
    }

    // Calculate the elapsed time after the sorting operation
    end_time = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed_time = end_time - start_time;

    return elapsed_time.count(); // Sorting time in seconds
}



void store_time(const char* input_path, const char* output_path, char sort_option) {
    Vertex<int>** graph = nullptr;
    int n_vertex = read_graph(input_path, graph);

    if (n_vertex > 0) {
        double sorting_time = measure_time(graph, n_vertex, sort_option);

        // Store sorting time in the output file
        std::ofstream result_file(output_path);
        if (result_file.is_open()) {
            result_file << sorting_time << std::endl;
            result_file.close();
        } else {
            std::cerr << "Error: Could not open the output file for writing." << std::endl;
        }

        // Clean up memory
        free_graph(graph, n_vertex);
    }
}



// Function to process and store the sorting time for all graphs
void store_time_all(const char* input_dir, const char* output_path, char sort_option) {
    std::ofstream result_file(output_path);
    if (!result_file.is_open()) {
        std::cerr << "Error: Could not open the output file for writing." << std::endl;
        return;
    }

    DIR* dir;
    struct dirent* entry;

    if ((dir = opendir(input_dir)) != nullptr) {
        while ((entry = readdir(dir)) != nullptr) {
            if (entry->d_type == DT_REG) {
                std::string filename = entry->d_name;
                std::string file_path = std::string(input_dir) + "/" + filename;
                Vertex<int>** graph = nullptr;
                int n_vertex = read_graph(file_path.c_str(), graph);

                if (n_vertex > 0) {
                    double sorting_time = measure_time(graph, n_vertex, sort_option);
                    result_file << filename << ": " << sorting_time << " sec" << std::endl;

                    // Clean up memory
                    free_graph(graph, n_vertex);
                }
            }
        }
        closedir(dir);
    } else {
        std::cerr << "Error: Could not open the input directory." << std::endl;
    }

    result_file.close();
}



int main(void) {
    const char* input_dir = "experiments/graphs";
    const char* output_dir = "experiments/results";

    if (!std::filesystem::exists(input_dir)) {
        std::cerr << "Error: Input directory does not exist." << std::endl;
        return 1;
    }

    char sorting_algorithms[] = {'b', 's', 'i', 'q', 'p', 'm', 'y'};
    const char* algorithm_names[] = {"bubble_sort", "selection_sort", "insertion_sort", "quick_sort", "heap_sort", "merge_sort", "count_sort"};


    for (int i = 0; i < 7; ++i) {
        std::string output_path = output_dir;
        output_path += "/";
        output_path += algorithm_names[i];
        output_path += ".txt";
        store_time_all(input_dir, output_path.c_str(), sorting_algorithms[i]);
    }

    return 0;
}