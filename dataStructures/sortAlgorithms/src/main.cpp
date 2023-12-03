#include <iostream>
#include <stdlib.h>

#include "algorithms.h"

int main(void) {

    const int n = 5;
    int array[n] = {-1, 90, 3, 2, 1};

    insertion_sort(array, n);


    for (int v : array) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

	return 0;
}