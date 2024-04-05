#include <vector>
#include <stack>
#include <stdio.h>

using namespace std;

// estruturas auxiliares para problema da articulação e clusters
vector<vector<int>> graph; // vetor de vetor para representar o grafo

vector<int> born; // tempos de início zerados
vector<bool> visited; // true: visitado, false: não-visitado
vector<int> low; // mínimo tempo de nascimento alcançavel

vector<int> parents;
vector<vector<int>> components;
stack<int> s;

int time_ = 0;


void read_graph(int n_vertex) {    
    for (int i=0; i < n_vertex; ++i) {
        
        // grau do vértice i
        int degree; scanf(" %d", &degree);
        graph[i].resize(degree);


        // leitura dos vizinhos j do vértice i
        for (int j=0; j<degree; ++j) {
            int neigh; scanf(" %d", &graph[i][j]);
        }
    }
}


void DFS_cut(int u, int parent) {
    
    visited[u] = true; // vértice u descoberto
    born[u] = low[u] = ++time_; // tempo de descoberta de u
    int children = 0; // numero de filhos de u na árvore de precedencia

    // percorre-se todos os vértices adjacentes a u
    for (int v : graph[u]) {
        // vértice adjacente ainda não foi descoberto
        if (!visited[v]) {
            // chama-se DFS_cut para o novo vértice descoberto v, cujo pai é u
            DFS_cut(v, u);

            low[u] = min(low[u], low[v]);

            if (parent != -1 && born[u] <= low[v]) {
                printf("%d ", u); // u é de corte
            }

            ++children;

        } else {
            // há aresta de retorno
            low[u] = min(low[u], born[v]);
        }
    }

    if (parent == -1 && children >= 2) {
        printf("%d ", u); // u é de corte    
    }
}


void DFS_cluster(int u) {
    born[u] = low[u] = ++time_; // tempo de descoberta de u
    s.push(u);

    for (int v : graph[u]) {
        if (born[v] == 0) {
            parents[v] = u; // u é pai de v
            
            DFS_cluster(v);

            low[u] = min(low[u], low[v]);

            if (born[u] <= low[v]) {
                
                vector<int> component;
                int y;

                do {
                    y = s.top();
                    s.pop();
                    component.push_back(y);

                } while (y != v);
                component.push_back(u);
                components.push_back(component);

            }
        } else if (v != parents[u]) {
            low[u] = min(low[u], born[v]);
        }
    }
}


void DFS(int n_vertex) {
    // para cada vértice u
    for (int u=0; u < n_vertex; ++u) {
            // se o vértice adjacente é branco
            if ( !visited[u] ) {
                DFS_cut(u, -1);
            }
        }
    printf("\n");
}


int main(void) {
    
    // lendo o número de vértices do grafo
    int n_vertex; scanf(" %d", &n_vertex);
    
    // Inicializando o vetor graph com tamanho n_vertex
    graph.resize(n_vertex);

    // declarando grafo como lista de adjacências: array de vetores
    read_graph(n_vertex);

    // arrays auxiliares DFS
    born.resize(n_vertex, 0); // tempos de início zerados
    visited.resize(n_vertex, false); // todos os vértices são inicialmente não visitados
    low.resize(n_vertex, 0); // mínimo tempo de nascimento alcançável
    parents.resize(n_vertex, -1);

    // DFS(n_vertex);
    DFS_cluster(0);
    
    printf("_______\n");
    for (const auto& component : components) {
        for (int v : component) {
            printf("%d ", v);
        }
        
        printf("\n");
    }

    return 0;

}


// gerar variáveis globais
// colocar macros de competição