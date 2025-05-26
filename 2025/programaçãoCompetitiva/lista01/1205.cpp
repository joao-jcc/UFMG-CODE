#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <iomanip>
#include <string>



using namespace std;
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define INF 0x3f3f3f3f

int N, M, K, O, D;
double P;

vector<vector<int> > adj;
vector<int> weights;
vector<int> distances;
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

int main(void) {_

    while (cin>>N) {
        // Leitura
        cin >> M >> K >> P;

        adj.assign(N+1, vector<int>()); 
        weights.assign(N+1, 0);
        distances.assign(N+1, INF);
        for (int i=0, u, v; i<M; ++i) {
            cin >> u >> v;
            adj[u].push_back(v); adj[v].push_back(u);
        }

        int A; cin >> A;  
        for (int i=0, s; i < A; ++i) {
            cin >> s; ++weights[s];
        }
        
        cin >> O >> D;

        // Dijkstra
        pq.push(make_pair(weights[O], O)); distances[O] = weights[O];
        while (!pq.empty()) {
            int disAtual = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (disAtual > distances[u]) {continue;}

            for (int v : adj[u]) {
                int w = weights[v];
                if (distances[v] > distances[u] + w) {
                    distances[v] = distances[u] + w;
                    pq.push(make_pair(distances[v], v));
                    }
                }
            }

            double ans = 0;
            if (distances[D] <= K) {
                ans = std::round( pow(P, distances[D])  * 1000) / 1000;
            }
        
            cout << fixed << setprecision(3) << ans << endl;
    }
    

    exit(0);
}