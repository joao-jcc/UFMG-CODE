#ifndef HEAP_HPP
#define HEAP_HPP

#include <iostream>
#include "utils.hpp"

class Heap {
    
    public:
        Heap(int max_size);
        ~Heap();

        void insert(int number);
        int remove();
        bool empty();
        
        void print(int position=0, int level=0);

    private:
        int _get_ancestral(int position);
        int _get_left_sucessor(int position);
        int _get_right_sucessor(int position);

        void _heapify_upper();
        void _heapify_down();
        
        int _size;
        int* _node;

};

#endif