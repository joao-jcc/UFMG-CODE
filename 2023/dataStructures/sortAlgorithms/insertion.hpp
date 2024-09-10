#ifndef INSERTION_HPP
#define INSERTION_HPP


inline void insertion_sort(int* array, int size) {
	for (int i=1; i<size; ++i) {
		int key = array[i];

		int j = i - 1;

		while ((key < array[j]) && (j >= 0)) {

			array[j+1] = array[j];
			--j;

		}

		array[j+1] = key;


	}
}


#endif