#include "tree.hpp"

Tree::Tree(std::string base_formula) : _root(nullptr), _base_formula(base_formula) {
    _depth = count_char(base_formula, 'a') + count_char(base_formula, 'e') + 1;
    _build();
}

Tree::~Tree() {

}

void Tree::_build() {
    if (_depth == 1) {
        _root = new NodeT(_base_formula);
        return; // The tree with depth 1 has only one node
    }

    // initialize root
    Tuple tuple = find_operator(_base_formula, 0);
    _root = new NodeT(tuple.sub_string, tuple.function);

    // expansão
    for (int i=1; i < _depth; ++i) {
        tuple = find_operator(_base_formula, tuple.index + 1);
        _expand(tuple, LEFT);

        if (i == 1) {
            continue;
        }
        _expand(tuple, RIGHT);
    }
}

void Tree::_expand(Tuple tuple, Direction direction) {
    NodeT* temp = _root;
    while (true) {
            temp = _walk_to(temp, direction);

            // achei a folha: crio dois filhos
            temp->left = new NodeT(temp->formula + "1" + tuple.sub_string, tuple.function, temp);
            temp->right = new NodeT(temp->formula + "0" + tuple.sub_string, tuple.function, temp);
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

        while (!traversal_stack.empty()) {
            traversal_stack.pop()->print();
        }

        return traversal_stack;
    }


void Tree::solve() {
    traver
}