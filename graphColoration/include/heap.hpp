//
// Created by João Costa on 03/11/23.
//

#ifndef HEAP_HPP
#define HEAP_HPP

#include <iostream>

struct Tuple {
    unsigned color;
    unsigned id;
};

class Heap {

public:
    Heap(int size);
    ~Heap();

    void insert(Tuple tuple);
    Tuple remove();
    bool empty();

    void print(int position=0, int level=0, int indentation=3);


private:
    int _get_ancestral(int position);
    int _get_left_sucessor(int position);
    int _get_right_sucessor(int position);

    void _heapify_upper();
    void _heapify_down();

    bool criterium(Tuple tuple1, Tuple tuple2);

    void swap(Tuple& tuple1, Tuple& tuple2);

    int _size;
    Tuple* _node;

};

#endif //HEAP_HPP
