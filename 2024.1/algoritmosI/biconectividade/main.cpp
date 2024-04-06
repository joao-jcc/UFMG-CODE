#include <vector>
#include <stack>
#include <stdio.h>

using namespace std;

// estruturas auxiliares para problema da articulação e clusters

vector<vector<int>> graph;  // vetor de vetores
vector<int> born; // tempo de descobrimento do vértice
vector<int> low; // mínimo tempo de nascimento alcançavel
stack<int> s; // pilha auxiliar ao problema de clusters

// resultados
vector<int> links; // links ed borda
vector<vector<int>> components; // vetor de vetores que representam componentes biconexas

int time_ = 0; // timestamp
int links_count = 0;
int clusters_count = 0;


void output(bool mode, int n) {
    if (mode) {
        std::sort(links.begin(), links.end());
        printf("%d\n", links_count);
        for (int link : links) {
            printf("%d\n", link+1);
        }
    } else {
        for (int i=0; i < clusters_count; ++i) {
            int cluster_size = components[i].size();
            printf("%d %d", n+i+1, cluster_size);
            for (int j=0; j < cluster_size; ++j) {
                printf(" %d", components[i][j] + 1);
            }
        
        printf("\n");
        }
    }
}

// função de leitura do grafo
void read_graph(int m) {    
    for (int i=0; i < m; ++i) {
        // grau do vértice i
        int x, y; scanf(" %d %d", &x, &y);
        graph[x-1].push_back(y-1);
        graph[y-1].push_back(x-1);
    }
}


void DFS_cut(int u, int parent) {
    
    born[u] = low[u] = ++time_; // tempo de descoberta de u
    int children = 0; // numero de filhos de u na árvore de precedencia

    // percorre-se todos os vértices adjacentes a u
    for (int v : graph[u]) {
        // vértice adjacente ainda não foi descoberto
        if (born[v] == 0) {
            // chama-se DFS_cut para o novo vértice descoberto v, cujo pai é u
            DFS_cut(v, u);

            low[u] = min(low[u], low[v]);

            if (parent != -1 && born[u] <= low[v]) {
                links.push_back(u); // u é de corte
                ++links_count;
            }

            ++children;

        } else {
            // há aresta de retorno
            low[u] = min(low[u], born[v]);
        }
    }

    if (parent == -1 && children >= 2) {
        links.push_back(u); // u é de corte
        ++links_count;
    }
}


void DFS_cluster(int u, int parent) {
    born[u] = low[u] = ++time_; // tempo de descoberta de u
    s.push(u);

    for (int v : graph[u]) {
        if (born[v] == 0) {
            
            DFS_cluster(v, u); // u é pai de v

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
                std::sort(component.begin(), component.end());
                components.push_back(component);
                ++clusters_count;

            }
        } else if (v != parent) {
            low[u] = min(low[u], born[v]);
        }
    }
}


void DFS(int n, bool mode) {
    // para cada vértice u
    for (int u=0; u < n; ++u) {
            // se o vértice u ainda não foi descoberto
            if ( born[u] == 0 ) {
                mode ? DFS_cut(u, -1) : DFS_cluster(u, -1);
            }
        }
}


int main(void) {
    
    // lendo o número de vértices do grafo e inicializando o grafo
    int n, m; scanf(" %d %d", &n, &m);

    graph.resize(n);

    // declarando grafo como lista de adjacências: array de vetores
    read_graph(m);

    // arrays auxiliares DFS
    born.resize(n, 0); // tempos de início zerados (indicam que vértices não foram descobertos)
    low.resize(n, 0); // mínimo tempo de nascimento alcançável

    DFS(n, false);
    output(false, n);

    return 0;

}


// gerar variáveis globais  [OK]
// colocar macros de competição