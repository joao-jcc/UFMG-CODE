//
// Created by João Costa on 28/10/23.
//

#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <cassert>

// Classe ExceptionEmptyList: Uma classe de exceção para representar situações em que
// uma operação não pode ser realizada em uma lista vazia.
class ExceptionEmptyList : public std::exception {
public:
    // Construtor da classe ExceptionEmptyList.
    // Parâmetros:
    // - message: Uma mensagem descritiva associada à exceção.
    ExceptionEmptyList(const char* message) : _message(message) {}

    // Função what: Sobrescrita da função what() da classe base std::exception.
    // Retorna a mensagem associada à exceção.
    const char* what() const throw() override {
        return _message;
    }

private:
    const char* _message;  // Mensagem associada à exceção.
};



// Estrutura de Nó Genérico para LinkedList
template<typename T>
struct Node {
    T data;          // Dados armazenados no nó
    Node<T>* next;   // Ponteiro para o próximo nó na lista
};

// Classe LinkedList Genérica
template <typename T>
class LinkedList {
public:
    // Construtor padrão
    LinkedList() : _first(nullptr), _last(nullptr), _size(0) {}

    // Destrutor
    ~LinkedList() {
        Node<T>* temp = _first;
        while (temp != nullptr) {
            _first = _first->next;
            delete temp;
            temp = _first;
            --_size;
        }

        _first = _last = nullptr;
        assert(_size == 0);
    }

    // Verifica se a lista está vazia
    bool empty() const {
        return _size == 0;
    }

    // Verifica se a lista contém um determinado dado
    bool contains(const T& data) const {
        Node<T>* temp = _first;
        while (temp != nullptr) {
            if (temp->data == data) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    // Adiciona um elemento no final da lista
    void append(T data) {
        Node<T>* node = new Node<T>{data, nullptr};

        if (empty()) {
            _first = _last = node;
        } else {
            _last->next = node;
            _last = node;
        }

        ++_size;
    }

    // Remove e retorna o primeiro elemento da lista
    T pop_front() {
        if (empty()) {
            throw ExceptionEmptyList("LinkedList is empty!");
        }

        T data = _first->data;

        Node<T>* del_node = _first;
        _first = _first->next;

        delete del_node;
        --_size;

        return data;
    }

    // Obtém o elemento em uma posição específica na lista
    T get_item(int index) const {
        Node<T>* temp = _first;

        for (int i = 1; i < index; ++i) {
            temp = temp->next;
        }

        return temp->data;
    }

    // Obtém o tamanho da lista
    unsigned get_size() const {
        return _size;
    }

    // Obtém o ponteiro para o primeiro nó da lista
    Node<T>* get_first() const {
        return _first;
    }

protected:
    Node<T>* _first;   // Ponteiro para o primeiro nó
    Node<T>* _last;    // Ponteiro para o último nó
    unsigned _size;    // Tamanho da lista
};



// Classe Vertex que representa um vértice em um grafo
template <typename T>
class Vertex : public LinkedList<T> {
    static int _count;  // Contador estático para atribuir identificadores únicos aos vértices
public:
    // Construtor padrão
    Vertex() : LinkedList<T>(), _id(_count), _color(0), _status(false) {
        ++_count;  // Incrementa o contador estático para atribuir um novo identificador único
    }

    // Destrutor
    ~Vertex() {}

    // Obtém o identificador único do vértice
    unsigned get_id() const {
        return _id;
    }

    // Obtém a cor do vértice
    unsigned get_color() const {
        return _color;
    }

    // Obtém o status de validação do vértice
    bool get_status() const {
        return _status;
    }

    // Define a cor do vértice
    void set_color(unsigned color) {
        _color = color;
    }

    // Obtém o número total de vértices criados
    static int get_count() {
        return _count;
    }

    // Valida o vértice em relação às cores dos vértices adjacentes no grafo
    bool validate(Vertex<int>**& graph) {
        for (unsigned target_color = 1; target_color < _color; ++target_color) {
            bool color_found = false;
            Node<T>* temp = this->_first;

            // Itera sobre os vértices adjacentes e verifica se algum tem a cor alvo
            for (unsigned j = 0; j < this->_size; ++j) {
                if (graph[temp->data]->get_color() == target_color) {
                    color_found = true;
                    break;
                }
                temp = temp->next;
            }

            // Se a cor alvo não for encontrada entre os vértices adjacentes, o vértice é inválido
            if (!color_found) {
                _status = false;
                return false;
            }
        }

        // Se todas as cores anteriores estiverem presentes nos vértices adjacentes, o vértice é válido
        _status = true;
        return true;
    }

private:
    unsigned _id;     // Identificador único do vértice
    unsigned _color;  // Cor do vértice
    bool _status;     // Status de validação do vértice
};

// Inicialização do contador estático
template<typename T>
inline int Vertex<T>::_count = 0;


#endif
