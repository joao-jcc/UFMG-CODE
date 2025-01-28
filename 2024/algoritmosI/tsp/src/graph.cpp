#include "graph.hpp"

Node::Node() {}
Node::Node(size_t v, size_t w) : v(v), w(w) {
}

Graph::Graph() {
}

void Graph::read() {
    std::cin >> N >> M;

    g = std::vector<std::vector<Node>>(N, std::vector<Node>());
    name_to_index = std::map<std::string, size_t>();
    index_to_name = std::vector<std::string>(N);

    size_t index = 0;
    for (size_t edge=0; edge < M; ++edge) {
        std::string city1, city2; size_t weight;
        std::cin >> city1 >> city2 >> weight;
        
        if (name_to_index.find(city1) == name_to_index.end()) {
            name_to_index[city1] = index++;
        }

        if (name_to_index.find(city2) == name_to_index.end()) {
            name_to_index[city2] = index++;
        }

        size_t u = name_to_index[city1];
        size_t v = name_to_index[city2];
        index_to_name[u] = city1; index_to_name[v] = city2;

        g[u].push_back(Node(v, weight));
    }
}


void Graph::read(std::string& path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << path << std::endl;
        exit(1);
    }

    file >> N >> M;

    g = std::vector<std::vector<Node>>(N, std::vector<Node>());
    name_to_index = std::map<std::string, size_t>();
    index_to_name = std::vector<std::string>(N);

    size_t index = 0;
    for (size_t edge = 0; edge < M; ++edge) {
        std::string city1, city2; 
        size_t weight;
        file >> city1 >> city2 >> weight;
        
        if (name_to_index.find(city1) == name_to_index.end()) {
            name_to_index[city1] = index++;
        }

        if (name_to_index.find(city2) == name_to_index.end()) {
            name_to_index[city2] = index++;
        }

        size_t u = name_to_index[city1];
        size_t v = name_to_index[city2];
        index_to_name[u] = city1; 
        index_to_name[v] = city2;

        g[u].push_back(Node(v, weight));
    }

    file.close();
}


void Graph::print() {
    std::cout << N << ", " << M << std::endl;

    for (size_t u=0; u < N; ++u) {
        for (Node neigh : g[u]) {
            std::cout << index_to_name[u];
            std::cout << ", " << index_to_name[neigh.v]; 
            std::cout << ", " << neigh.w << std::endl;
        }
    }
}