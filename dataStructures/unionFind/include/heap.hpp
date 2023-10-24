#ifndef HEAP_HPP
#define HEAP_HPP

#include <iostream>
#include "unionFind.hpp"

class Heap {
    
    public:
        Heap(int max_size);
        ~Heap();

        void insert(Aresta aresta);
        Aresta remove();
        bool empty();
        
        void print(int position=0, int level=0, int indentation=3);

    private:
        int _get_ancestral(int position);
        int _get_left_sucessor(int position);
        int _get_right_sucessor(int position);

        void _heapify_upper();
        void _heapify_down();
        
        int _size;
        Aresta* _node;

};

#endif