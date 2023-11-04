//
// Created by João Costa on 03/11/23.
//

#include "heap.hpp"


Heap::Heap(int size) {
    _node = new Tuple[size];
    _size = 0;
}

Heap::~Heap() {
    delete _node;
}

bool Heap::criterium(Tuple tuple1, Tuple tuple2) {
    // color criterium
    if (tuple1.color > tuple2.color) {
        return true;
    };

    // id criterium
    if ((tuple1.color == tuple2.color) && (tuple1.id > tuple2.id)) {
        return true;
    }

    return false;
}

int Heap::_get_ancestral(int position) {
    return (position - 1) / 2;
}


int Heap::_get_left_sucessor(int position) {
    return 2 * position + 1;
}

int Heap::_get_right_sucessor(int position) {
    return 2 * position + 2;
}


bool Heap::empty() {
    return _size == 0;
}

void Heap::insert(Tuple tuple) {
    if (empty()) {
        _node[0] = tuple;
        ++_size;
        return;
    }

    _node[_size] = tuple;
    ++_size;

    _heapify_upper();
}

Tuple Heap::remove() {
    if (_size < 0) {
        std::cerr << "Empty Heap!" << std::endl;
        exit(1);
    }

    Tuple root = _node[0];
    _node[0] = _node[_size - 1];
    --_size; // o size-1 fica esquecido, porém a alocação é estática
    _heapify_down();
    return root;
}
void Heap::_heapify_down() {
    int position = 0;
    while (position < _size) {
        int l_position = _get_left_sucessor(position);
        int r_position = _get_right_sucessor(position);
        int smallest = position;

        if (l_position < _size && criterium(_node[smallest], _node[l_position])) {
            smallest = l_position;
        }
        if (r_position < _size && criterium(_node[smallest], _node[r_position])) {
            smallest = r_position;
        }

        if (smallest == position) {
            return;
        }

        swap(_node[position], _node[smallest]);
        position = smallest;
    }
}


void Heap::_heapify_upper() {
    int position = _size - 1;

    while (position != 0 && (criterium(_node[_get_ancestral(position)], _node[position]))) {
        swap(_node[position], _node[_get_ancestral(position)]);
        position = _get_ancestral(position);
    }
}

void Heap::print(int position, int level, int indentation) {
    if (position > _size - 1) {
        return;
    }

    for (int i=0; i < indentation*level; ++i) {
        std::cout << " ";
    };

    int color = _node[position].color;
    int id = _node[position].id;

    std::cout << "(" << color << ", " << id << ")" << std::endl;
    print(_get_left_sucessor(position), level+1);
    print(_get_right_sucessor(position), level+1);
}

void Heap::swap(Tuple& tuple1, Tuple& tuple2) {
    Tuple temp = tuple1;
    tuple1 = tuple2;
    tuple2 = temp;
}
