#ifndef SELECTION_HPP
#define SELECTION_HPP


inline void swap_int(int* n1, int* n2) {
	int temp = *n1;
	*n1 = *n2;
	*n2=temp;
}


inline void selection_sort(int* array, int size) {

	for (int i=0; i < size; ++i) {

		int index_min = i;
		for (int j=i+1; j < size; ++j) {

			if (array[index_min] > array[j]) {
				index_min = j;
			}

		}

		swap_int(array + i, array + index_min);
	}

}


#endif
