#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <string>
#include "stack.hpp"
#include "queue.hpp"
#include  "utils.hpp"


/**
 * @brief Enumeração que representa os tipos de funções em um nó da árvore.
 */
enum Function {
    AND,
    OR, 
    LEAF
};


/**
 * @brief Estrutura que representa um par de função e subexpressão em uma fórmula.
 */
typedef struct Tuple {
    Function function;      // Tipo de função (AND, OR, ou LEAF).
    std::string sub_string; // Substring de valores.
} Tuple;


/**
 * @brief Estrutura que representa um nó em uma árvore de expressões lógicas.
 */
typedef struct NodeT {
    std::string valuation;  // String de valores (0 ou 1) associada ao nó.
    Function function;     // Tipo de função no nó (AND, OR, ou LEAF).
    bool flag;             // Valor booleano do nó.
    NodeT* left;           // Ponteiro para o nó filho esquerdo.
    NodeT* right;          // Ponteiro para o nó filho direito.

    /**
     * @brief Construtor que inicializa um nó com valores padrão.
     * @param valuation A valoração associada ao nó.
     * @param function O tipo de função no nó.
     * @param flag O sinalizador de controle.
     * @param right O ponteiro para o nó filho direito.
     * @param left O ponteiro para o nó filho esquerdo.
     */
    NodeT(std::string valuation = "", Function function = LEAF, bool flag = false, NodeT* right = nullptr, NodeT* left = nullptr) :
        valuation(valuation), function(function), flag(flag), left(left), right(right) {
    }
} NodeT;


/**
 * @brief Classe que representa uma árvore de expressões lógicas.
 */
class Tree {
public:
    /**
     * @brief Construtor que inicializa uma árvore com a fórmula e valoração fornecidas.
     * @param formula A fórmula lógica a ser representada na árvore.
     * @param valuation A sequência de valorações (0's e 1's) para a fórmula.
     */
    Tree(std::string formula, std::string valuation);

    /**
     * @brief Destrutor da classe Tree.
     */
    ~Tree();

    /**
     * @brief Resolve a árvore de expressões lógicas.
     */
    void solve();

    /**
     * @brief Imprime a árvore em um formato legível.
     * @param node O nó atual (inicialmente, deve ser chamado com o nó raiz).
     * @param depth A profundidade atual da árvore (inicialmente, deve ser chamado com 0).
     * @param prefix Um caractere para representar a conexão com o nó pai.
     */
    void print(NodeT* node, int depth, char prefix = 'o');

    /**
     * @brief Obtém o nó raiz da árvore.
     * @return O nó raiz da árvore.
     */
    NodeT* get_root() {
        return _root;
    }

    /**
     * @brief Obtém a profundidade da árvore.
     * @return A profundidade da árvore.
     */
    int get_depth() {
        return _depth;
    }

private:
    NodeT* _root;       // Nó raiz da árvore.
    int _depth;         // Profundidade da árvore.
    std::string _formula;    // Fórmula lógica associada à árvore.
    std::string _valuation;  // Valoração associada à fórmula.

    /**
     * @brief Constrói a árvore com base na fórmula e valoração fornecidas.
     */
    void _build();

    /**
     * @brief Avalia a expressão em um nó, combinando dois operandos com uma função.
     * @param operand1 O primeiro operando.
     * @param operand2 O segundo operando.
     * @param function O tipo de função a ser aplicada.
     * @return true se a expressão é verdadeira, false caso contrário.
     */
    bool _evaluate(NodeT* operand1, NodeT* operand2, Function function);

    /**
     * @brief Combina as valorações de dois operandos.
     * @param operand1 O primeiro operando.
     * @param operand2 O segundo operando.
     * @return A valoração resultante da combinação.
     */
    std::string _merge(NodeT* operand1, NodeT* operand2);

    /**
     * @brief Realiza uma travessia na árvore e retorna uma pilha de nós.
     * @return Uma pilha de nós na ordem da travessia.
     */
    Stack<NodeT*> _traversal_stack();

    /**
     * @brief Encontra o operador lógico mais à direita em uma valoração.
     * @param valuation A valoração a ser verificada.
     * @param index A posição do operador encontrado (retornado por referência).
     * @return Uma estrutura Tuple contendo o tipo de função e a subexpressão associada.
     */
    Tuple _find_operator(std::string valuation, int& index);
};


#endif