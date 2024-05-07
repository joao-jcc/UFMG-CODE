#include <stdio.h>
#include <vector>
#include <queue>
#include <stack>
#include <limits.h>

using namespace std;
#define INF INT_MAX


typedef pair<int, int> node;
struct tuple3 {
    int distance;
    int vertice;
    int turn;

    // Define the custom comparator function
    bool operator<(const tuple3& other) const {
        return distance < other.distance; // Order by distance from minor to greater
    }
};

struct comparetuple3 {
    bool operator()(tuple3 const& t1, tuple3 const& t2)
    {
        return t1.distance > t2.distance;
    }
};


int N, M, J, T, K; 
vector<vector<node> > graph;  
vector<vector<int> > graph_t; 
vector<bool> monsters;
vector<vector<bool> > monsters_turn_position;
int max_monster_turn;

// OUTPUT
int COST, TURN;
stack<int> player_path;
vector<vector<int> > monsters_path;
const vector<vector<int> > monsters_path_final;

// função que incializa as variáveis globais 
void init() {

    scanf(" %d %d %d %d %d", &N, &M, &J, &T, &K);
    monsters_turn_position.resize(N, std::vector<bool>(N, false));
    monsters_path.resize(N, vector<int>());
    monsters.resize(N, false);
    max_monster_turn = 0;

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

        graph[x].push_back(make_pair(w, y)); 
        graph_t[y].push_back(x);

    }
    // loops
    for (int i=0; i < N; ++i) {
        graph[i].push_back(make_pair(1, i));
    }
}

bool lack_rsc(int distance, int turn) {
    return distance > (turn+1) * K;
}


// calcula a posição dos monstros ao longo dos turnos
void build_monsters_route(vector<int> parents, vector<int> depths) {
    // loop por todas as posições iniciais dos monstros

    for (int i=0; i < N; ++i) {
        if (!monsters[i]) {continue;}
        // não há caminho do monstro para a caravana porém o monstro está no posicao i
        if (depths[i] == INF){
            monsters_path[i].push_back(i);
               
            for (int turn=0; turn < N; ++turn) {
                monsters_turn_position[turn][i] = true; // monstro parado
            }
            continue;
        }
        // há monstro na posição inicial i e há caminho para caravana
        int vertice = i;
        int turns = depths[i] + 1;
        for (int turn=0; turn < turns; ++turn) {
            monsters_turn_position[turn][vertice] = true;
            monsters_path[i].push_back(vertice);
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
        int u = frontier.front(); frontier.pop();
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

void we_loose(vector<vector<int> >& parents, vector<vector<int> >& min_distances, int max_turn) {
    int min_d = INF;
    int vertice = 0;
    for (int i=0; i < N; ++i) {
        if (min_distances[i][max_turn] < min_d && min_distances[i][max_turn] != 0) {
            vertice = i;
            min_d = min_distances[i][max_turn];
        }
    }

    COST = min_d; TURN = max_turn;

    player_path.push(vertice+1);
    for (int i=0; i < max_turn; ++i) {
        vertice = parents[vertice][max_turn-i];
        player_path.push(vertice+1); 
    }
}


/*
[x] loops
[x] monstros
[x] turnos
[x] recursos
*/
bool djkistra(int source) {
    priority_queue<tuple3, vector<tuple3>, comparetuple3> pq;
    
    vector<vector<int> > min_distances(N, vector<int>(T, INF));
    vector<vector<int> > parents(N, vector<int>(T, -2));
    vector<vector<bool> > explored(N, vector<bool>(T, false));
    int u, distance, turn;
    int max_turn;

    min_distances[0][0] = 0;
    parents[0][0] = -1;
    explored[0][0] = true;
    pq.push(tuple3{0, source, 0}); // distance, vertice, turn

    tuple3 tuple;
    while(!pq.empty()) {

        tuple = pq.top(); pq.pop();

        // excedeu número de turnos máximo
        if (tuple.turn > T) {continue;}

        u = tuple.vertice;
        distance = tuple.distance;
        turn = tuple.turn;

        max_turn = turn > max_turn ? turn : max_turn;

        explored[u][turn] = true;
        // solução encontrada
        if (u == N-1) {
            COST = distance; TURN = turn;

   
            player_path.push(u+1);
            for (int i=0; i < turn; ++i) {
                u = parents[u][turn-i];
                player_path.push(u+1); 
            }

            return true;
        } 


        // loop por todos os vértice adjacentes a u
        for (node edge : graph[u]) {
    
            int w = edge.first;
            int v = edge.second;
            
            // monstros: olhando turno atual e futuro
            int indice = turn > max_monster_turn ? max_monster_turn : turn;
            if (monsters_turn_position[indice][v] || monsters_turn_position[indice+1][v]) {continue;}
            
            int hyp_distance = distance + w; // distância candidata
            if (!explored[v][turn+1]) { 
                if (lack_rsc(hyp_distance, turn+1)) {continue;}

                min_distances[v][turn+1] = hyp_distance;
                pq.push(tuple3{min_distances[v][turn+1], v, turn+1});
                // u é pai de v
                parents[v][turn+1] = u;

            } else if (min_distances[v][turn+1] > hyp_distance) {
                if (lack_rsc(hyp_distance, turn+1)) {continue;}
                min_distances[v][turn+1] = hyp_distance;
                pq.push(tuple3{min_distances[v][turn+1], v, turn+1});
                // u é pai de v
                parents[v][turn+1] = u;

            }
        }
    }


    we_loose(parents, min_distances, max_turn);

    return false;
}



int main(void) {
    
    init();
    bfs();

    if(djkistra(0)) {
        printf("1\n");
    } else {printf("0\n");};

    for (int i=0; i < N; ++i) {
        if (!monsters[i]) {continue;};

        int size =  monsters_path[i].size(); 
        printf("%d ", size);
        for (int j=0; j < size; ++j) {
            if (j != size-1) {
            printf("%d ", monsters_path[i][j]+1);
            }
            else {
            printf("%d\n", monsters_path[i][j]+1);
            }
        }
    }

    printf("%d %d\n", COST, TURN);

    for (int i=0; i < TURN+1; ++i) {
        if (i != TURN)
        printf("%d ", player_path.top());
        else 
        printf("%d\n", player_path.top());
        player_path.pop();
    }


    return 0;
}