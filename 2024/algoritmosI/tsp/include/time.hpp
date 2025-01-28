#ifndef TIME_HPP
#define TIME_HPP

#include <vector>
#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include "tsp.hpp"


class Time {
    public:
        Time();

        std::chrono::microseconds execute(char method, size_t repeat=1000);
        void executeAll(std::string folder, std::string save_path, size_t repeat, char method);

        void save(std::string path);
    
    private:
        TSP tsp;
        std::vector<std::chrono::microseconds> clocks; 
        std::vector<size_t> number_vertices;

};

#endif