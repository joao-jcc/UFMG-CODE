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
int goal;


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
    int n, m; 
    scanf(" %d %d", &n, &m);
    graph.resize(n);
    
    // declarando grafo como lista de adjacências: array de vetores
    read(m);
    if (print_flag) {print(n);};

    parents.assign(n, -1);
    explored.assign(n, false);
    depths.assign(n, 0);

}


bool bfs(int start, int goal) {
    // vértice de início
    frontier.push(start);

    while(!frontier.empty()) {
        int v = frontier.front();
        frontier.pop();

        // observa-se os vértices adjacentes a v
        for (int u : graph[v]) {
            // caso u não tenha sido explorado
            if (!explored[u]) {
                // v é pai de u
                parents[u] = v;
                
                // caso u seja o vértice objetivo
                if (u == goal) {
                    return true; // há solução
                }

                // caso não sej adicione u à fronteira
                frontier.push(u);
            }
        }
        // v foi explorado
        explored[v] = true;
    }

    return false; // não há solução
}

void print_solution(int goal) {
    int v = goal;
    stack<int> solution;
    solution.push(v);
    while(parents[v] != -1) {
        v = parents[v];
        solution.push(v);
    }

    while(!solution.empty()) {
        printf("%d", solution.top());
        solution.pop();
    }
    printf("\n");
}


int main(void) {
    
    init();

    int start = 2;
    int goal = 1;

    
    if (bfs(start, goal)) {
        printf("Solved!\n");
        print_solution(goal);
    }


    return 0;
}