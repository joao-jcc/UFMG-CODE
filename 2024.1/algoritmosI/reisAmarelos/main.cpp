#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;
#define INF (unsigned)!((int)0)

/*
node: (peso da aresta, vértice de destino) ou (distancia pata origem, vértice)
N: número de vértices no grafo
M: número de conexões no grafo
J: número de monstros
T: número máximo de turnos a serem jogados
K: número de recursos do turno
graph: mapa do jogo, grafo ponderado
graph_t: mapa do jogo sem pesos para BFS da etapa dos monstros
monsters: indica a posição inicial dos monstros no turno 0
monsters_turn_position: posição dos monstros ao longo dos turnos até o turno onde não há mais mudança
*/
typedef pair<int, int> node;
int N, M, J, T, K; 
vector<vector<node> > graph;  
vector<vector<int> > graph_t; 
vector<bool> monsters;
vector<vector<bool> > monsters_turn_position;
int max_monster_turn;


// função que incializa as variáveis globais 
void init() {

    scanf(" %d %d %d %d %d", &N, &M, &J, &T, &K);
    monsters_turn_position.resize(N, std::vector<bool>(N, false));
    monsters.resize(N, false);
    max_monster_turn = -1;

    for (int j=0; j < J; ++j) {
        int p;
        scanf("%d", &p);
        monsters[p-1] = true; // vértice diminuído de 1
    }

    // ler grafo/mapa com arestas ponderadas
    graph.resize(N);
    graph_t.resize(N);
    for (int i=0; i < M; ++i) {

        int x, y, w;         // aresta de x para y com peso w
        scanf(" %d %d %d", &x, &y, &w);
        --x; --y; // vértices diminúidos de 1

        graph[x].push_back(make_pair(y, w)); 
        graph_t[y].push_back(x);

    }
}

// calcula a posição dos monstros ao longo dos turnos
void build_monsters_route(vector<int> parents, vector<int> depths) {
    // loop por todas as posições iniciais dos monstros
    for (int i=0; i < N; ++i) {
        if (!monsters[i]) {continue;}
        // não há caminho do monstro para a caravana
        if (depths[i] == INF){
            for (int turn=0; turn < N; ++turn) {
                monsters_turn_position[turn][i] = true; // monstro parado
            }
            continue;
        }
            // há monstro na posição inicial i
        int vertice = i;
        int turns = depths[i] + 1;
        for (int turn=0; turn < turns; ++turn) {
            monsters_turn_position[turn][vertice] = true;
            vertice = parents[vertice];
        }

        max_monster_turn = turns > max_monster_turn ? turns : max_monster_turn;
        --max_monster_turn;
    }
}

// calcula os caminhos mínimos dos monstros à caravana
void bfs() {
    // estruturas da bfs
    vector<int> parents(N, -1);
    vector<bool> explored(N, false);
    vector<int> depths(N, INF);
    queue<int> frontier;
    // vértice de início/caravana
    depths[0] = 0;
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

    build_monsters_route(parents, depths);
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
        printf("max monster turn: %d\n", max_monster_turn);
    }
}


int main(void) {
    
    init();
    bfs();

    print(false, true);

    return 0;
}


/*
Próxima etapa:
    calcular os caminhos mínimos dos mosntros até a caravana.
    Juntar isso em uma estrutura matricial ou de adjacência com turnos x posicao de mosntros
*/
