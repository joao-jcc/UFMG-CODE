#include <iostream>
#include "tsp.hpp"
#include "time.hpp"


int main(void) {

    Time time;
    time.executeAll("testCases/inputs", "greedy_results.txt", 1, 'g');
    time.executeAll("testCases/inputs", "dynamic_results.txt", 1, 'd');
    time.executeAll("testCases/inputs", "brute_results.txt", 1, 'b');
    
    


    return 0;
}