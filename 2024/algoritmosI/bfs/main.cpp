#include <vector>
#include <queue>
#include <stack>
#include <stdio.h>


using namespace std;

// estruturas auxiliares para problema da articulação e clusters
vector<vector<int> > graph;  // vetor de vetores
vector<int> parents;
vector<int> depths;
vector<bool> explored;
queue<int> frontier;
int start;
int n, m; 


// função de leitura do grafo não-direcionado
void read(int m) {    
    for (int i=0; i < m; ++i) {
        // grau do vértice i
        int x, y; 
        scanf(" %d %d", &x, &y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
}

void print(int n) {
    for (int u=0; u < n; ++u) {
        printf("%d: ", u);
        for (int v : graph[u]) {
            printf(" %d", v);
        }
        printf("\n");
    }
}

void init(bool print_flag=false) {
    // lendo o número de vértices do grafo e inicializando o grafo
    scanf(" %d %d", &n, &m);
    graph.resize(n);
    
    // declarando grafo como lista de adjacências: array de vetores
    read(m);
    if (print_flag) {print(n);};

    parents.assign(n, -1);
    explored.assign(n, false);
    depths.assign(n, 0);

}


void bfs(int start) {
    // vértice de início
    frontier.push(start);

    while(!frontier.empty()) {
        int v = frontier.front();
        frontier.pop();
        explored[v] = true;

        // observa-se os vértices adjacentes a v
        for (int u : graph[v]) {
            // caso u não tenha sido explorado
            if (!explored[u]) {
                // v é pai de u
                parents[u] = v;

                frontier.push(u);
                explored[u] = true;
            }
        }
    }
}

void paths(int n) {

    stack<int> path;
    for (int i=0; i < n; ++i) {
        printf("%d: ", i);
        int v = i;
        path.push(v);
        while(parents[v] != -1) {
            v = parents[v];
            path.push(v);
        }
        while(!path.empty()) {
            printf("%d", path.top());
            path.pop();
        }
        printf("\n");
    }
}


int main(void) {
    
    init();

    int start = 2;
    
    bfs(start);
    paths(n);

    return 0;
}