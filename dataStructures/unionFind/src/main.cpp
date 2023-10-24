#include <iostream>
#include "heap.hpp"
#include "utils.hpp"

int main(void) {
    
    Heap heap(10);
    
    heap.insert(13);
    heap.insert(15);
    heap.insert(8);
    heap.insert(23);
    heap.insert(21);
    heap.insert(9);
    heap.insert(2);
    // heap.remove();
    // heap.remove();
    // heap.remove();
    // heap.remove();
    // heap.remove();
    // heap.remove();
    // heap.remove();
    heap.print();


    return 0;
}