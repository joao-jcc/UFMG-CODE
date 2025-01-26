#include "time.hpp"

int main(void) {
    TSP tsp;
    Time time(tsp);

    time.execute();
    time.save("results/t00.txt", 1000);
}