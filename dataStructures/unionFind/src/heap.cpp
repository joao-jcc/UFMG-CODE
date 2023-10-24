#include "heap.hpp"


Heap::Heap(int max_size) {
    _node = new int[max_size];
    _size = 0;
}

Heap::~Heap() {
    delete _node;
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

void Heap::insert(int number) {
    if (empty()) {
        _node[0] = number;
        ++_size;
        return;
    }

    _node[_size] = number;
    ++_size;

    _heapify_upper();
} 

int Heap::remove() {
    if (_size < 0) {
        std::cerr << "Empty Heap!" << std::endl;
        exit(1);
    }

    int root = _node[0];
    _node[0] = _node[_size - 1];
    --_size; // o size-1 fica esquecido, porém a alocação é estática
    _heapify_down();

    return root;
}

void Heap::_heapify_down() {
    int position = 0;
    while(position < _size) {
        int l_position = _get_left_sucessor(position);
        int r_position = _get_right_sucessor(position);
        // heap fixed
        if ((_node[position] <= _node[l_position]) && _node[position] <= _node[r_position]) {
            return;
        }

        if (l_position >= _size || r_position >= _size) {
            return;
        }

        // get the position of the minor node
        int m_position = _node[l_position] < _node[r_position] ? l_position : r_position;
        // swap posicao e minor
        swap(_node[position], _node[m_position]);
        position = m_position;
    }


}

void Heap::_heapify_upper() {
    int position = _size - 1;
    while (position != 0 && (_node[_get_ancestral(position)] > _node[position])) {
        swap(_node[position], _node[_get_ancestral(position)]);
        position = _get_ancestral(position);
    }
}

void Heap::print(int position, int level) {
    if (position > _size - 1) {
        return;
    }

    for (int i=0; i < level; ++i) {
        std::cout << " ";
    };

    std::cout << _node[position] << std::endl;
    print(_get_left_sucessor(position), level+1);
    print(_get_right_sucessor(position), level+1);
}
