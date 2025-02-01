#include "tsp.hpp"

// funções para gerenciar conjuntos bit-wise
static size_t full_set (size_t n) {
    return (1 << n) - 1;
}

static size_t del_set (size_t sbin, size_t element) {
    return ~(1 << element) & sbin;
}

static size_t init_set (size_t n, size_t element) {
    return del_set(full_set(n), element);
}

static bool find_set (size_t set, size_t element) {
    return ((1 << element) & set) == (1 << element);
}



// TSP

TSP::TSP(Graph graph) :
    graph(graph), 
    best_path(std::vector<size_t>(graph.N, UNDEFINED)), 
    best_cost(UNDEFINED),
    count_solutions(0) {}


void TSP::print_solution() {
    std::cout << best_cost << std::endl;
    for (size_t i=0; i < best_path.size(); ++i) {
        if (i != best_path.size()-1) {
           
            std::cout << graph.index_to_name[best_path[i]] << " ";
        } else {
            std::cout << graph.index_to_name[best_path[i]] << std::endl;
        }
    }
}


void TSP::solve() {

    switch(graph.method) {
        case 'b':
            _brute_force();
            break;
        
        case 'g':
            _greedy();
            break;
        
        case 'd':
            _dynamic();
            break;
        
        default:
            _brute_force();
            break;
    }

}


void TSP::_brute_force_aux(size_t root, 
                           size_t cost, 
                           std::vector<size_t>& path,
                           size_t index,
                           size_t end) {
    path[root] = index;

    // último vértice do caminho
    if (index == graph.N-1) {
        size_t w = graph.matrix[root][end];
        if (best_cost > cost + w) { best_cost = cost + w; best_path = path;}
    }

    else {

        for (size_t v=0; v < graph.N; ++v) {
                // vértice já explorado
                if (path[v] != UNDEFINED) {continue;}
        
                _brute_force_aux(v, cost +  graph.matrix[root][v], path, index + 1, end);
            }

    }
   
    path[root] = UNDEFINED;
}


void TSP::_brute_force() {
    
    std::vector<size_t> path(graph.N, UNDEFINED);
    for (size_t root=0; root < graph.N; ++root) {
        _brute_force_aux(root, 0, path, 0,  root);
    }

}


void TSP::_greedy() {

}

void TSP::_dynamic() {

    // Itera sobre todas as raízes possíveis
    for (size_t root = 0; root < graph.N; ++root) {
        // Inicializa a matriz de memoização
        std::vector<std::vector<State>> mem(graph.N, std::vector<State>(1 << graph.N, {UNDEFINED, UNDEFINED, UNDEFINED}));

        size_t initial_sbin = init_set(graph.N, root);
        State result = _dynamic_aux(root, initial_sbin, root, mem);

        // Atualiza o melhor custo
        if (result.cost < best_cost) {
            best_cost = result.cost;
            // Reconstroi o caminho final
            best_path.clear();
            size_t sbin = initial_sbin; size_t v = root;
            while (sbin != UNDEFINED) {
                best_path.push_back(v); // Adiciona o vértice atual ao caminho
                State state = mem[v][sbin];
                v = state.next_root;
                sbin = state.next_sbin; 
            }
        }
    }
}


State TSP::_dynamic_aux(size_t root, size_t sbin, size_t end,
                        std::vector<std::vector<State>>& mem) {
    // Caso base: todos os vértices foram visitados
    if (sbin == 0) {
        return mem[root][sbin] = {graph.matrix[root][end], UNDEFINED, UNDEFINED}; // Estado folha
    }

    // Verifica se o estado já foi computado
    if (mem[root][sbin].cost != UNDEFINED) {
        return mem[root][sbin];
    }

    // Inicializa o estado atual com custo infinito e filho indefindo
    State state = {MAX_SIZET, UNDEFINED, UNDEFINED};

    // Explora todos os vértices não visitados
    for (size_t v = 0; v < graph.N; ++v) {
        if (graph.matrix[root][v] == UNDEFINED || !find_set(sbin, v)) {
            continue; // Ignora vértices inalcançáveis ou já visitados
        }

        size_t new_sbin = del_set(sbin, v); // Remove v do conjunto de vértices não visitados
        State subproblem = _dynamic_aux(v, new_sbin, end, mem);
        size_t cost = graph.matrix[root][v] + subproblem.cost;

        // Atualiza o estado atual se encontrarmos um custo menor
        if (cost < state.cost) {
            state.cost = cost;
            state.next_root = v;
            state.next_sbin = new_sbin;
        }
    }

    // Armazena o estado na matriz de memoização
    return mem[root][sbin] = state;
}