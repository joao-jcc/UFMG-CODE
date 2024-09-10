//
// Created by João Costa on 30/11/23.
//

#include "algorithms.h"

void swap(int& n1, int& n2) {
    int temp = n1;
    n1 = n2;
    n2 = temp;
}

void bubble_sort(int* array, int n) {
    for (int i=1; i < n; ++i) {
        for (int j=0; j < n-i; ++j) {
            if (array[j] > array[j+1]) {
                swap(array[j], array[j+1]);
            }
        }
    }
}


void selection_sort(int* array, int n) {
    for (int i = 0; i < n-1; ++i) {
        int min = i;
        for(int j = i+1; j < n; ++j) {
            if (array[j] < array[min]) {
                min = j;
            }
        }

        swap(array[i], array[min]);
    }
}


void insertion_sort(int* array, int n) {
    for (int i = 1; i < n; ++i) {
        int value = array[i];
        int j = i-1;
        while((j >= 0) && (value < array[j])) {
            array[j+1] = array[j];
            --j;
        }

        array[j+1] = value;
    }
}