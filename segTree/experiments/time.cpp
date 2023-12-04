//
// Created by João Costa on 07/11/23.
//
#include <filesystem>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <istream>

#include <string>
#include <chrono>

#include <iostream>
#include "utils.hpp"
#include "simpleVector.hpp"
#include "matrix.hpp"
#include "segTree.hpp"



#include <iomanip>  // Include for std::setprecision

namespace fs = std::filesystem;


void read_from_txt_and_write_to_csv(const std::string& filePath, std::ofstream& csvFile) {
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return;
    }

    int n, q;
    file >> n >> q;

    // Assuming that SegTree and other classes have been defined and included
    SegTree seg_tree(n);
//    SimpleVector simple_vec(n);

    double time_of_u = 0.0;  // Initialize time_of_u to 0 seconds with double precision
    double time_of_q = 0.0;  // Initialize time_of_q to 0 seconds with double precision

    char operation;
    while (q--) {
        file >> operation;

        if (operation == 'u') {
            // index
            int i;
            file >> i;

            // matrix
            Matrix* matrix = new Matrix(2, 2, false);

            // Skip two lines in the file
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            auto start_time_update = std::chrono::high_resolution_clock::now();
            seg_tree.update(i, matrix, 1, 0, n - 1);
//            simple_vec.update(i, matrix);
            auto end_time_update = std::chrono::high_resolution_clock::now();

            auto duration_update = std::chrono::duration<double>(end_time_update - start_time_update);
            time_of_u += duration_update.count();
        } else if (operation == 'q') {
            int born_time, death_time;
            Vector2D point;
            file >> born_time >> death_time >> point.x >> point.y;

            auto start_time_query = std::chrono::high_resolution_clock::now();
            Matrix* matrix = seg_tree.query(born_time, death_time, 1, 0, n - 1);
//                Matrix* matrix = simple_vec.query(born_time, death_time);
            auto end_time_query = std::chrono::high_resolution_clock::now();

            auto duration_query = std::chrono::duration<double>(end_time_query - start_time_query);
            time_of_q += duration_query.count();
        }
    }

    file.close();

    csvFile << n << "," << std::fixed << std::setprecision(9) << time_of_u << "," << std::setprecision(9) << time_of_q << "\n";

}



// Assume the definition of read_from_txt_and_write_to_csv and other classes are included

void process_files_in_folder(const std::string& folderPath, const std::string& csvFilePath) {
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.path().extension() == ".txt") {
            std::ifstream file(entry.path().string());
            std::ofstream csvFile(csvFilePath, std::ios::app);  // Open CSV file in append mode

            if (file.is_open() && csvFile.is_open()) {
                read_from_txt_and_write_to_csv(entry.path().string(), csvFile);
                file.close();
                csvFile.close();
            } else {
                std::cerr << "Error opening files for processing: " << entry.path().string() << std::endl;
            }
        }
    }
}

int main() {
//    const std::string folderPath = "experiments/tests"; // Change this to your actual folder path
//    const std::string csvFilePath = "experiments/results/segTree.csv";  // Change this to your desired CSV file path
//    process_files_in_folder(folderPath, csvFilePath);
    int n, q;
    std::cin >> n >> q;

    SegTree seg_tree(n);
    SimpleVector simple_vec(n);

    char operation;
    while(q--) {
        std::cin >> operation;

        if (operation == 'u') {
            // index
            int i;
            std::cin >> i;

            // matrix
            Matrix* matrix = new Matrix(2, 2, false);
            matrix->read();

            simple_vec.update(i, matrix);

        }

        else if (operation == 'q') {
            int born_time, death_time;
            Vector2D point;
            std::cin >> born_time >> death_time >> point.x >> point.y;

            Matrix* matrix = simple_vec.query(born_time, death_time);

            Vector2D new_point = (*matrix) * point;
            new_point.print();

        }
    }


    return 0;
}