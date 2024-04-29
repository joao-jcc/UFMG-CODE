#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;
// par de interiros que representam arestas com pesos (.first: vertice y, .second: weight)
// ou vértice e sua distância da origem (.fisrt: distance, .second: vertice label)
typedef pair<int, int> node;

/*
N: número de vértices no grafo
M: número de conexões no grafo
J: número de monstros
T: número máximo de turnos a serem jogados
K: número de recursos do turno
*/
int N, M, J, T, K; 

vector<vector<node> > graph;  // grafo/mapa do jogo
vector<vector<int> > graph_t; // grafo transposto sem pesos para bfs


vector<bool> monsters; // posição inicial dos monstros: 0, 1, ... N-1
vector<vector<bool> > monsters_turn_position; // posição dos monstros ao longo dos turnos: 0, 1,..., N-1

// estruturas da bfs
queue<int> frontier;
vector<int> parents;
vector<bool> explored;
vector<int> depths;


// função que incializa as variáveis e estruturas
void init() {
    scanf(" %d %d %d %d %d", &N, &M, &J, &T, &K);
    
    // ler posição inicial dos monstros; no máximo tem-se 100 monstros e rotas de tamanho N
    monsters_turn_position.resize(N, std::vector<bool>(N, false));
    monsters.resize(N, false);
    explored.resize(N, false);
    parents.resize(N, -1);
    depths.resize(N, 0);

    for (int j=0; j < J; ++j) {
        int p;
        scanf("%d", &p);
        monsters[p-1] = true; // vértice diminuído de 1
    }

    // ler grafo/mapa com arestas ponderadas
    graph.resize(N);
    graph_t.resize(N);
    for (int i=0; i < M; ++i) {
        // aresta de x para y com peso w
        int x, y, w; 
        scanf(" %d %d %d", &x, &y, &w);
        --x; --y; // vértices diminúidos de 1
        graph[x].push_back(make_pair(y, w)); 
        graph_t[y].push_back(x);
    }
}


void build_monsters_route() {
    // loop por todas as posições iniciais dos monstros
    for (int i=0; i < N; ++i) {
        if (!monsters[i]) {continue;}
            // há monstro na posição inicial i
        int vertice = i;
        int turns = depths[i] + 1;
        for (int turn=0; turn < turns; ++turn) {
            monsters_turn_position[turn][vertice] = true;
            vertice = parents[vertice];
        }
        
    }
}


void bfs() {
    // vértice de início/caravana
    frontier.push(0);

    while(!frontier.empty()) {
        int u = frontier.front();
        frontier.pop();
        explored[u] = true;

        // observa-se os vértices adjacentes a u
        for (int v: graph_t[u]) {
            // caso v não tenha sido explorado
            if (!explored[v]) {
                // u é pai de v
                parents[v] = u;
                depths[v] = depths[u] + 1;
                explored[v] = true;
                frontier.push(v);
            }
        }
    }
}


// função para printar o grafo ponderado
void print(bool graph_flag=false, bool monsters_turn_flag=false) {

    if (graph_flag) {
        printf("=== GRAFO ===\n");
        for (int u=0; u < N; ++u) {
            printf("%d: ", u);
            for (node edge : graph[u]) {
                printf(" (%d %d)", edge.first, edge.second);
            }
            printf("\n");
        }
    }
    
    if (monsters_turn_flag) {
        for (int i=0; i < N; ++i) {
            printf("turn %d: ", i);
            for (int monster : monsters_turn_position[i]) {
                printf("%d ", monster);
            }
            printf("\n");
        }
    }
}


int main(void) {
    
    init();
    bfs();
    build_monsters_route();

    print(false, true);

    return 0;
}


/*
Próxima etapa:
    calcular os caminhos mínimos dos mosntros até a caravana.
    Juntar isso em uma estrutura matricial ou de adjacência com turnos x posicao de mosntros
*/