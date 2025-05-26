#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define INF 0x3f3f3f3f

int N, M, S;
vector<vector<pair<int, int> > > adj;
vector<int> distances;
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;


int main(void) {_
    // Leitura
    cin >> N >> M; 
    adj.assign(N + 1, vector<pair<int, int>>());
    distances.assign(N+1, INF);
    
    for (int i=0, u, v, w; i < M; ++i) {
        cin >> u >> v >> w;
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }

    cin >> S;

    // Dijkstra
    pq.push(make_pair(0, S)); distances[S] = 0;
    while (!pq.empty()) {
        int disAtual = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (disAtual > distances[u]) {continue;}

        for (auto [v, w] : adj[u]) {
            if (distances[v] > distances[u] + w) {
                distances[v] = distances[u] + w;
                pq.push(make_pair(distances[v], v));
                }
            }
        }

        int min_v = INF, max_v = -1;
        for (int d : distances) {
            if (d == 0 || d == INF) continue;
            if (d < min_v) min_v = d;
            if (d > max_v) max_v = d;
        }

        cout << max_v - min_v << endl;

    exit(0);
}