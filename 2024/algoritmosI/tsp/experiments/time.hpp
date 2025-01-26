#ifndef TIME_HPP
#define TIME_HPP

#include <vector>
#include <chrono>
#include <string>
#include <fstream>
#include "tsp.hpp"

class Time {
    public:
        Time(TSP tsp);

        std::chrono::milliseconds execute(size_t repeat=1000, char method='b');
        void executeAll(std::string folder, std::string save_path, size_t repeat, char method);

        void save(std::string path, size_t times);
    
    private:
        TSP tsp;
        std::vector<std::chrono::milliseconds> clocks; 

};

#endif