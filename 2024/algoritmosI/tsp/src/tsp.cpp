#include "tsp.hpp"

TSP::TSP() : 
    graph(nullptr), 
    best_path(std::vector<size_t>()), 
    best_cost(UNDEFINED),
    initialized(false) {}

void TSP::set(Graph& graph) { 
    this->graph = &graph; 
    initialized=true; 
    best_cost = UNDEFINED;
    best_path.clear();
}

void TSP::print_solution() {
    std::cout << best_cost << std::endl;
    for (size_t i=0; i < best_path.size(); ++i) {
        if (i != best_path.size()-1) {
            std::cout << graph->index_to_name[best_path[i]] << " ";
        } else {
            std::cout << graph->index_to_name[best_path[i]] << std::endl;
        }
    }
}


void TSP::solve() {
    if (!initialized) {
        std::cerr << "ERRO: TSP não inicializado!" << std::endl;
        exit(1);
    }
    std::cout << "method: " << graph->method << std::endl;
    switch(graph->method) {
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

    for (Node node : graph->g[root]) {
        if (node.v == end && index == graph->N - 1) {

            if (best_cost > cost + node.w) {
                best_cost = cost + node.w; best_path = path;
            }

            path[root] = UNDEFINED; return;
        }

        // branch and bound
        if (path[node.v] != UNDEFINED) {continue;}

        _brute_force_aux(node.v, cost + node.w, path, index + 1, end);
    }

    path[root] = UNDEFINED;
}


void TSP::_brute_force() {
    std::vector<size_t> path(graph->N, UNDEFINED);
    for (size_t root = 0; root < graph->N; ++root) {
        _brute_force_aux(root, 0, path, 0, root);
    }
}


void TSP::_greedy() {
    size_t current_vertice = 0; // Começa no vértice inicial
    best_path.clear();
    best_path.push_back(current_vertice);
    size_t best_cost = 0;

    std::vector<bool> visited(graph->N, false); 
    visited[current_vertice] = true;

    for (size_t i = 1; i < graph->N; ++i) {
        size_t min_distance = std::numeric_limits<size_t>::max();
        size_t min_vertice = UNDEFINED;

        // Procura o próximo nó com menor distância
        for (const Node& node : graph->g[current_vertice]) {
            if (!visited[node.v] && node.w < min_distance) {
                min_distance = node.w;
                min_vertice = node.v;
            }
        }

        // Atualiza os custos e caminho
        if (min_vertice != UNDEFINED) {
            best_cost += min_distance;
            best_path.push_back(min_vertice);
            visited[min_vertice] = true;
            current_vertice = min_vertice;
        }
    }

 
    for (const Node& node : graph->g[current_vertice]) {
        if (node.v == 0) {
            best_cost += node.w;
            break;
        }
    }

    this->best_cost = best_cost;

}


void TSP::_dynamic() {
    size_t n = graph->N;
    std::vector<std::vector<size_t>> dp(1 << n, std::vector<size_t>(n, MAX_SIZET));
    std::vector<std::vector<size_t>> parent(1 << n, std::vector<size_t>(n, UNDEFINED));

    // Inicializa o custo para visitar o primeiro nó a partir do nó 0
    dp[1][0] = 0;

    // Itera sobre todos os subconjuntos de nós
    for (size_t mask = 1; mask < (1 << n); ++mask) {
        for (size_t u = 0; u < n; ++u) {
            if (dp[mask][u] == MAX_SIZET) continue;

            // Tenta visitar todos os nós não visitados
            for (const Node& node : graph->g[u]) {
                size_t v = node.v;
                if (!(mask & (1 << v))) {
                    size_t new_mask = mask | (1 << v);
                    if (dp[new_mask][v] > dp[mask][u] + node.w) {
                        dp[new_mask][v] = dp[mask][u] + node.w;
                        parent[new_mask][v] = u;
                    }
                }
            }
        }
    }

    size_t final_mask = (1 << n) - 1;
    size_t min_cost = MAX_SIZET;
    size_t last_node = UNDEFINED;

    for (size_t u = 1; u < n; ++u) {
        if (dp[final_mask][u] != MAX_SIZET && graph->g[u][0].w != MAX_SIZET) {
            size_t total_cost = dp[final_mask][u] + graph->g[u][0].w;
            if (total_cost < min_cost) {
                min_cost = total_cost;
                last_node = u;
            }
        }
    }

    // Reconstruir o caminho
    if (last_node != UNDEFINED) {
        best_cost = min_cost;
        best_path.clear();

        size_t current_node = last_node;
        size_t current_mask = final_mask;

        while (current_node != UNDEFINED) {
            best_path.push_back(current_node);
            size_t prev_node = parent[current_mask][current_node];
            current_mask ^= (1 << current_node);
            current_node = prev_node;
        }

        for (size_t i = 0; i < n / 2; ++i) {
            size_t temp = best_path[i];
            best_path[i] = best_path[n - i - 1];
            best_path[n - i - 1] = temp;
}
        
    } else {
        best_cost = UNDEFINED;
        best_path.clear();
    }
}