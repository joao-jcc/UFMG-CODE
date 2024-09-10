//
// Criado por João Costa em 03/11/23.
//

#include "heap.hpp"

// Construtor: Inicializa um heap vazio com alocacao dinâmica de memória para um array de Tuples
Heap::Heap(int size) {
    _node = new Tuple[size];
    _size = 0;
}

// Destrutor: Libera a memória alocada para o array de Tuples
Heap::~Heap() {
    delete[] _node;
}

// Critério de comparação para determinar a ordem no heap (usado na comparação de Tuples)
bool Heap::criterium(Tuple tuple1, Tuple tuple2) {
    // Critério de cor
    if (tuple1.color > tuple2.color) {
        return true;
    };

    // Critério de ID (em caso de cores iguais)
    if ((tuple1.color == tuple2.color) && (tuple1.id > tuple2.id)) {
        return true;
    }

    return false;
}

// Obtém o índice do nó ancestral
int Heap::_get_ancestral(int position) {
    return (position - 1) / 2;
}

// Obtém o índice do nó sucessor à esquerda
int Heap::_get_left_sucessor(int position) {
    return 2 * position + 1;
}

// Obtém o índice do nó sucessor à direita
int Heap::_get_right_sucessor(int position) {
    return 2 * position + 2;
}

// Verifica se o heap está vazio
bool Heap::empty() {
    return _size == 0;
}

// Insere um elemento no heap e ajusta para manter a propriedade do heap
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

// Remove e retorna o elemento do topo do heap, ajustando para manter a propriedade do heap
Tuple Heap::remove() {
    if (_size < 0) {
        std::cerr << "Heap vazio!" << std::endl;
        exit(1);
    }

    Tuple root = _node[0];
    _node[0] = _node[_size - 1];
    --_size; // O size-1 fica esquecido, mas a alocação é estática
    _heapify_down();
    return root;
}

// Restaura a propriedade do heap movendo um nó para baixo
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

// Restaura a propriedade do heap movendo um nó para cima
void Heap::_heapify_upper() {
    int position = _size - 1;

    while (position != 0 && (criterium(_node[_get_ancestral(position)], _node[position]))) {
        swap(_node[position], _node[_get_ancestral(position)]);
        position = _get_ancestral(position);
    }
}

// Imprime a estrutura do heap (usado para depuração)
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

// Troca os valores de duas Tuples
void Heap::swap(Tuple& tuple1, Tuple& tuple2) {
    Tuple temp = tuple1;
    tuple1 = tuple2;
    tuple2 = temp;
}
