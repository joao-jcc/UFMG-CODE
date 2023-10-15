#include "tree.hpp"

Tree::Tree(std::string formula, std::string valuation) : _root(nullptr), _formula(formula), _valuation(valuation) {
    _depth = count_char(valuation, 'a') + count_char(valuation, 'e') + 1;
    _build();
}

Tree::~Tree() {
    // Libera a memória alocada para os nós da árvore
    Stack<NodeT*> stack = _traversal_stack();
    while (!stack.empty()) {
       NodeT* node = stack.peek();
       stack.pop();
       delete node;
    }
}

Tuple Tree::_find_operator(std::string str, int& index) {
    // Encontra o operador lógico na string de valoração
    int start = index;
    int len = str.length();
    for (; index < len; ++index) {
        if (str[index] == 'a') {
            return Tuple{AND, str.substr(start, index - start)};
        } else if (str[index] == 'e') {
            return Tuple{OR, str.substr(start, index - start)};
        }
    }

    return Tuple{LEAF, str.substr(start, index - start)};
}

std::string Tree::_merge(NodeT* operand1, NodeT* operand2) {
    // Combinar as valorações de dois operandos
    std::string result;
    std::string str1 = operand1->valuation;
    std::string str2 = operand2->valuation;

    if (operand1->flag && operand2->flag) {
        int len = str1.length();
        for (int i = 0; i < len; ++i) {
            if (str1[i] == str2[i]) {
                result += str1[i];
            } else {
                result += "a";
            }
        }
    } else if (!operand1->flag) {
        result = operand2->valuation;
    } else {
        result = operand1->valuation;
    }

    return result;
}

void Tree::_build() {
    // Constrói a árvore de expressões lógicas
    if (_depth == 1) {
        _root = new NodeT(_valuation);
        _root->flag = evaluate_expression(_formula, _root->valuation);
        return;
    }

    int index = 0;
    Tuple tuple = _find_operator(_valuation, index);
    ++index;

    _root = new NodeT(tuple.sub_string, tuple.function);
    Queue<NodeT*> queue;
    queue.add(_root);

    while (tuple.function != LEAF) {
        tuple = _find_operator(_valuation, index);
        ++index;

        int size = queue.get_size();
        for (int i = 0; i < size; ++i) {
            NodeT* current = queue.peek();
            queue.pop();

            current->left = new NodeT(current->valuation + "1" + tuple.sub_string, tuple.function, false);
            current->right = new NodeT(current->valuation + "0" + tuple.sub_string, tuple.function, false);

            if (tuple.function == LEAF) {
                current->right->flag = evaluate_expression(_formula, current->right->valuation);
                current->left->flag = evaluate_expression(_formula, current->left->valuation);
            }

            queue.add(current->left);
            queue.add(current->right);
        }
    }
}

Stack<NodeT*> Tree::_traversal_stack() {
    // Realiza uma travessia pós-ordem na árvore
    Stack<NodeT*> node_stack;
    Stack<NodeT*> traversal_stack;
    NodeT* current = _root;

    while (current || !node_stack.empty()) {
        if (current) {
            node_stack.add(current);
            traversal_stack.add(current);
            current = current->right;
        } else {
            NodeT* top_node = node_stack.peek();
            node_stack.pop();
            current = top_node->left;
        }
    }

    return traversal_stack;
}

void Tree::solve() {
    // Resolve a árvore de expressões lógicas
    NodeT* current = _root;
    if (current) {
        Stack<NodeT*> stack_evaluation;
        Stack<NodeT*> post_stack = _traversal_stack();

        while (!post_stack.empty()) {
            NodeT* current = post_stack.peek();
            post_stack.pop();

            if (current->function == LEAF) {
                stack_evaluation.add(current);
            } else {
                NodeT* operand2 = stack_evaluation.peek();
                stack_evaluation.pop();
                NodeT* operand1 = stack_evaluation.peek();
                stack_evaluation.pop();

                bool result = _evaluate(operand1, operand2, current->function);
                std::string result_str = result ? _merge(operand1, operand2) : "";

                operand1->flag = result;
                operand1->valuation = result_str;

                stack_evaluation.add(operand1);
            }
        }

        current = stack_evaluation.peek();
        stack_evaluation.pop();

        if (current->flag) {
            std::cout << current->flag << " "  << current->valuation << std::endl;
        } else {
            std::cout << current->flag << std::endl;
        }
    }
}

bool Tree::_evaluate(NodeT* operand1, NodeT* operand2, Function function) {
    // Avalia uma expressão em um nó
    if (function == AND) {
        return operand1->flag && operand2->flag;
    } else if (function == OR) {
        return operand1->flag || operand2->flag;
    } else {
        std::cerr << "Node não é um operador" << std::endl;
        exit(2);
    }
}

void Tree::print(NodeT* node, int depth, char prefix) {
    // Imprime a árvore em um formato legível
    if (node == nullptr) {
        return;
    }

    std::cout << "  ";
    for (int i = 0; i < depth; i++) {
        std::cout << (i == depth - 1 ? "+" : "    ");
    }

    std::string function;
    switch(node->function) {
        case 0:
            function = "AND";
            break;
        case 1:
            function = "OR";
            break;
        case 2:
            function = "LEAF";
            break;
    }
    std::cout << prefix << "--" << node->valuation << "(" << function << ")" << std::endl;

    print(node->left, depth + 1, 'L');
    print(node->right, depth + 1, 'R');
}
