#include <stdio.h>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
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
        if (t1.distance != t2.distance) {
            return t1.distance > t2.distance;} 
        else if (t1.turn != t2.turn) {
            return t1.turn < t2.turn;
      } else {
        return t1.vertice > t2.vertice;
      };
    }
};

int N, M, J, T, K;
vector<vector<node> > graph;  

//Output
// colunas de 0 a T guardam o caminho do monstro
// coluna T+1 guarda o tamanho do caminho
stack<int> player_path;
int COST, TURN, WIN;

vector<int> monsters_initial;
vector<vector<int> > monster_path; // N X T



// calcula a posição dos monstros ao longo dos turnos
void build_monsters_path(vector<vector <int> >& graph_t) {

    // bfs no grafo transposto
    vector<int> parents(N, -1);
    vector<bool> explored(N, false);
    vector<int> depths(N, INF);
    queue<int> frontier;
    // vértice de início/caravana
    depths[0] = 0; 
    explored[0] = true;
    frontier.push(0);

    while(!frontier.empty()) {
        int u = frontier.front(); frontier.pop();
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
            else if (depths[v] == depths[u] + 1 && parents[v] > u) {
                parents[v] = u;
            }
        }
    }

    for (int i=0; i < J; ++i) {
        int current = monsters_initial[i];

        for (int v = current; v != -1; v = parents[v]) {
            monster_path[i].push_back(v);
        }

    }
}   


// função que incializa as variáveis globais 
void init() {
    if (scanf(" %d %d %d %d %d", &N, &M, &J, &T, &K) != 5 || N < 0 || M < 0 || J < 0 || T < 0 || K < 0) {return;}
    
    monsters_initial.resize(J, -1);
    monster_path.resize(J, vector<int>());
    for (int j=0; j < J; ++j) {
        int p;
        if ((scanf(" %d", &p) != 1) || p <= 0 || p > N) {return;}
        
        monsters_initial[j] = p-1;
    }

    // ler grafo/mapa com arestas ponderadas
    vector<vector <int> > graph_t(N, vector<int>());
    graph.resize(N);
    for (int i=0; i < M; ++i) {

        int x, y, w;         // aresta de x para y com peso w

        if (scanf(" %d %d %d", &x, &y, &w) != 3 || x < 0 || y < 0 || w < 0) {return;}
        --x; --y; // vértices diminúidos de 1

        graph[x].push_back(make_pair(w, y)); 
        graph_t[y].push_back(x);
        // Resolver problema que monstros tem uma predileção por caminhos lexicograficamente pequenos:
        sort(graph_t[y].begin(), graph_t[y].end());

    }

    // loops
    for (int i=0; i < N; ++i) {
        graph[i].push_back(make_pair(1, i));
    }

    build_monsters_path(graph_t);
}


vector<vector<bool>> transpose_by_bool(const vector<vector<int>>& matrix) {        
    vector<vector<bool> > transposed(T+1, vector<bool>(N, false));

    // 6 4 2 1
    // 7 4 2 1
    for (int i=0; i < J; ++i) {
        int size = matrix[i].size();
        if (size == 1) {
            int v = matrix[i][0];
            for (int turn=0; turn<T+1; ++turn) {
                transposed[turn][v] = true;
            }
             continue;
        }
        for (int turn=0; turn < size; ++turn) {
            int el = matrix[i][turn];
            transposed[turn][el] = true;
        }

        for (int turn=size; turn < T+1; ++turn) {
            transposed[turn][0] = true;
        }
    }    
    return transposed;
}



void djkistra(int source) {
    priority_queue<tuple3, vector<tuple3>, comparetuple3> pq;
    
    vector<vector<int> > min_distances(N, vector<int>(T+1, INF));
    vector<vector<int> > parents(N, vector<int>(T+1, -2));
    vector<vector<bool> > turn_vertice_monsters = transpose_by_bool(monster_path);

    
    min_distances[0][0] = 0;
    parents[0][0] = -1;

    pq.push(tuple3{0, source, 0}); // distance, vertice, turn

    tuple3 the_best = {0, source, 0};
    tuple3 bacopolis = {0, source, 0};

    while(!pq.empty()) {

        tuple3 tuple = pq.top(); pq.pop();

        int u = tuple.vertice;
        int distance = tuple.distance;
        int turn = tuple.turn;


        if (min_distances[u][turn] < distance) {continue;}

        // ordenando lexicograficamente por turno maior, distancia menor e vertice menor
        bool c1 = turn > the_best.turn;
        bool c2 = (turn == the_best.turn && distance < the_best.distance);
        bool c3 = (turn == the_best.turn) && (distance = the_best.distance) && (u < the_best.vertice);

        if (c1 || c2 || c3) {the_best = tuple;};

        // solução encontrada
        if (u == N-1) {
            bacopolis = tuple;
            break;
        } 

        // excedeu o turno limite
        if (turn == T) {continue;}


        // loop por todos os vértice adjacentes a u
        for (node edge : graph[u]) {
    
            int w = edge.first;
            int v = edge.second;

            // verificar monstros
            if (turn_vertice_monsters[turn][v] || turn_vertice_monsters[turn+1][v]) {continue;}
            
            // relaxamento do vértice se houver
            int current_distance = min_distances[v][turn+1];
            int hyp_distance = min_distances[u][turn] + w;
            int resources = (turn + 1) * K;

            if (current_distance > hyp_distance && hyp_distance <= resources) {
                min_distances[v][turn+1] = hyp_distance;
                parents[v][turn+1] = u;
                pq.push({min_distances[v][turn+1], v, turn+1});
            }
        }
    }


    int vertice, turn;
    if (bacopolis.turn > 0) { 
        WIN = 1;
        turn = TURN = bacopolis.turn;
        vertice = bacopolis.vertice;
    } else {
        WIN = 0;
        turn = TURN = the_best.turn;
        vertice = the_best.vertice;
    }

    COST = min_distances[vertice][turn];

    player_path.push(vertice+1);
    for (int i=0; i < turn; ++i) {
        vertice = parents[vertice][turn-i];
        player_path.push(vertice+1); 
    }
}

void print_monsters_path() {

    for (int i = 0; i < J; i++){
        // Printar o comprimento do caminho do monstro i:
        int comp = monster_path[i].size();
        printf("%d", comp);
        for(int t = 0; t < comp; t++){
            // Printar o caminho do monstro i:
            printf(" %d", monster_path[i][t] + 1);
        }
        printf("\n");
    }
}


int main(void) {
    
    init();
    djkistra(0);

    printf("%d\n", WIN ? 1 : 0);
    
    print_monsters_path();

    printf("%d %d\n", COST, TURN);

    while (!player_path.empty()) {
        printf("%d ", player_path.top());
        player_path.pop();
    }
    printf("\n");

    return 0;
}
