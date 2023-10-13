#include "tree.hpp"

Tree::Tree(std::string formula, std::string valuation) : _root(nullptr), _formula(formula), _valuation(valuation) {
    _depth = count_char(valuation, 'a') + count_char(valuation, 'e') + 1;
    _build();
}

Tree::~Tree() {
    Stack<NodeT*> stack;
    while(!stack.empty()) {
       NodeT* node = stack.pop();
       delete node;
    }
    delete _root;
}


Tuple Tree::_find_operator(std::string str, int& index) {
    int start = index;
    int len = str.length(); 
    for (; index < len; ++index) {
        if (str[index] == 'a') {
            return Tuple{AND, str.substr(start, index - start)};
        }
        else if (str[index] == 'e') {
            return Tuple{OR, str.substr(start, index - start)};
        }
    }

    return Tuple{LEAF, str.substr(start, index - start)};
}

std::string Tree::_merge(std::string str1, std::string str2) {
    std::string result;
    int len = str1.length();
    for (int i=0; i < len; ++i) {
        if (str1[i] == str2[i]) {
            result += str1[i];
            continue;
        }
        result += "a";
    }

    return result;
}

void Tree::_build() {    
    if (_depth == 1) {
        // node craido com Leaf
        _root = new NodeT(_valuation);
        _root->flag = evaluate_expression(_formula, _root->valuation);
        return; // The tree with depth 1 has only one node
    }

    int index = 0;
    // initialize root
    Tuple tuple = _find_operator(_valuation, index);
    ++index;
    
    _root = new NodeT(tuple.sub_string, tuple.function);
    Queue<NodeT*> queue;
    queue.add(_root);

    while (tuple.function != LEAF) {
        tuple = _find_operator(_valuation, index);
        ++index;

        int size = queue.get_size();
        for (int i=0; i < size; ++i) {
            NodeT* current = queue.peek();
            queue.pop();

            // CREATE CHILD
            current->left = new NodeT(current->valuation + "1" + tuple.sub_string, tuple.function, false, current);
            current->right = new NodeT(current->valuation + "0" + tuple.sub_string, tuple.function, false, current);

            if (tuple.function == LEAF) {
                current->right->flag = evaluate_expression(_formula, current->right->valuation);
                          
                current->left->flag = evaluate_expression(_formula, current->left->valuation);
            }


            queue.add(current->left);
            queue.add(current->right);  // add right child first

        }
    }

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


 void Tree::_update_nodes(NodeT* n1, NodeT* n2, NodeT* n3, bool value) {
        if (n1->flag && n2->flag && value) {
            n1->valuation = _merge(n1->valuation, n2->valuation);   
        } else if (value) {
            n1->valuation = n1->flag ? n1->valuation : n2->valuation;
        } else {
            n1->valuation = "";
        }

        n1->flag = value;
 }

void Tree::solve() {
    Stack<NodeT*> stack = _traversal_stack();

    bool flag = true;
    while(stack.get_size() > 1) {
        NodeT* n1 = stack.pop();
        NodeT* n2 = stack.pop();
        NodeT* n3 = stack.pop();

        if (flag) {
            bool value = n3->function == AND ? n1->flag & n2->flag : n1->flag | n2->flag;

           _update_nodes(n1, n2, n3, value);
            stack.add(n1);
        } else {
            NodeT* n4 = stack.pop();
            bool value = n4->function == AND ? n2->flag & n3->flag : n2->flag | n3->flag;
            _update_nodes(n2, n3, n4, value);
            stack.add(n2);
            stack.add(n1);
        }

        flag = !flag;
    }

    NodeT* node = stack.pop();
    std::cout << node->flag << " " << node->valuation << std::endl;
}

void Tree::print(NodeT* node, int depth, char prefix) {
    if (node == nullptr) {
        return;
    }

    // Print the current node
    std::cout << "  ";
    for (int i = 0; i < depth; i++) {
        std::cout << (i == depth - 1 ? "+" : "    ");
    }
    std::cout << prefix << "--" << node->valuation << std::endl;

    // Print the left subtree
    print(node->left, depth + 1, 'L');

    // Print the right subtree
    print(node->right, depth + 1, 'R');
}
