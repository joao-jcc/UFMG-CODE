#include "heap.hpp"


Heap::Heap(int max_size) {
    _node = new Aresta[max_size];
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

void Heap::insert(Aresta aresta) {
    if (empty()) {
        _node[0] = aresta;
        ++_size;
        return;
    }

    _node[_size] = aresta;
    ++_size;

    _heapify_upper();
} 

Aresta Heap::remove() {
    if (_size < 0) {
        std::cerr << "Empty Heap!" << std::endl;
        exit(1);
    }

    Aresta root = _node[0];
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

        if (l_position < _size && _node[l_position].custo < _node[smallest].custo) {
            smallest = l_position;
        }
        if (r_position < _size && _node[r_position].custo < _node[smallest].custo) {
            smallest = r_position;
        }

        if (smallest == position) {
            return;
        }

        std::swap(_node[position], _node[smallest]);
        position = smallest;
    }
}


void Heap::_heapify_upper() {
    int position = _size - 1;
    while (position != 0 && (_node[_get_ancestral(position)].custo > _node[position].custo)) {
        std::swap(_node[position], _node[_get_ancestral(position)]);
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

    int custo = _node[position].custo;
    int u = _node[position].u;
    int v = _node[position].v;

    std::cout << "(" << u << ", " << v << ", " << custo << ")" << std::endl;
    print(_get_left_sucessor(position), level+1);
    print(_get_right_sucessor(position), level+1);
}
