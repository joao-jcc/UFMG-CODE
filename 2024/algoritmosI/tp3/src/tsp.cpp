#include "tsp.hpp"

// Funções auxiliares para manipulação de conjuntos bitwise
static size_t full_set(size_t n) {
    return (1 << n) - 1; // Cria um conjunto contendo todos os elementos
}

static size_t del_set(size_t sbin, size_t element) {
    return ~(1 << element) & sbin; // Remove um elemento do conjunto
}

static size_t init_set(size_t n, size_t element) {
    return del_set(full_set(n), element); // Inicializa um conjunto sem um elemento específico
}

static bool find_set(size_t set, size_t element) {
    return (((size_t)1 << element) & set) == ((size_t)1 << element); // Verifica se um elemento pertence ao conjunto
}


TSP::TSP(Graph graph) :
    graph(graph), 
    best_path(std::vector<size_t>(graph.N, UNDEFINED)), 
    best_cost(UNDEFINED) {}


void TSP::print_solution() {
    std::cout << best_cost << std::endl;
    for (size_t i = 0; i < best_path.size(); ++i) {
        if (i != best_path.size() - 1) {
            std::cout << graph.index_to_name[best_path[i]] << " ";
        } else {
            std::cout << graph.index_to_name[best_path[i]] << std::endl;
        }
    }
}


// Seleciona e executa o método para resolver o TSP
void TSP::solve() {
    best_path.clear();
    best_cost = MAX_SIZET;

    switch (graph.method) {
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


// Algoritmo de força bruta (recursivo)
void TSP::_brute_force_aux(size_t root, size_t cost, std::vector<size_t>& path, size_t index, size_t end) {
    path[root] = index;

    // Se chegou ao último vértice do caminho
    if (index == graph.N - 1) {
        size_t w = graph.matrix[root][end];
        if (best_cost > cost + w) { 
            best_cost = cost + w; 
            best_path = path;
        }
    } else {
        for (size_t v = 0; v < graph.N; ++v) {
            if (path[v] != UNDEFINED) continue; // Se o vértice já foi explorado, ignora
            _brute_force_aux(v, cost + graph.matrix[root][v], path, index + 1, end);
        }
    }

    path[root] = UNDEFINED; // Restaura o estado para backtracking
}


// Executa o algoritmo de força bruta para todas as raízes possíveis
void TSP::_brute_force() {
    std::vector<size_t> path(graph.N, UNDEFINED);
    for (size_t root = 0; root < graph.N; ++root) {
        _brute_force_aux(root, 0, path, 0, root);
    }
}


void TSP::_greedy() {
    // Define a cidade inicial como 0
    size_t current_city = 0;
    
    // Cria um conjunto com todas as cidades, exceto a cidade inicial
    size_t sbin = init_set(graph.N, current_city);
    
    std::vector<size_t> path;
    size_t cost = 0;

    path.push_back(current_city);

    // Enquanto ainda houver cidades não visitadas
    while (sbin != 0) {
        size_t min_v = UNDEFINED;  // Armazena a próxima cidade com menor custo
        size_t min_w = MAX_SIZET;  // Armazena o menor custo encontrado

        // Percorre todas as cidades para encontrar a mais próxima ainda não visitada
        for (size_t v = 0; v < graph.N; ++v) {
            if (v == current_city || !find_set(sbin, v)) continue; // Ignora a cidade atual ou já visitada
            
            size_t w = graph.matrix[current_city][v]; // Custo para ir até a cidade v

            // Atualiza a cidade mais próxima se encontrar um custo menor
            if (min_w > w) {
                min_w = w;
                min_v = v;
            }
        }
        
        cost += min_w;
        path.push_back(min_v);
        current_city = min_v;
        
        // Remove a cidade visitada do conjunto de cidades não visitadas
        sbin = del_set(sbin, min_v);
    }

    // Retorna à cidade inicial para completar o ciclo
    cost += graph.matrix[current_city][0];

    best_cost = cost;
    best_path = path;
}


void TSP::_dynamic() {
    // Itera sobre todas as possíveis cidades de partida (raízes)
    for (size_t root = 0; root < graph.N; ++root) {
        
        // Cria a matriz de memoização
        std::vector<std::vector<State>> mem(graph.N, std::vector<State>(1 << graph.N, {UNDEFINED, UNDEFINED, UNDEFINED}));

        // Inicializa o conjunto de cidades ainda não visitadas, excluindo a raiz
        size_t initial_sbin = init_set(graph.N, root);
        
        // Chama a função auxiliar recursiva para calcular a melhor solução a partir da raiz
        State result = _dynamic_aux(root, initial_sbin, root, mem);

        // Se o custo encontrado for menor que o melhor custo atual, atualiza a solução ótima
        if (result.cost < best_cost) {
            best_cost = result.cost;
            best_path.clear();
            
            // Reconstrói o caminho percorrido a partir da matriz de memoização
            size_t sbin = initial_sbin, v = root;
            while (sbin != UNDEFINED) {
                best_path.push_back(v); 
                State state = mem[v][sbin]; 
                v = state.next_root; 
                sbin = state.next_sbin;
            }
        }
    }
}

// Função auxiliar recursiva para a solução dinâmica do TSP
State TSP::_dynamic_aux(size_t root, size_t sbin, size_t end, std::vector<std::vector<State>>& mem) {
    if (sbin == 0) { // Caso base: todos os vértices foram visitados
        return mem[root][sbin] = {graph.matrix[root][end], UNDEFINED, UNDEFINED};
    }

    if (mem[root][sbin].cost != UNDEFINED) { // Verifica se o estado já foi computado
        return mem[root][sbin];
    }

    State state = {MAX_SIZET, UNDEFINED, UNDEFINED}; // Inicializa com valores máximos

    // Explora os vértices ainda não visitados
    for (size_t v = 0; v < graph.N; ++v) {
        if (graph.matrix[root][v] == UNDEFINED || !find_set(sbin, v)) continue;

        size_t new_sbin = del_set(sbin, v);
        State subproblem = _dynamic_aux(v, new_sbin, end, mem);
        size_t cost = graph.matrix[root][v] + subproblem.cost;

        if (cost < state.cost) { // Atualiza o melhor estado
            state.cost = cost;
            state.next_root = v;
            state.next_sbin = new_sbin;
        }
    }

    return mem[root][sbin] = state; // Armazena o resultado na tabela de memoização
}