#include <iostream>
#include <stdlib.h>

#include "insertion.hpp"
#include "selection.hpp"

int main(int argc, char* argv[]) {

	int size = argc - 1;

	int numbers[size];
	for (int i=1; i<argc; ++i) {
		numbers[i-1] = std::strtol(argv[i], NULL, 10);
	}


	// insertion_sort(numbers, size);
	selection_sort(numbers, size);

	for (int number : numbers) {
		std::cout << number << " ";
	} 
	std::cout << std::endl;


	return 0;
}