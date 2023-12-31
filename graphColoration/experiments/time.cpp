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

    char letter;
    input_file >> letter;

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



double measure_time(Vertex<int>** graph, int n_vertex, char option) {
    // Declare start_time and end_time variables outside the switch
    auto start_time = std::chrono::high_resolution_clock::now();
    auto end_time = std::chrono::high_resolution_clock::now();

    switch (option) {
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
        
        case 'v':
            validate_graph(graph, n_vertex);
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



void save_time(const char* input_path, const char* output_path, char option) {
    Vertex<int>** graph = nullptr;
    int n_vertex = read_graph(input_path, graph);

    if (n_vertex > 0) {
        double sorting_time = measure_time(graph, n_vertex, option);

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
void save_time_all(const char* input_dir, const char* output_path, char option) {
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
                    // Extracting the number from the filename
                    std::string number_str = filename.substr(filename.find('_') + 1, filename.find('.') - filename.find('_') - 1);
                    int number = std::stoi(number_str);

                    double sorting_time = measure_time(graph, n_vertex, option);
                    result_file << number << " " << sorting_time << " sec" << std::endl;

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

    // sem heapsort
//    char sorting_algorithms[] = {'b', 's', 'i', 'q', 'm', 'y'};
//    const char* algorithm_names[] = {"bubble_sort", "selection_sort", "insertion_sort", "quick_sort", "merge_sort", "count_sort"};

    char sorting_algorithms[] = {'y'};
    const char* algorithm_names[] = {"validation"};




    for (int i = 0; i < 1; ++i) {
        std::string output_path = output_dir;
        output_path += "/";
        output_path += algorithm_names[i];
        output_path += ".txt";
        save_time_all(input_dir, output_path.c_str(), sorting_algorithms[i]);
    }

    return 0;
}