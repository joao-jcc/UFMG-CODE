#include "tree.hpp"

Tree::Tree(std::string formula, std::string valuation) : _root(nullptr), _formula(formula), _valuation(valuation) {
    _depth = count_char(valuation, 'a') + count_char(valuation, 'e') + 1;
    _build();
}

Tree::~Tree() {

}


inline Tuple Tree::_find_operator(std::string str, int& index) {
    int start_index = index;
    for (; index < str.length(); ++index) {
        if (str[index] == 'a') {
            return Tuple{AND, str.substr(start_index, index - start_index), index};
        }
        else if (str[index] == 'e') {
            return Tuple{OR, str.substr(start_index, index - start_index), index};
        }
    }

    return Tuple{LEAF, str.substr(start_index, index - start_index), index};
}


void Tree::_build() {
    if (_depth == 1) {
        _root = new NodeT(_valuation);
        _root->flag = evaluate_expression(_formula, _root->valuation);
        return; // The tree with depth 1 has only one node
    }

    //
    // initialize root
    Tuple tuple = find_operator(_valuation, 0);
    _root = new NodeT(tuple.sub_string, tuple.function);

    // expansão
    for (int i=1; i < _depth; ++i) {
        tuple = find_operator(_valuation, tuple.index + 1);
        _expand(tuple, LEFT, i);

        if (i == 1) {
            continue;
        }
        _expand(tuple, RIGHT, i);
    }
}

void Tree::_expand(Tuple tuple, Direction direction, int depth) {
    NodeT* temp = _root;
    while (true) {
            temp = _walk_to(temp, direction);

            // achei a folha: crio dois filhos
            temp->left = new NodeT(temp->valuation + "1" + tuple.sub_string, tuple.function, temp);
            temp->right = new NodeT(temp->valuation + "0" + tuple.sub_string, tuple.function, temp);

            if (depth == _depth - 1) {
                temp->right->flag = evaluate_expression(_formula, temp->right->valuation);
                temp->left->flag = evaluate_expression(_formula, temp->left->valuation);
            }

            // set flag to true
            temp->flag = true;

            // ascensão
            while(temp->flag == true) {
                temp = temp->parent;

                // preenchi todo um braço
                if (temp == nullptr) {
                    return;
                }

            }
            // set flag to true
            temp->flag = true;

            // modifico a direcao de caminhamento
            direction = direction == LEFT ? RIGHT : LEFT;

     }
}


NodeT* Tree::_walk_to(NodeT* temp, Direction direction) {
    if (direction == LEFT) {
        // caminho para a esquerda
        while(temp->left != nullptr) {
            temp = temp->left;
            temp->flag = false;
        }
    }

    else if (direction == RIGHT) {
        // caminho para a direita
        while(temp->right != nullptr) {
            temp = temp->right;
            temp->flag = false;
        }

    }

    return temp;
}

// são nodes
Stack<NodeT*> Tree::_traversal_stack() {
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
    Stack<NodeT*> stack = _traversal_stack();
    std::string string_result;

    bool flag = true;
    while(stack.get_size() > 1) {
        NodeT* n1 = stack.pop();
        NodeT* n2 = stack.pop();
        NodeT* n3 = stack.pop();

        if (flag) {
            bool value = n3->function == AND ? n1->flag & n2->flag : n1->flag | n2->flag;
            n1->flag = value;
            stack.add(n1);
        } else {
            NodeT* n4 = stack.pop();
            bool value = n4->function == AND ? n2->flag & n3->flag : n2->flag | n3->flag;
            n2->flag = value;
            stack.add(n2);
            stack.add(n1);
        }
    }

    std::cout << stack.pop()->flag << std::endl;
}